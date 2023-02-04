#pragma once
#include <map>
#include <stack>
#include "VariantRectangle.h"
#include "GraphNode.h"

namespace FPA
{
/**
 * Class for placing VariantRectangles based on PlacementGraph and variant configuration
*/
class RectanglePlacer
{
private:
	/**
	 * Helper struct, which holds inforamtions about a node
	*/
	struct Parent {
		GraphNode* node;
		int rightIndex;
		int downIndex;
		Parent(GraphNode* nodeptr, int nextRight, int nextDown) : node(nodeptr), rightIndex(nextRight), downIndex(nextDown) {};
	};

	std::map<Type*, VariantRectangle*> plane;		/// Holds the plane of currently placed rectangles
	GraphNode* startNode = nullptr;					/// The starting node of a graph
	std::map<Type*, Variant*> configuration;		/// Given configuration of Variants
	Variant* blankVariant = nullptr;				/// A variant, that has the width and height equal 0
	GraphNode* lastBottomVar = nullptr;				/// Helper poiter for remembering a GraphNode in a specific situation

	//Managing
	std::stack<Parent> parentPtrs;					/// Stack of Parents, which holds all created rectangels before currentnode
	GraphNode* currentNode = nullptr;				/// The grapNode of the currenctly created rectangle
	int currentRightIndex = 0;						/// Index of the current node, that is created on the right
	int currentDownIndex = 0;						/// Index of the current node, that is created ti the down

	Point pt;										/// Point for creating next rectangle
	Point suggestedPt;								/// Point for creating next rectangle

	/**
	 * The main method of the class. It runs a while loop until all rectangles are placed.
	*/
	void AddRectangles();

	/**
	 * Changes the current node to the node that was used previously
	*/
	void GotoParent();

	/**
	 * Changes the current node to the node on the right described by currentRightIndex
	*/
	void PushGoRight();

	/**
	 * Changes the current node to the node down described by currentDownIndex
	*/
	void PushGoDown();

	/**
	 * Creates a new rectangle and inserts it into the plane. The creation is based on pt and suggestedPt
	*/
	void CreateRectangle();

	/**
	 * Checks if currentNode can be set to the node down
	 * @return Boolean
	*/
	bool allowedToGoDown();

	/**
	 * Checks if the given configuraion is possible
	 * @return Boolean. True if everythig is right, otherwise false
	*/
	bool goodConfigurationState();

	/**
	 * @brief Checks if the variant of the given type can be parent of all it's requirements
	 * @param type The type of the checked variant
	 * @return Boolean. True if it's ok, otherwise false
	*/
	bool willFitAllElements(Type* type);

	/**
	 * Calculates the best top left position of the next added rectangle on the right
	*/
	void calcSuggestedPtRight();

	/**
	 * Calculates the best top left position of the next down added rectangle
	*/
	void calcSuggestedPtDown();

	/**
	 * Checks if any rectangle on the plane is intersecting
	 * @return Boolean. True if any rectanle is intersecting with another one. False if nothing is intersecting.
	*/
	bool isAnythingIntersecting();


public:
	/**
	 * Constructor.
	 * @param start_H_Node 
	 * @param variantConfiguration 
	*/
	RectanglePlacer(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration);

	/**
	 * Desctructor
	*/
	~RectanglePlacer();

	/**
	 * @brief 
	 * @return 
	*/
	std::map<Type*, VariantRectangle*> GetPlacedRectangles();
};

} //namespace FPA

