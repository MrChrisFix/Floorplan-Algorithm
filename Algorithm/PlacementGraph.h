#pragma once
#include "GraphNode.h"
#include <map>
#include "VariantRectangle.h"

namespace FPA {

class PlacementGraph
{
private:
	GraphNode *G_start, *G_end, *H_start, *H_end;

	std::map<Type*, GraphNode*> TypeLookup;

	unsigned calculateGGraph(std::map<Type*, VariantRectangle*> &plane);
	unsigned calculateHGraph(std::map<Type*, VariantRectangle*> &plane);

	unsigned calculateUncompleteGGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode);
	unsigned calculateUncompleteHGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode);

	void changeOrdersOnSites();
	void correctLeftRight(GraphNode* node, std::vector<GraphNode*>& dirVec);
	void correctTopBottom(GraphNode* node, std::vector<GraphNode*> &dirVec);

public:
	PlacementGraph();
	~PlacementGraph();

	void CreateGraph(std::vector<Type*> types);

	std::pair<unsigned, unsigned> CalculateCost(std::map<Type*, Variant*> &configuration);

	std::map<Type*, VariantRectangle*> GetRectanglePlane(std::map<Type*, Variant*> configuration);
};

} //namespace FPA
