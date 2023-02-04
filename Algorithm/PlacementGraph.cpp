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

unsigned PlacementGraph::calculateUncompleteGGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode)
{
	if (startNode->isEnd)
		return 0;

	unsigned max = 0;
	for (auto node : startNode->down)
	{
		unsigned myCost = 0;
		if (!node->isRoot)
		{
			Variant* var = configuration[node->GetType()];
			if(var != nullptr)
				myCost = var->GetHeight();
		}
		unsigned cost = calculateUncompleteGGraph(configuration, node) + myCost;
		if (cost > max)
			max = cost;
	}

	return max;
}

unsigned PlacementGraph::calculateUncompleteHGraph(std::map<Type*, Variant*>& configuration, GraphNode* startNode)
{
	if (startNode->isEnd)
		return 0;

	unsigned max = 0;
	for (auto node : startNode->right)
	{
		unsigned myCost = 0;
		if (!node->isRoot)
		{
			Variant* var = configuration[node->GetType()];
			if (var != nullptr)
				myCost = var->GetWidth();
		}
		unsigned cost = calculateUncompleteHGraph(configuration, node) + myCost;
		if (cost > max)
			max = cost;
	}

	return max;
}

void PlacementGraph::changeOrdersOnSites()
{
	for (auto& graph : this->TypeLookup)
	{
		if(graph.second->up.size() > 1)
		{
			correctTopBottom(graph.second, graph.second->up);
		}

		if(graph.second->left.size() > 1)
		{
			correctLeftRight(graph.second, graph.second->left);
		}

		if (graph.second->down.size() > 1)
		{
			correctTopBottom(graph.second, graph.second->down);
		}

		if (graph.second->right.size() > 1)
		{
			correctLeftRight(graph.second, graph.second->right);
		}
	}

}

void PlacementGraph::correctLeftRight(GraphNode* node, std::vector<GraphNode*>& dirVec)
{
	std::vector<GraphNode*> newVec;

	//1. Find the first
	for (int i = 0; i < dirVec.size(); i++)
	{
		bool found = true;
		auto current = dirVec[i];

		for (auto& di : dirVec)
		{
			auto id = std::find(current->up.begin(), current->up.end(), di);
			if (id != current->up.end())
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			newVec.push_back(current);
			break;
		}
	}

	// 2. Traverse now having an anchor point
	for (int i = 0; i < dirVec.size()-1; )
	{
		int old_i = i;
		for (auto& di : dirVec)
		{
			auto id = std::find(di->up.begin(), di->up.end(), newVec[i]);
			if (id != di->up.end())
			{
				newVec.push_back(di);
				i++;
				break;
			}
		}
		if (i == old_i)
			throw "Elements are not connected near element " + node->GetType()->GetName();
	}
	dirVec = newVec;
}

void PlacementGraph::correctTopBottom(GraphNode* node, std::vector<GraphNode*> &dirVec)
{
	std::vector<GraphNode*> newVec;

	//1. Find the first
	for (int i = 0; i < dirVec.size(); i++)
	{
		bool found = true;
		auto current = dirVec[i];

		for (auto& di : dirVec)
		{
			auto id = std::find(current->left.begin(), current->left.end(), di);
			if (id != current->left.end())
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			newVec.push_back(current);
			break;
		}
	}

	// 2. Traverse now having an anchor point
	for (int i = 0; i < dirVec.size()-1; )
	{
		int old_i = i;
		for (auto& di : dirVec)
		{
			auto id = std::find(di->left.begin(), di->left.end(), newVec[i]);
			if (id != di->left.end())
			{
				newVec.push_back(di);
				i++;
				break;
			}
		}
		if (i == old_i)
			throw "Elements are not connected near element " + node->GetType()->GetName();
	}
	dirVec = newVec;
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

	changeOrdersOnSites();
}

std::pair<unsigned, unsigned> PlacementGraph::CalculateCost(std::map<Type*, Variant*> &configuration)
{
	unsigned G = -1, H = -1;
	if (configuration.size() < TypeLookup.size())
	{
		auto copy = configuration; //The copy is added, becouse the conf is passed by reference (for speed) and is obscured by it
		G = this->calculateUncompleteGGraph(copy, G_start);
		H = this->calculateUncompleteHGraph(copy, H_start);
	}
	else
	{
		std::map<Type*, VariantRectangle*> rectanglePlane = GetRectanglePlane(configuration);
		if (rectanglePlane.empty())
		{
			G = -1;
			H = -1;
		}
		else
		{
			G = this->calculateGGraph(rectanglePlane);
			H = this->calculateHGraph(rectanglePlane);

			for (auto& rect : rectanglePlane)
				delete rect.second;
		}

	}

	return std::pair<unsigned, unsigned>(G, H);
}

std::map<Type*, VariantRectangle*> PlacementGraph::GetRectanglePlane(std::map<Type*, Variant*> configuration)
{
	RectanglePlacer placer(this->H_start, configuration);

	std::map<Type*, VariantRectangle*> rectanglePlane = placer.GetPlacedRectangles();

	return rectanglePlane;
}

} //namespace FPA

