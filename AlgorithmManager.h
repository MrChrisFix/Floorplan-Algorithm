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

public:
	AlgorithmManager();
	~AlgorithmManager();

	void StartCalculations();
	void setTypes(std::vector<Type*> Types);
	void importTypesFromXML(std::string pathToXml);

private:
	void CreateTree();

	void AddTreeBranch(unsigned int depth, std::vector<Variant*> &variantStack, TreeNode* ptr);
};

