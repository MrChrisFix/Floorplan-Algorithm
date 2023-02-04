#pragma once
#include <vector>
#include "Type.h"

namespace FPA {

/**
 * Class representing a node in the graph
*/
class GraphNode
{
	friend class PlacementGraph;
	friend class RectanglePlacer;

private:
	std::vector<GraphNode*> up;		///Vector with the nodes that are up
	std::vector<GraphNode*> left;	///Vector with the nodes that are to the left
	std::vector<GraphNode*> down;	///Vector with the nodes that are down
	std::vector<GraphNode*> right;	///Vector with the nodes that are to the right

	Type* type;						///The type the node is representing

	bool isRoot;					///Indication if the node is the root node
	bool isEnd;						///Indication if the node is the last node (most left in H and most down in G)

public:
	/**
	 * Constructor for root and end node
	 * @param isRoot true -> root; false -> end
	 * @param is_H_Graph Which attribute (height or width) should be used for calculations
	*/
	GraphNode(bool isRoot);

	/**
	 * Constructor for a regular node
	 * @param theType The type the node should represent
	 * @param is_H_Graph Which attribute (height or width) should be used for calculations
	*/
	GraphNode(Type* theType);
	/**
	 * Destructor 
	*/
	~GraphNode();

	/**
	 * Adds given node to the vector of the given side.
	 * The method also adds the invoked node in the opposite side vector of the given node
	 * @param node The node to add
	*/
	void ConnectWithNode(GraphNode* node, SIDE side);

	/**
	 * Getter for the type
	 * @return The assigned type of the Node 
	*/
	Type* GetType();

	/**
	 * Getter for nodes on the right
	 * @return reference to this->right
	*/
	std::vector<GraphNode*>& GetRightNodes();

	/**
	 * Getter for nodes on down
	 * @return reference to this->down
	*/
	std::vector<GraphNode*>& GetDownNodes();

	/**
	 * Boolean for getting the info if the node is an end node
	 * @return Is the node an end node
	*/
	bool isEndNode();

	/**
	 * Boolean for getting the info if the node is a start node
	 * @return Is the node an start node
	*/
	bool isStartNode();

private:

	/**
	 * Getter for the vector of the given SIDE
	 * @param side the SIDE of whoose vector should be given
	 * @return Reference to the vector of the given SIDE
	*/
	std::vector<GraphNode*>& GetVectorBySide(SIDE side);

	/**
	 * Getter for the vector of the opposite side of the given SIDE
	 * @param side the SIDE of whoose oposite vector should be given
	 * @return Reference to the vector of the opposite SIDE
	*/
	std::vector<GraphNode*>& GetVectorByOppsiteSide(SIDE side);

};

} //namespace FPA
