#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "Type.h"
#include "GraphNode.h"
#include "ResultStruct.h"
#include <future>
#include <chrono>
#include <deque>

namespace FPA {

class AlgorithmManager
{
private:
	std::vector<Type*> types;

	GraphNode *Graph_G, *Graph_H;
	GraphNode *Graph_G_End, *Graph_H_End;

	//Calc
	unsigned bestValue;
	unsigned bestWidth;
	unsigned bestHeight;
	std::vector<Variant*> bestCombination;

	//Multithreading
	short threadNum;
	int awaliableBufferSpace;
	bool caltulateMultithread;
	std::mutex bufferSizeGuard;
	std::mutex guard;

public:
	std::deque<std::pair<int, std::vector<Variant*>>> WorkToDo;

public:
	AlgorithmManager();
	~AlgorithmManager();

	ResultStruct StartCalculations(unsigned int threads, bool multiThread = false);
	void setTypes(std::vector<Type*> Types);

private:
	void FixTypeConnections();
	void PopulateGraphs();
	void FindOptimal();

	void FindSinglethread(unsigned depth, std::vector<Variant*> variantStack);
	void FindMultithread(unsigned depth, std::vector<Variant*> variantStack);
	void ManageThreads();
	void CalculateCosts(std::vector<Variant*> variantStack);

	void Populate_G_Graph(GraphNode* parentNode);
	void Populate_H_Graph(GraphNode* currentNode);
};

} //namespace FPA