#pragma once
#include <string>
#include <vector>
#include <mutex>
//#include "Type.h"
#include "ResultStruct.h"
#include <future>
#include <chrono>
#include <deque>
#include "PlacementGraph.h"

namespace FPA {

class AlgorithmManager
{
private:
	std::vector<Type*> types;

	//GraphNode *Graph_G, *Graph_H;
	//GraphNode *Graph_G_End, *Graph_H_End;
	PlacementGraph* Graphs;

	//Calc
	unsigned bestValue;
	unsigned bestWidth;
	unsigned bestHeight;
	std::map<Type*, Variant*> bestCombination;

	//Multithreading
	short threadNum;
	int awaliableBufferSpace;
	bool caltulateMultithread;
	std::mutex bufferSizeGuard;
	std::mutex guard;

public:
	std::deque<std::pair<int, std::map<Type*, Variant*>>> WorkToDo;

public:
	AlgorithmManager();
	~AlgorithmManager();

	ResultStruct StartCalculations(unsigned int threads, bool multiThread = false);
	void setTypes(std::vector<Type*> Types);

private:
	//void FixTypeConnections();
	//void PopulateGraphs();
	void FindOptimal();

	void FindSinglethread(unsigned depth, std::map<Type*, Variant*> variantStack);
	void FindMultithread(unsigned depth, std::map<Type*, Variant*> variantStack);
	void ManageThreads();
	void CalculateCostsWithMutex(std::map<Type*, Variant*> variantStack);

	ResultStruct GetResults();
};

} //namespace FPA