#pragma once
#include <vector>
struct TreeNode
{
	TreeNode* parent;
	unsigned int nodeCost;
	unsigned int cost;		//< Summary cost of node and parent
	std::vector<TreeNode*> branches;

	TreeNode(TreeNode* parentPtr, unsigned int Cost);
	~TreeNode();

	TreeNode* AddNewBranch(unsigned int Cost);
	void reCalculateCost();
};

