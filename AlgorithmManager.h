#pragma once
#include <vector>
#include "Type.h"
#include <string>
#include "TreeNode.h"
#include "GraphNode.h"

class AlgorithmManager
{
private:
	std::vector<Type*> types;
	TreeNode* treeRoot;

	GraphNode *Graph_G, *Graph_H;
	GraphNode *Graph_G_End, *Graph_H_End;

public:
	AlgorithmManager();
	~AlgorithmManager();

	std::pair<unsigned,std::vector<Variant*>> StartCalculations();
	void setTypes(std::vector<Type*> Types);

private:
	void PopulateGraphs();
	void CreateTree();
	std::pair<unsigned, std::vector<Variant*>> FindOptimal();



	void ReadLeaf(TreeNode* currentNode, unsigned &currentMin, TreeNodeLeaf*& currentBest);
	void Populate_G_Graph(GraphNode* parentNode);
	void Populate_H_Graph(GraphNode* currentNode);
	void AddTreeBranch(unsigned int depth, std::vector<Variant*> &variantStack, TreeNode* ptr);
};

