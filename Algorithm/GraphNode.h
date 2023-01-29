#pragma once
#include <vector>
#include "Type.h"

namespace FPA {

/**
 * The graphs G and H are used to calculate the height and width costs respectivly. 
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
	 * Getter
	 * @return The assigned type of the Node 
	*/
	Type* GetType();

	std::vector<GraphNode*>& GetRightNodes();
	std::vector<GraphNode*>& GetDownNodes();
	bool isEndNode();
	bool isStartNode();

private:

	std::vector<GraphNode*>& GetVectorBySide(SIDE side);
	std::vector<GraphNode*>& GetVectorByOppsiteSide(SIDE side);

};

} //namespace FPA
