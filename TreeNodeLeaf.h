#pragma once
#include "TreeNode.h"
#include "Variant.h"

struct TreeNodeLeaf : public TreeNode
{
private:
	//No outside access
	using TreeNode::branches; 
	using TreeNode::AddNewBranch;
public:
	unsigned int cost;
	std::vector<Variant*> composition;

	TreeNodeLeaf(TreeNode* parent, unsigned int Cost, std::vector<Variant*> variants);
};

