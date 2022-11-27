#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "Type.h"
#include "TreeNode.h"
#include "GraphNode.h"

class AlgorithmManager
{
private:
	std::vector<Type*> types;
	//TreeNode* treeRoot;

	GraphNode *Graph_G, *Graph_H;
	GraphNode *Graph_G_End, *Graph_H_End;

	//Calc
	unsigned bestValue;
	std::vector<Variant*> bestCombination;

	//Multithreading
	bool caltulateMultithread;
	std::mutex guard;

public:
	AlgorithmManager();
	~AlgorithmManager();

	std::pair<unsigned,std::vector<Variant*>> StartCalculations();
	void setTypes(std::vector<Type*> Types);

private:
	void PopulateGraphs();
	//[[deprecated]] void CreateTree();
	void FindOptimal();
	//[[deprecated]] std::pair<unsigned, std::vector<Variant*>> FindOptimal_old();

	void FindSinglethread(unsigned depth, std::vector<Variant*> variantStack);
	void FindMultithread(unsigned depth, std::vector<Variant*> variantStack);
	void CalculateCosts(std::vector<Variant*> variantStack);

	
	//[[deprecated]] void ReadLeaf(TreeNode* currentNode, unsigned &currentMin, TreeNodeLeaf*& currentBest);
	void Populate_G_Graph(GraphNode* parentNode);
	void Populate_H_Graph(GraphNode* currentNode);
	//[[deprecated]] void AddTreeBranch(unsigned int depth, std::vector<Variant*> &variantStack, TreeNode* ptr);
};

