#include "RectanglePlacer.h"
#include <stack>

namespace FPA
{

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
			if (this->plane[currentNode->GetType()] != nullptr) // this element already exists on the plane
			{
				if (currentDownIndex == 0 && currentRightIndex == 0) // the indexes are always 0 when entering an unknown element
				{
					currentNode = parentPtrs.top().node;
					currentRightIndex = parentPtrs.top().rightIndex;
					currentDownIndex = parentPtrs.top().downIndex;
					parentPtrs.pop();
					continue;
				}
			}
			else
			{
				//Create rect
				Variant* var = configuration[currentNode->GetType()];
				if (var == nullptr)
					var = this->blankVariant;
				VariantRectangle* rect = new VariantRectangle(var, pt.X, pt.Y); //TODO: position
				this->plane[currentNode->GetType()] = rect;
			}

		}


		if (currentNode->GetRightNodes().size() <= currentRightIndex || currentNode->GetRightNodes()[0]->isEndNode()) //Did all elements on the right
		{
			//Go down
			if (currentNode->GetDownNodes().size() <= currentDownIndex || currentNode->GetDownNodes()[0]->isEndNode()) //Also did everything down
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
			else //I can go more down (TODO: but should i always do it?)
			{
				bool found = false;
				for (auto right : parentPtrs.top().node->GetRightNodes())
					if (currentNode->GetDownNodes()[currentDownIndex] == right)
						found = true;

				if (!found) // If the element down isn't part of our parent left
				{
					currentNode = parentPtrs.top().node;
					currentRightIndex = parentPtrs.top().rightIndex;
					currentDownIndex = parentPtrs.top().downIndex;
					parentPtrs.pop();
					continue;
				}

				Variant* var = configuration[currentNode->GetType()];
				if (var != nullptr)
					pt.Y += var->GetHeight();

				parentPtrs.push(Parent(currentNode, currentRightIndex, currentDownIndex + 1));
				currentNode = currentNode->GetDownNodes()[currentDownIndex];
				currentRightIndex = 0;
				currentDownIndex = 0;
				continue;
			}
		}
		else //I can go more to the right
		{
			Variant* var = configuration[currentNode->GetType()];
			if (var != nullptr)
				pt.X += var->GetWidth();
			
			if (currentRightIndex > 0)
			{
				auto lastBeenRightElement = currentNode->GetRightNodes()[currentRightIndex - 1];
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

	AddRectangles();

	return this->plane;
}

} //namespace FPA

