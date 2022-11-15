#include "GraphNode.h"

unsigned GraphNode::GoThroughBranch(std::vector<Variant> &combination) const
{
    if (this->isEnd)
        return 0;


    unsigned max = 0;
    for (auto branch : this->next)
    {
        unsigned myCost = 0;
        if (!this->isRoot)
        {
            for (auto& var : combination)
            {
                if (var.GetType() == this->type)
                {
                    if (this->calcHeight)
                        myCost = var.Height();
                    else
                        myCost = var.Width();
                    break;
                }
            }
        }
        unsigned cost = branch->GoThroughBranch(combination) + myCost;
        if (cost > max)
            max = cost;
    }

    return max;
}

GraphNode::GraphNode(bool Root, bool countHeight)
{
    this->isRoot = Root;
    this->isEnd = !Root;
    this->calcHeight = countHeight;
    this->type = nullptr;
}

GraphNode::GraphNode(Type* theType, bool countHeight)
{
    this->isEnd = false;
    this->isRoot = false;
    this->type = theType;
    this->calcHeight = countHeight;
}

void GraphNode::AddNodeToGraph(GraphNode* node)
{
    this->next.push_back(node);
    node->prev.push_back(this);
}

unsigned int GraphNode::calculateCost(std::vector<Variant> combination) const
{
    if(!this->isRoot) //Only the root should use this method
        return 0;

    return GoThroughBranch(combination);

}
