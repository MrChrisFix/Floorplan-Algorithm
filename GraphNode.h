#pragma once
#include <vector>
#include "Type.h"

/// <summary>
/// The graphs G and H are used to calculate the height and width costs respectivly.
/// </summary>
class GraphNode
{
	std::vector<GraphNode*> next;
	std::vector<GraphNode*> prev;

	Type* type;

	bool isRoot;
	bool isEnd;
	bool calcHeight;

	unsigned GoThroughBranch(std::vector<Variant> &combination) const;

public:
	GraphNode(bool isRoot, bool countHeight);			//<- Root & End constructor
	GraphNode(Type* theType, bool countHeight);			//<- Node constructor
	~GraphNode();

	void AddNodeToGraph(GraphNode* node);

	unsigned int calculateCost(std::vector<Variant> combination) const;


};

