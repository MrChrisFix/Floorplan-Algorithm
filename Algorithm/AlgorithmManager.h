#pragma once
#include <vector>
#include <mutex>
#include "ResultStruct.h"
#include <future>
#include <chrono>
#include <deque>
#include "PlacementGraph.h"

namespace FPA {

class AlgorithmManager
{
private:
	std::vector<Type*> types;						/// The vector of types used for all calculations
	PlacementGraph* Graphs;							/// The graph

	//Calc
	unsigned bestValue;								/// The current best area
	unsigned bestWidth;								/// The currently best width
	unsigned bestHeight;							/// The currently best height
	std::map<Type*, Variant*> bestCombination;		/// The currently best combination of variants

	//Multithreading
	short threadNum;								/// The number of threads which should be used in multithreading
	int availableBufferSpace;						/// The number of items, that can be added to the WorkToDo buffer
	bool caltulateMultithread;						/// Should the aplication use multithreading
	std::mutex bufferSizeGuard;						/// Semaphore protecting the buffer
	std::mutex guard;								/// Semaphore protecting the best values

public:
	std::deque<std::pair<int, std::map<Type*, Variant*>>> WorkToDo;		/// Buffer of tasks for multithreading

public:
	/**
	 * Constructor
	*/
	AlgorithmManager();

	/**
	 * Destructor
	*/
	~AlgorithmManager();

	/**
	 * The main method of this class.
	 * @param threads Number of thread the algorithm should be using
	 * @param multiThread Should the aplication use multithreading
	 * @return The result of the optimization. The values are empty and 0 if no result at all was found.
	*/
	ResultStruct* StartCalculations(unsigned int threads, bool multiThread = false);

	/**
	 * Sets the type vector
	 * @param Types The new type vector
	*/
	void setTypes(std::vector<Type*> Types);

private:
	/**
	 * Method, which starts sequentional or parralel calculations
	*/
	void FindOptimal();


	/**
	 * Recurrent method for finding the optimal configuraion by going through a tree-like structure
	 * @param depth The next depth of the tree
	 * @param variantStack The current variant coniguration
	*/
	void FindSinglethread(unsigned depth, std::map<Type*, Variant*> variantStack);

	/**
	 * Recurrent method for finding the optimal configuraion by going through a tree-like structure. This method is for threads, becouse it uses semaphores
	 * @param depth The next depth of the tree
	 * @param variantStack The current variant coniguration
	*/
	void FindMultithread(unsigned depth, std::map<Type*, Variant*> variantStack);

	/**
	 * The method the main thread is stuck in while other threads find the optimal solution. 
	 * The main therad creates and destroys threads in a producer-consumer like scenario
	*/
	void ManageThreads();

	/**
	 * Saves the best configuration based on the configuration
	 * @param variantStack The variaont configuraion, whoose cost values should be saved
	*/
	void CalculateCostsWithMutex(std::map<Type*, Variant*> variantStack);

	/**
	 * The method created a ResultStruct object and inserts the best value to it
	 * @return A ResultStruct, which has the best values stored in it
	*/
	ResultStruct* GetResults();
};

} //namespace FPA