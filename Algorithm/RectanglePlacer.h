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
	void AddRectangles();

	enum class Intersection{
		None,		// No intersecton
		Fully,		// Fully inside of one => technicly shouldn't be possible, becouse neighbouring elemment shuld be at least Side intersecting
		Side,		// Only one border is crossed
		Corner,		// Corner crossing each other
		Bullet,		// Two parrarel sides
		Half		// 3 sides are in each other; like Side but the opposite rectangle involved
	};

public:
	RectanglePlacer();
	~RectanglePlacer();

	std::map<Type*, VariantRectangle*> PlaceRectangles(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration);
};

} //namespace FPA

