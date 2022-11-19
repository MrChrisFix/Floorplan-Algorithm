#pragma once
#include <vector>
#include "Type.h"

/// <summary>
/// The graphs G and H are used to calculate the height and width costs respectivly.
/// </summary>
class GraphNode
{
private:
	std::vector<GraphNode*> next;
	std::vector<GraphNode*> prev;

	Type* type;

	bool isRoot;
	bool isEnd;
	bool calcHeight;

public:
	GraphNode(bool isRoot, bool is_H_Graph);			//<- Root & End constructor
	GraphNode(Type* theType, bool is_H_Graph);			//<- Node constructor
	~GraphNode();

	//Adds child in the 'next' vector
	void AddNodeToGraph(GraphNode* node);		

	unsigned int calculateCost(std::vector<Variant*> combination) const;
	
	GraphNode* FindNodeByType(Type* searched);

	Type* GetType();

private:
	unsigned GoThroughBranch(std::vector<Variant*>& combination) const;
	void removeChildNode(GraphNode* node);
};

