#include "TreeNode.h"

TreeNode::TreeNode(TreeNode* parentPtr, unsigned int Cost)
{
	this->parent = parentPtr;
	this->nodeCost = Cost;
	if (parentPtr == nullptr)
		this->cost = Cost;
	else
		this->cost = parentPtr->cost + Cost;

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

TreeNode* TreeNode::AddNewBranch(unsigned int Cost)
{
	TreeNode* node = new TreeNode(this, Cost);
	this->branches.push_back(node);

	return node;
}

void TreeNode::reCalculateCost()
{
	if (this->parent != nullptr)
		this->cost = this->nodeCost + this->parent->cost;
	else
		this->cost = this->nodeCost;
}
