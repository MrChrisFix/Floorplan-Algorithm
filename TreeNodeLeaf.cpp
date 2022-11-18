#include "TreeNodeLeaf.h"

TreeNodeLeaf::TreeNodeLeaf(TreeNode* parent, unsigned int Cost, std::vector<Variant*> variants) : TreeNode(parent)
{
	this->cost = Cost;
	this->composition = variants;
}
