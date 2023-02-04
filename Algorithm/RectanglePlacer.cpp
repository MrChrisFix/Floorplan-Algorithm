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
			//Go down
			if (currentNode->GetDownNodes().size() <= currentDownIndex || currentNode->GetDownNodes()[0]->isEndNode()) //Also did everything down
			{//In this case I should go back to the parent
				
				if (parentPtrs.empty())
					break;

				GotoParent();
			}
			else //I can go more down
			{
				if (!allowedToGoDown())
				{
					lastBottomVar = currentNode;
					GotoParent();
				}
				else
				{
					calcSuggestedPtDown();
					PushGoDown();
				}
				
			}
		}
		else //I can still go to the right
		{
			calcSuggestedPtRight();
			PushGoRight();
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
	VariantRectangle* rect = nullptr;

	if (currentNode->GetRightNodes()[0] == lastBottomVar)
	{
		if (currentNode->GetRightNodes().size() == 1)
		{
			rect = new VariantRectangle(var, suggestedPt.X, pt.Y);
		}
		else
		{ // is on the border
			int freeSpaceUp = suggestedPt.Y - pt.Y;
			if (freeSpaceUp > var->GetHeight())
			{
				rect = new VariantRectangle(var, suggestedPt.X - var->GetWidth(), suggestedPt.Y + 1 - var->GetHeight());
			}
			else
				rect = new VariantRectangle(var, suggestedPt.X - var->GetWidth(), pt.Y);
		}
	}
	else
	{
		//use sugested pt
		rect = new VariantRectangle(var, suggestedPt.X, suggestedPt.Y);
	}
	this->plane[currentNode->GetType()] = rect;
}

RectanglePlacer::~RectanglePlacer()
{
	this->startNode = nullptr;
}


std::map<Type*, VariantRectangle*> RectanglePlacer::GetPlacedRectangles()
{
	if (goodConfigurationState())
	{
		currentNode = startNode;
		AddRectangles();
	}

	return this->plane;
}

bool RectanglePlacer::allowedToGoDown()
{	
	//The Element can be considered if the it has nothing on the left, bc otherwise the created later rectangle would be in the wrong place
	if (currentNode->GetDownNodes()[currentDownIndex]->left[0]->isStartNode()) 
		return true;

	//Bottom has a parent up that's left of current 
	{
		auto& UpsFromDown = currentNode->GetDownNodes()[currentDownIndex]->up;
		auto currBottomLeft = currentNode->left.back();
		if (UpsFromDown.back() == currentNode && UpsFromDown.size() > 1 && UpsFromDown[UpsFromDown.size() - 2] == currBottomLeft)
			return true;
	}
	

	return false;
}

bool RectanglePlacer::willFitAllElements(Type* type)
{
	//Checks if N-1 elements fit on the side, so that the N-th element can also fit and eventually be much oversized

	Variant* nodeVariant = configuration[type];
	if (nodeVariant == nullptr)
		return true;


	int rightVariantsHeight = 0;
	int downVariantsWidth = 0;
	for (int i=0; i< type->right.size()-2 && type->right.size() > 1; i++)
	{
		Variant* var = configuration[type->right[i]];
		if (var != nullptr)
		{
			rightVariantsHeight += var->GetHeight();
		}
	}
	for (int i=0; i< type->down.size()-2 && type->down.size() >1; i++)
	{
		Variant* var = configuration[type->down[i]];
		if (var != nullptr)
		{
			downVariantsWidth += var->GetWidth();
		}
	}

	//TODO!!! WARNING!!!: This doens't take in consideration the elements, that are on the border

	//TODO: another test: if dimension is sizeof 1 and mus be on the border

	return (rightVariantsHeight < nodeVariant->GetHeight() && downVariantsWidth < nodeVariant->GetWidth());
}

void RectanglePlacer::calcSuggestedPtRight()
{
	if (currentNode->GetType() == nullptr) //startNode
	{
		suggestedPt.X = 0; suggestedPt.Y = 0;
	}
	else
	{
		suggestedPt = pt = plane[currentNode->GetType()]->TopRight();
		if (currentRightIndex > 0)
		{
			Type* lastBottom = currentNode->GetRightNodes()[currentRightIndex - 1]->GetType();
			suggestedPt.Y = plane[lastBottom]->BottomLeft().Y;
		}

		//Check if the most down right is shared with the element down most right - ergo 2 on left sharing 1 on right
		if (currentRightIndex == currentNode->GetRightNodes().size() - 1)
		{
			GraphNode* downMostLeftTop = currentNode->GetDownNodes().back()->GetRightNodes().size() > 0 ?
				currentNode->GetDownNodes().back()->GetRightNodes()[0] : nullptr;

			if (downMostLeftTop == currentNode->GetRightNodes()[currentRightIndex])
			{
				//if the right is bigger than me and bottom, set normally, otherwise set as much inside me and the rest beside over bottom

				Variant* BottomRightVar = configuration[currentNode->GetRightNodes().back()->GetType()];
				int myRemainingHeight = plane[currentNode->GetType()]->BottomRight().Y - suggestedPt.Y;

				if (BottomRightVar != nullptr && BottomRightVar->GetHeight() < myRemainingHeight && BottomRightVar->GetHeight() > 1)
				{
					suggestedPt.Y = plane[currentNode->GetType()]->BottomRight().Y + 1 - BottomRightVar->GetHeight();
				}

			}
		}
	}
}

void RectanglePlacer::calcSuggestedPtDown()
{
	if (lastBottomVar != nullptr)
	{
		suggestedPt = plane[lastBottomVar->GetType()]->BottomLeft();
		if (configuration[currentNode->GetDownNodes()[currentDownIndex]->GetType()] != nullptr)
			suggestedPt.X -= configuration[currentNode->GetDownNodes()[currentDownIndex]->GetType()]->GetWidth(); //Could backfire, not tested enough
	}
	else
		suggestedPt = plane[currentNode->GetType()]->BottomLeft();

	pt = plane[currentNode->GetType()]->BottomLeft();

	if (currentDownIndex > 0)
	{
		Type* lastRight = currentNode->GetDownNodes()[currentDownIndex - 1]->GetType();
		suggestedPt.X = plane[lastRight]->TopLeft().X;
	}
	else if (!currentNode->left.back()->isStartNode() && currentNode->GetDownNodes()[0] == currentNode->left.back()->GetDownNodes().back())
	{
		if (currentNode->left.back()->GetDownNodes().size() == 1)
		{
			suggestedPt.X = plane[currentNode->left.back()->GetType()]->BottomLeft().X;
		}
		else
			suggestedPt.X = plane[currentNode->GetType()]->BottomLeft().X - 1;

		if (plane[currentNode->left.back()->GetType()] != nullptr &&
			plane[currentNode->left.back()->GetType()]->BottomRight().Y >
			plane[currentNode->GetType()]->BottomLeft().Y)
		{
			suggestedPt.Y = plane[currentNode->left.back()->GetType()]->BottomRight().Y;

		}
	}
}

bool RectanglePlacer::goodConfigurationState()
{
	for (auto& element : this->configuration)
	{
		if (!willFitAllElements(element.first))
			return false;
	}

	return true;
}

} //namespace FPA

