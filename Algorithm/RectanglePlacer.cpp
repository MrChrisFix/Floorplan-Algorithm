#include "RectanglePlacer.h"
#include <stack>

namespace FPA
{

void RectanglePlacer::AddNextRect(int tlX, int tlY, GraphNode* parNode)
{
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
			//Hey, don't do this here, do it in the method below :)
		}
	}

}

void RectanglePlacer::AddRectangles()
{
	struct Parent {
		GraphNode* node;
		int rightIndex;
		int downIndex;
		Parent(GraphNode* nodeptr, int nextRight, int nextDown) : node(nodeptr), rightIndex(nextRight), downIndex(nextDown) {};
	};

	std::stack<Parent> parentPtrs;
	auto currentNode = startNode;
	int currentRightIndex = 0;
	int currentDownIndex = 0;

	Point pt(0,0);
	Point suggestedPt(0, 0);

	while (true)
	{
		if (currentNode->GetType() != nullptr)
		{
			//Create rect
			Variant* var = configuration[currentNode->GetType()];
			if (var == nullptr)
				var = this->blankVariant;
			VariantRectangle* rect = new VariantRectangle(var, 0, 0); //TODO: position
			this->plane[currentNode->GetType()] = rect;
		}


		if (currentNode->GetRightNodes().size() <= currentRightIndex || currentNode->GetRightNodes()[0]->isEndNode()) //Did all elements on the right
		{
			//Go down
			if (currentNode->GetDownNodes().size() <= currentDownIndex || currentNode->GetDownNodes()[0]->isEndNode()) //also did everything down
			{
				//I should go back to the parent

				if (parentPtrs.empty())
					break;

				currentNode = parentPtrs.top().node;
				currentRightIndex = parentPtrs.top().rightIndex;
				currentDownIndex = parentPtrs.top().downIndex;
				parentPtrs.pop();
				continue;
			}
			else // i can go more down (TODO: but should i always do it?)
			{
				Variant* var = configuration[currentNode->GetType()];
				if (var != nullptr)
					pt.Y += var->GetHeight();

				parentPtrs.push(Parent(currentNode, currentRightIndex, currentDownIndex+1));
				currentNode = currentNode->GetDownNodes()[currentDownIndex];
				currentRightIndex = 0;
				currentDownIndex = 0;
				continue;
			}
		}
		else //i can go more to the right
		{
			Variant* var = configuration[currentNode->GetType()];
			if (var != nullptr)
				pt.X += var->GetWidth();
			
			if (currentRightIndex > 0)
			{
				auto lastBeenRightElement = currentNode->GetRightNodes()[currentRightIndex-1];
				Variant* lastBeenRightVariant = configuration[lastBeenRightElement->GetType()];
				if (lastBeenRightVariant != nullptr)
					pt.Y += lastBeenRightVariant->GetHeight();
			}

			parentPtrs.push(Parent(currentNode, currentRightIndex + 1, currentDownIndex));
			currentNode = currentNode->GetRightNodes()[currentRightIndex];
			currentRightIndex = 0;
			currentDownIndex = 0;
			continue;
		}
	}
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

