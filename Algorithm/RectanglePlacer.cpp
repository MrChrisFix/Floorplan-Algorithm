#include "RectanglePlacer.h"
#include <stack>

namespace FPA
{

void RectanglePlacer::AddNextRect(int tlX, int tlY, GraphNode* parNode)
{
	/*for (auto node : parNode->GetRightNodes())
	{
		Variant* var = configuration[node->GetType()];
		if (var == nullptr)
			var = this->blankVariant;
		VariantRectangle* rect = new VariantRectangle(var, tlX, tlY);
		this->plane[node->GetType()] = rect;
		if (!node->GetRightNodes()[0]->isEndNode())
		{
			AddNextRect(tlX + var->GetWidth(), tlY, node);
		}
		tlY += var->GetHeight();
	}*/


	// new idea
	// 1. Create the rectangle
	// 2. If there are rectangles on the right create them top to bottom
	// 3. If there are rectanles down tell them the position of the bottom of the created elements on the right

	for (auto node : parNode->GetRightNodes())
	{
		Variant* var = configuration[node->GetType()];
		if (var == nullptr)
			var = this->blankVariant;
		VariantRectangle* rect = new VariantRectangle(var, tlX, tlY);
		this->plane[node->GetType()] = rect;
		if (!node->GetRightNodes()[0]->isEndNode())
		{
			//auto a = AddNextRect(tlX + var->GetWidth(), tlY, node);
		}
		if (!node->GetDownNodes()[0]->isEndNode())
		{

		}
	}

}

void RectanglePlacer::AddNextRect(int tlX, int tlY, GraphNode* parNode) //TODO: change name and agrs
{
	//Method name: AddRectangles

	std::stack<GraphNode*> parentPtrs;

	//parentPtrs.

}


RectanglePlacer::RectanglePlacer()
{
	this->blankVariant = new Variant(0, 0, nullptr);
	this->startNode = nullptr;
}

RectanglePlacer::~RectanglePlacer()
{
	this->startNode = nullptr;
}

std::map<Type*, VariantRectangle*> RectanglePlacer::PlaceRectangles(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration)
{
	this->startNode = start_H_Node;
	this->configuration = variantConfiguration;

	AddNextRect(0, 0, startNode); //The problem here is that the configuration isn't always complete, therefore conf[type] gives sometimes nullptr

	return this->plane;
}

} //namespace FPA

