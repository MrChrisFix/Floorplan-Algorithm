#pragma once
#include "GraphNode.h"
#include <map>
#include "VariantRectangle.h"

namespace FPA {

class PlacementGraph
{
private:
	GraphNode *G_start, *G_end, *H_start, *H_end;	/// Node, which is on the edge and has no type

	std::map<Type*, GraphNode*> TypeLookup;			/// A lookup table for GraphNodes based on the Type

	/**
	 * Method for calculating the cost of the G graph based on the plane of rectangles
	 * @param plane Plane of VariantRectangles
	 * @return The cost of the G graph
	*/
	unsigned calculateGGraph(std::map<Type*, VariantRectangle*> &plane);

	/**
	 * Method for calculating the cost of the H graph based on the plane of rectangles
	 * @param plane Plane of VariantRectangles
	 * @return The cost of the H graph
	*/
	unsigned calculateHGraph(std::map<Type*, VariantRectangle*> &plane);

	/**
	 * @brief Rerccurencial method for calculating the cost of the G graph and uncomplete configuration
	 * @param configuration Configuration of variants
	 * @param startNode The next node in recurency
	 * @return The cost of the G graph 
	*/
	unsigned calculateUncompleteGGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode);

	/**
	 * @brief Rerccurencial method for calculating the cost of the H graph and uncomplete configuration
	 * @param configuration Configuration of variants
	 * @param startNode The next node in recurency
	 * @return The cost of the H graph
	*/
	unsigned calculateUncompleteHGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode);

	/**
	 * Corrects the order in which GraphNodes are connected
	*/
	void changeOrdersOnSites();

	/**
	 * @brief Correts the order of the given node on the left or right based on the passed vector
	 * @param node The node on which the side should be corrected
	 * @param dirVec The side vector of the node
	*/
	void correctLeftRight(GraphNode* node, std::vector<GraphNode*>& dirVec);

	/**
	 * @brief Correts the order of the given node's top and bottom based on the passed vector
	 * @param node he node on which the side should be corrected
	 * @param dirVec The side vector of the node
	*/
	void correctTopBottom(GraphNode* node, std::vector<GraphNode*> &dirVec);

public:
	/**
	 * @brief Constructor
	*/
	PlacementGraph();

	/**
	 * Destructor
	*/
	~PlacementGraph();

	/**
	 * Creates the graph based on the type vector
	 * @param types Type vector of which a graph should be created
	*/
	void CreateGraph(std::vector<Type*> types);

	/**
	 * Calculates the cost of the given configuration
	 * @param configuration The configuration of variants
	 * @return A pair which contains the height and width of the configuration
	*/
	std::pair<unsigned, unsigned> CalculateCost(std::map<Type*, Variant*> &configuration);

	/**
	 * Getter for the plane of rectangles based on the given configuration and created graph
	 * @param configuration The configuration of Variants which should be used to create the plane
	 * @return A map of VariantRectabgles with the keys beeing the Type
	*/
	std::map<Type*, VariantRectangle*> GetRectanglePlane(std::map<Type*, Variant*> configuration);
};

} //namespace FPA
