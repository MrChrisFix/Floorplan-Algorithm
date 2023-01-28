#pragma once
#include <map>
#include <stack>
#include "VariantRectangle.h"
#include "GraphNode.h"

namespace FPA
{

class RectanglePlacer
{
private:
	struct Parent {
		GraphNode* node;
		int rightIndex;
		int downIndex;
		Parent(GraphNode* nodeptr, int nextRight, int nextDown) : node(nodeptr), rightIndex(nextRight), downIndex(nextDown) {};
	};

	std::map<Type*, VariantRectangle*> plane;
	GraphNode* startNode;
	std::map<Type*, Variant*> configuration;
	Variant* blankVariant; //TODO: somehow manage memory of this object
	GraphNode* lastBottomVar = nullptr;

	//Managing
	std::stack<Parent> parentPtrs;
	GraphNode* currentNode;
	int currentRightIndex = 0;
	int currentDownIndex = 0;

	Point pt;
	Point suggestedPt;

	void AddRectangles();
	void GotoParent();
	void PushGoRight();
	void PushGoDown();
	void CreateRectangle();
	bool allowedToGoDown();


public:
	RectanglePlacer(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration);
	~RectanglePlacer();

	std::map<Type*, VariantRectangle*> GetPlacedRectangles();
};

} //namespace FPA

