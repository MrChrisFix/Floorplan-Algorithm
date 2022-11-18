#pragma once
#include <vector>

struct TreeNodeLeaf; //<- avoiding a #include deadlock

struct TreeNode
{
	TreeNode* parent;
	std::vector<TreeNode*> branches;

	TreeNode(TreeNode* parentPtr);
	~TreeNode();

	TreeNode* AddNewBranch();
	void AddLeaf(TreeNodeLeaf* leaf);
};

