#include "PlacementGraph.h"
namespace FPA {

PlacementGraph::PlacementGraph()
{
	G_start = nullptr;
	G_end = nullptr;
	H_start = nullptr;
	H_end = nullptr;
}

PlacementGraph::~PlacementGraph()
{
	if (G_start != nullptr)
		delete G_start;
	//G_end should be deleted by G_start
	if (H_start != nullptr)
		delete H_start;
	if (H_end != nullptr)
		delete H_end;
}

void PlacementGraph::CreateGraph(std::vector<Type*> types)
{
	if (types.empty()) 
		throw "The type vector is empty";

	G_start = new GraphNode(true);
	G_end = new GraphNode(false);
	H_start = new GraphNode(true);
	H_end = new GraphNode(false);

	for (auto& type : types)
	{
		GraphNode* node = TypeLookup[type];
		if (node == nullptr)
		{
			node = new GraphNode(type);
			TypeLookup[type] = node;
		}

		if (type->left.empty())
			node->ConnectWithNode(H_end, SIDE::LEFT);
		else
		{
			for (auto& left : type->left)
			{
				if (TypeLookup[left] != nullptr) // the node already exists
				{
					node->ConnectWithNode(TypeLookup[left], SIDE::LEFT);
					continue;
				}
				auto childNode = new GraphNode(left);
				TypeLookup[left] = childNode;
				node->ConnectWithNode(childNode, SIDE::LEFT);
			}
		}
		if (type->right.empty())
			node->ConnectWithNode(H_start, SIDE::RIGHT);

		//At this point every type should have it's node

		if (type->down.empty())
			node->ConnectWithNode(G_end, SIDE::DOWN);
		else
		{
			for (auto& down : type->down)
			{
				if (TypeLookup[down] == nullptr)
					throw "Types are wrong connected";
				node->ConnectWithNode(TypeLookup[down], SIDE::DOWN);
			}
		}
		if (type->up.empty())
			node->ConnectWithNode(G_start, SIDE::UP);
	}

}
std::pair<unsigned, unsigned> PlacementGraph::CalculateCost(std::vector<Variant*> configuration)
{
	return std::pair<unsigned, unsigned>(-1,-1);
}
} //namespace FPA
