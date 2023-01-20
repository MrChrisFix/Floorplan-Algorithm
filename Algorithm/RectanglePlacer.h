#pragma once
#include <map>
#include "VariantRectangle.h"
#include "GraphNode.h"

namespace FPA
{

class RectanglePlacer
{
private:
	std::map<Type*, VariantRectangle*> plane;
	GraphNode* startNode;
	std::map<Type*, Variant*> configuration;
	Variant* blankVariant; //TODO: somehow manage memory of this object

	void AddNextRect(int tlX, int tlY, GraphNode* node);

public:
	RectanglePlacer();
	~RectanglePlacer();

	std::map<Type*, VariantRectangle*> PlaceRectangles(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration);
};

} //namespace FPA

