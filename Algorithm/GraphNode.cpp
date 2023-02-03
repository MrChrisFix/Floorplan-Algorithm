#include "GraphNode.h"
#include <algorithm>

namespace FPA {

std::vector<GraphNode*>& GraphNode::GetVectorBySide(SIDE side)
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
    return this->right;
}

std::vector<GraphNode*>& GraphNode::GetVectorByOppsiteSide(SIDE side)
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

std::vector<GraphNode*>& GraphNode::GetRightNodes()
{
    return this->right;
}

std::vector<GraphNode*>& GraphNode::GetDownNodes()
{
    return this->down;
}

bool GraphNode::isEndNode()
{
    return this->isEnd;
}

bool GraphNode::isStartNode()
{
    return this->isRoot;
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

Type* GraphNode::GetType()
{
    return this->type;
}

} //namespace FPA
