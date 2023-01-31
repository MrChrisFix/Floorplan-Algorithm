#include "PlacementGraph.h"
#include "RectanglePlacer.h"
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
	if (H_start != nullptr)
		delete H_start;
	//H_end should be deleted by H_start
	if (G_start != nullptr)
		delete G_start;
	if (G_end != nullptr)
		delete G_end;
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
			node->ConnectWithNode(H_start, SIDE::LEFT);
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
			node->ConnectWithNode(H_end, SIDE::RIGHT);


		if (type->down.empty())
			node->ConnectWithNode(G_end, SIDE::DOWN);
		else
		{
			for (auto& down : type->down)
			{
				if (TypeLookup[down] != nullptr)
				{
					node->ConnectWithNode(TypeLookup[down], SIDE::DOWN);
					continue;
				}
				auto childNode = new GraphNode(down);
				TypeLookup[down] = childNode;
				node->ConnectWithNode(childNode, SIDE::DOWN);
			}
		}
		if (type->up.empty())
			node->ConnectWithNode(G_start, SIDE::UP);
	}
}

std::pair<unsigned, unsigned> PlacementGraph::CalculateCost(std::map<Type*, Variant*> configuration)
{
	std::map<Type*, VariantRectangle*> rectanglePlane = GetRectanglePlane(configuration);
	if (rectanglePlane.empty())
	{
		return std::pair<unsigned, unsigned>(-1, -1);
	}


	auto G = this->calculateGGraph(rectanglePlane);
	auto H = this->calculateHGraph(rectanglePlane);

	return std::pair<unsigned, unsigned>(G, H);
}

std::map<Type*, VariantRectangle*> PlacementGraph::GetRectanglePlane(std::map<Type*, Variant*> configuration)
{
	RectanglePlacer placer(this->H_start, configuration);

	std::map<Type*, VariantRectangle*> rectanglePlane = placer.GetPlacedRectangles();

	return rectanglePlane;
}

} //namespace FPA

