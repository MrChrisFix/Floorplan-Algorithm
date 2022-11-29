#pragma once
#include <vector>
#include "Type.h"

/**
 * The graphs G and H are used to calculate the height and width costs respectivly. 
*/
class GraphNode
{
private:
	std::vector<GraphNode*> next;	///Vector with the nodes that are to the left(H) or down(G)
	std::vector<GraphNode*> prev;	///Vector with the nodes that are to the right(H) or up(G)

	Type* type;						///The type the node is representing

	bool isRoot;					///Indication if the node is the root node
	bool isEnd;						///Indication if the node is the last node (most left in H and most down in G)
	bool calcHeight;				///Which attribute (height or width) should be used for calculations

public:
	/**
	 * Constructor for root and end node
	 * @param isRoot true -> root; false -> end
	 * @param is_H_Graph Which attribute (height or width) should be used for calculations
	*/
	GraphNode(bool isRoot, bool is_H_Graph);

	/**
	 * Constructor for a regular node
	 * @param theType The type the node should represent
	 * @param is_H_Graph Which attribute (height or width) should be used for calculations
	*/
	GraphNode(Type* theType, bool is_H_Graph);
	/**
	 * Destructor 
	*/
	~GraphNode();

	/**
	 * Adds given node to the 'next' vector.
	 * The method also adds the invoked node in the 'prev' vector of the given node
	 * @param node The node to add
	*/
	void AddNodeToGraph(GraphNode* node);		

	/**
	 * Caltulationg the cost of the invoked graph and the given Variant configuration
	 * @param combination A vector containing the configuration of Variants
	 * @return The maximal cost of the configuration (height or width)
	*/
	unsigned int calculateCost(std::vector<Variant*> combination) const;
	
	/**
	 * Finding a node of the given Type
	 * @param searched The type which is searched
	 * @return A pointer to the Node
	*/
	GraphNode* FindNodeByType(Type* searched);

	/**
	 * Getter
	 * @return The assigned type of the Node 
	*/
	Type* GetType();

private:
	/**
	 * Private method used in cost calculation
	 * @param combination A vector containing the configuration of Variants
	 * @return The maximal cost of the configuration (height or width)
	*/
	unsigned GoThroughBranch(std::vector<Variant*>& combination) const;
	/**
	 * Private method used to remove the given node from the 'next' vector. It's used in the destructor.
	 * @param node The node to remove
	*/
	void removeChildNode(GraphNode* node);
};

