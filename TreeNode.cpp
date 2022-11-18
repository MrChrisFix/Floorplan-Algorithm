#include "TreeNode.h"

TreeNode::TreeNode(TreeNode* parentPtr)
{
	this->parent = parentPtr;
}

TreeNode::~TreeNode()
{
	for (auto node : branches)
	{
		if(node != nullptr)
			delete node;
		node = nullptr;
	}
	branches.clear();
	this->parent = nullptr;
}

TreeNode* TreeNode::AddNewBranch()
{
	TreeNode* node = new TreeNode(this);
	this->branches.push_back(node);

	return node;
}

void TreeNode::AddLeaf(TreeNodeLeaf* leaf)
{
	branches.push_back((TreeNode*) leaf);
}
