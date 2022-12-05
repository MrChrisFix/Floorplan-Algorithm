#include "GraphNode.h"
#include <algorithm>

unsigned GraphNode::GoThroughBranch(std::vector<Variant*> &combination) const
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
                if (var->GetType() == this->type)
                {
                    if (this->calcHeight)
                        myCost = var->GetHeight();
                    else
                        myCost = var->GetWidth();
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

void GraphNode::removeChildNode(GraphNode* node)
{
    this->next.erase(std::find(this->next.begin(), this->next.end(), node));
}

GraphNode::GraphNode(bool Root, bool is_H_Graph)
{
    this->isRoot = Root;
    this->isEnd = !Root;
    this->calcHeight = is_H_Graph;
    this->type = nullptr;
}

GraphNode::GraphNode(Type* theType, bool is_H_Graph)
{
    this->isEnd = false;
    this->isRoot = false;
    this->type = theType;
    this->calcHeight = is_H_Graph;
}

GraphNode::~GraphNode()
{
    for (auto node : this->next)
    {
        if (node->prev.size() == 1) //I am the only parent
        {
            delete node;
        }
    }

    this->prev.clear();
    this->next.clear();
    this->type = nullptr;
}

void GraphNode::AddNodeToGraph(GraphNode* node)
{
    if (std::find(this->next.begin(), this->next.end(), node) != this->next.end() || !(this->next.size() > 1) ) //Preventing adding the same node multiple times
    {
        this->next.push_back(node);
        node->prev.push_back(this);
    }

}

unsigned int GraphNode::calculateCost(std::vector<Variant*> combination) const
{
    if(!this->isRoot) //Only the root should use this method
        return 0;

    return GoThroughBranch(combination);

}

GraphNode* GraphNode::FindNodeByType(Type* searched)
{
    for (auto node : this->next)
    {
        if (node->type == searched)
            return node;
        node->FindNodeByType(searched);
    }

    return nullptr;
}

Type* GraphNode::GetType()
{
    return this->type;
}
