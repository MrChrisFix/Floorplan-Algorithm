#pragma once
#include "GraphNode.h"
#include <map>

namespace FPA {

class PlacementGraph
{
private:
	GraphNode *G_start, *G_end, *H_start, *H_end;

	std::map<Type*, GraphNode*> TypeLookup;


public:
	PlacementGraph();
	~PlacementGraph();

	void CreateGraph(std::vector<Type*> types);

	std::pair<unsigned, unsigned> CalculateCost(std::vector<Variant*> configuration); //WARNING: first is G, second is H

};

} //namespace FPA
