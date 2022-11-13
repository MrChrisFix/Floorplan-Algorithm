#pragma once
#include <vector>
#include "Type.h"
#include <string>
#include "TreeNode.h"

class AlgorithmManager
{
private:
	std::vector<Type*> types;
	TreeNode* treeRoot;

public:
	AlgorithmManager();
	~AlgorithmManager();

	void StartCalculations();
	void setTypes(std::vector<Type*> Types);
	void importTypesFromXML(std::string pathToXml);

private:
	void CreateTree();

	void AddTreeBranch(unsigned int depth, TreeNode* ptr);
};

