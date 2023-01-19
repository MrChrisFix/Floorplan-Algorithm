#include "GraphNode.h"
#include <algorithm>

namespace FPA {

unsigned GraphNode::GoThroughBranch(std::vector<Variant*> &combination) const
{
    if (this->isEnd)
        return 0;


    unsigned max = 0;
    /*for (auto branch : this->next)
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
    }*/

    return max;
}

//void GraphNode::removeChildNode(GraphNode* node)
//{
//    this->next.erase(std::find(this->next.begin(), this->next.end(), node));
//}

std::vector<GraphNode*> GraphNode::GetVectorBySide(SIDE side)
{
    switch (side)
    {
    case FPA::SIDE::UP:
    {
        return this->up;
    }
    case FPA::SIDE::LEFT:
    {
        return this->left;
    }
    case FPA::SIDE::DOWN:
    {
        return this->down;
    }
    case FPA::SIDE::RIGHT:
    {
        return this->right;
    }
    default:
        break;
    }
}

std::vector<GraphNode*> GraphNode::GetVectorByOppsiteSide(SIDE side)
{
    switch (side)
    {
    case FPA::SIDE::UP:
    {
        return this->down;
    }
    case FPA::SIDE::LEFT:
    {
        return this->right;
    }
    case FPA::SIDE::DOWN:
    {
        return this->up;
    }
    case FPA::SIDE::RIGHT:
    {
        return this->left;
    }
    default:
        break;
    }
}

GraphNode::GraphNode(bool Root)
{
    this->isRoot = Root;
    this->isEnd = !Root;
    this->type = nullptr;
}

GraphNode::GraphNode(Type* theType)
{
    this->isEnd = false;
    this->isRoot = false;
    this->type = theType;
}

GraphNode::~GraphNode()
{
    for (auto node : this->right)
    {
        if (node->left.size() == 1) //I am the only parent
        {
            delete node;
        }
        else //Remove child connection to me
        {
            auto it = std::find(node->left.begin(), node->left.end(), this);
            node->left.erase(it);
        }
    }
    this->up.clear();
    this->down.clear();
    this->left.clear();
    this->right.clear();
    this->type = nullptr;
}

void GraphNode::ConnectWithNode(GraphNode* node, SIDE side)
{    
    bool found = false;
    for(auto& nod : this->GetVectorBySide(side))
        if (nod == node)
        {
            found = true;
            break;
        }

    if (!found) //Preventing adding the same node multiple times
    {
        this->GetVectorBySide(side).push_back(node);
        node->GetVectorByOppsiteSide(side).push_back(this);
    }

}

unsigned int GraphNode::calculateCost(std::vector<Variant*> combination) const
{
    if(!this->isRoot) //Only the root should use this method
        return 0;

    return GoThroughBranch(combination);

}

Type* GraphNode::GetType()
{
    return this->type;
}

} //namespace FPA
