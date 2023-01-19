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

unsigned PlacementGraph::calculateGGraph(std::map<Type*, VariantRectangle*>& plane)
{
	int Gmin = INT32_MAX, Gmax = 0;

	for (auto& starter : G_start->down)
	{
		if (plane[starter->GetType()]->TopLeft().Y < Gmin)
			Gmin = plane[starter->type]->TopLeft().Y;
	}

	for (auto& ender : G_end->up)
	{
		if (plane[ender->GetType()]->BottomLeft().Y > Gmax)
			Gmax = plane[ender->GetType()]->BottomLeft().Y;
	}
	return Gmax - Gmin;
}
unsigned PlacementGraph::calculateHGraph(std::map<Type*, VariantRectangle*>& plane)
{
	int Hmin = INT32_MAX, Hmax = 0;

	for (auto& starter : H_start->right)
	{
		if (plane[starter->GetType()]->TopLeft().X < Hmin)
			Hmin = plane[starter->type]->TopLeft().X;
	}

	for (auto& ender : H_end->left)
	{
		if (plane[ender->GetType()]->TopRight().X > Hmax)
			Hmax = plane[ender->GetType()]->TopRight().X;
	}
	return Hmax - Hmin;
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
	// Steps:
	// 1. Create plane of rectangles and place them correctly
	// 2. Calculate 'G graph'
	// 3. Calculate 'H graph'

	// I think calculating the graphs will be super easy.
	// E.g. for the H graph just check which element is the most left by comparing element from the 'right' vector of H_start
	// and which element is the most right by comparing elements from the 'left' vector of H_end

	std::map<Type*, VariantRectangle*> rectanglePlane = this->CreateAndPlaceRectangles(configuration); //<Todo

	auto G = this->calculateGGraph(rectanglePlane);
	auto H = this->calculateHGraph(rectanglePlane);

	return std::pair<unsigned, unsigned>(G, H); //G, H
}
std::map<Type*, VariantRectangle*> PlacementGraph::CreateAndPlaceRectangles(std::vector<Variant*> configuration)
{
	if (G_start == nullptr)
		throw "Uninitialized graph";

	//TODO

	return std::map<Type*, VariantRectangle*>();
}
} //namespace FPA
