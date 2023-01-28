#include "RectanglePlacer.h"

namespace FPA
{

void RectanglePlacer::AddRectangles()
{
	while (true)
	{
		if (!currentNode->isStartNode())
		{
			if (this->plane[currentNode->GetType()] != nullptr) // this element already exists on the plane
			{
				if (currentDownIndex == 0 && currentRightIndex == 0) // the indexes are always 0 when entering an unknown element
				{
					GotoParent();
					continue;
				}
			}
			else
			{
				CreateRectangle();
			}

		}


		if (currentNode->GetRightNodes().size() <= currentRightIndex || currentNode->GetRightNodes()[0]->isEndNode()) //Did all elements on the right
		{
			lastBottomVar = currentNode->GetRightNodes()[currentNode->GetRightNodes().size() - 1];

			//Go down
			if (currentNode->GetDownNodes().size() <= currentDownIndex || currentNode->GetDownNodes()[0]->isEndNode()) //Also did everything down
			{//In this case I should go back to the parent
				
				if (parentPtrs.empty())
					break;

				GotoParent();
				continue; //<- this continue is useless, becouse without it goes anyway to the end of the loop
			}
			else //I can go more down (TODO: but should i always do it?)
			{
				if (!allowedToGoDown())
				{
					GotoParent();
					continue; //<- this continue could be useless, becouse without it goes anyway to the end of the loop
				}

				lastBottomVar = currentNode->GetRightNodes()[currentNode->GetRightNodes().size()];
				suggestedPt = plane[lastBottomVar->GetType()]->BottomLeft();

				pt = plane[currentNode->GetType()]->BottomLeft();

				if (currentDownIndex > 0)
				{
					auto lastBeenBottomElement = currentNode->GetDownNodes()[currentDownIndex - 1];
					Variant* lastBottomVariant = configuration[lastBeenBottomElement->GetType()];
						if (lastBottomVariant != nullptr)
							pt.Y += lastBottomVariant->GetWidth();
				}

				PushGoDown();
				continue; //<- this continue is useless, becouse without it goes anyway to the end of the loop
			}
		}
		else //I can go more to the right
		{
			Variant* var = configuration[currentNode->GetType()];
			if (currentNode->GetType() == nullptr) //startNode
			{
				suggestedPt.X = 0; suggestedPt.Y = 0;

			}
			else
			{
				suggestedPt = plane[currentNode->GetType()]->TopRight();
				if (currentRightIndex > 0)
				{
					Type* lastBottom = currentNode->GetRightNodes()[currentRightIndex - 1]->GetType();
					suggestedPt.Y = plane[lastBottom]->BottomLeft().Y;
				}

				if (currentRightIndex == currentNode->GetRightNodes().size()-1)
				{
					auto downMostLeftTop = currentNode->GetDownNodes()[currentNode->GetDownNodes().size() - 1]->GetRightNodes()[0];
					if (downMostLeftTop == currentNode->GetRightNodes()[currentRightIndex])
					{
						//Small Rabbit hole
					}
				}
			}

			PushGoRight();
			continue; //<- this continue is useless, becouse without it goes anyway to the end of the loop
		}
	}
}

void RectanglePlacer::GotoParent()
{
	currentNode = parentPtrs.top().node;
	currentRightIndex = parentPtrs.top().rightIndex;
	currentDownIndex = parentPtrs.top().downIndex;
	parentPtrs.pop();
}


RectanglePlacer::RectanglePlacer(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration) : pt(0,0), suggestedPt(0,0)
{
	this->blankVariant = new Variant(0, 0, nullptr);
	this->startNode = start_H_Node;
	this->configuration = variantConfiguration;
}

void RectanglePlacer::PushGoRight()
{
	parentPtrs.push(Parent(currentNode, currentRightIndex + 1, currentDownIndex));
	currentNode = currentNode->GetRightNodes()[currentRightIndex];
	currentRightIndex = 0;
	currentDownIndex = 0;
}

void RectanglePlacer::PushGoDown()
{
	parentPtrs.push(Parent(currentNode, currentRightIndex, currentDownIndex + 1));
	currentNode = currentNode->GetDownNodes()[currentDownIndex];
	currentRightIndex = 0;
	currentDownIndex = 0;
}

void RectanglePlacer::CreateRectangle()
{
	Variant* var = configuration[currentNode->GetType()];
	if (var == nullptr)
		var = this->blankVariant;
	VariantRectangle* rect = nullptr; //TODO: position

	if (currentNode->GetRightNodes()[0] == lastBottomVar)
	{
		if (currentNode->GetRightNodes().size() == 1)
		{
			rect = new VariantRectangle(var, suggestedPt.X - var->GetWidth(), pt.Y);
		}
		else
		{ // is on the border
			//use a bit moved pt
			//TODO: calculate the better position
			rect = new VariantRectangle(var, suggestedPt.X, suggestedPt.Y);
		}
	}
	else
	{
		//use sugested pt
		rect = new VariantRectangle(var, suggestedPt.X - var->GetWidth(), suggestedPt.Y);
	}
	this->plane[currentNode->GetType()] = rect;
}

RectanglePlacer::~RectanglePlacer()
{
	this->startNode = nullptr;
}


std::map<Type*, VariantRectangle*> RectanglePlacer::GetPlacedRectangles()
{
	AddRectangles();

	return this->plane;
}

bool RectanglePlacer::allowedToGoDown()
{	
	//If the element has nothing on the left it can be considered, bc otherwise the created later rectangle would be in the wrong place
	if (currentNode->GetDownNodes()[currentDownIndex]->left[0]->isEndNode()) 
		return true;


	for (auto right : parentPtrs.top().node->GetRightNodes())
		if (currentNode->GetDownNodes()[currentDownIndex] == right)
			return true;

	return false;
}

} //namespace FPA

