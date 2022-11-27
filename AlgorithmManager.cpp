#include "AlgorithmManager.h"
#include "TreeNodeLeaf.h"

AlgorithmManager::AlgorithmManager()
{
	this->Graph_G = new GraphNode(true, true);
	this->Graph_H = new GraphNode(true, false);
	this->Graph_G_End = new GraphNode(false, true);
	this->Graph_H_End = new GraphNode(false, false);

	this->bestValue = -1;
	this->caltulateMultithread = true; //TODO: make as argument
}

AlgorithmManager::~AlgorithmManager()
{
	delete this->Graph_G;
	delete this->Graph_H;
}

std::pair<unsigned, std::vector<Variant*>> AlgorithmManager::StartCalculations()
{
	PopulateGraphs();
	FindOptimal();

	return std::pair<unsigned, std::vector<Variant*>>(this->bestValue, this->bestCombination);
}

void AlgorithmManager::setTypes(std::vector<Type*> Types)
{
	this->types = Types;
}

void AlgorithmManager::Populate_G_Graph(GraphNode* currentNode)
{
	auto currentType = currentNode->GetType();

	if (currentType == nullptr) throw;

	if (currentType->down.empty())
	{
		currentNode->AddNodeToGraph(this->Graph_G_End);
	}

	if (currentType->up.empty())
	{
		this->Graph_G->AddNodeToGraph(currentNode);
		return;
	}

	for (auto up : currentType->up)
	{
		auto foundUp = this->Graph_G->FindNodeByType(up); //is the type upwards already in the graph?
		if (foundUp != nullptr)
			foundUp->AddNodeToGraph(currentNode);
		else
		{
			GraphNode* newUp = new GraphNode(up, true);
			newUp->AddNodeToGraph(currentNode);
			Populate_G_Graph(newUp);
		}
	}
}

void AlgorithmManager::Populate_H_Graph(GraphNode* currentNode)
{
	auto currentType = currentNode->GetType();

	if (currentType == nullptr) throw;

	if (currentType->right.empty())
	{
		currentNode->AddNodeToGraph(this->Graph_H_End);
	}

	if (currentType->left.empty())
	{
		this->Graph_H->AddNodeToGraph(currentNode);
		return;
	}

	for (auto left : currentType->left)
	{
		auto foundLeft = this->Graph_H->FindNodeByType(left); //is the type on the left already in the graph?
		if (foundLeft != nullptr)
			foundLeft->AddNodeToGraph(currentNode);
		else
		{
			GraphNode* newLeft = new GraphNode(left, false);
			newLeft->AddNodeToGraph(currentNode);
			Populate_H_Graph(newLeft);
		}
	}
}

void AlgorithmManager::PopulateGraphs()
{
	for (auto type : this->types)
	{
		//Check if the type is already in the graphs
		if (this->Graph_G->FindNodeByType(type) != nullptr)
			continue;

		//G Graph
		auto newNode = new GraphNode(type, true);
		this->Populate_G_Graph(newNode);

		if (this->Graph_H->FindNodeByType(type) != nullptr)
			continue;

		//H Graph
		newNode = new GraphNode(type, false);
		this->Populate_H_Graph(newNode);
	}
}

void AlgorithmManager::FindOptimal()
{
	std::vector<Variant*> VariantStack;

	if (this->caltulateMultithread)
	{
		FindMultithread(0, VariantStack);
	}
	else
	{
		FindSinglethread(0, VariantStack);
	}
}

void AlgorithmManager::FindSinglethread(unsigned depth, std::vector<Variant*> variantStack)
{
	for (auto variant : this->types[depth]->GetVariants())
	{
		variantStack.push_back(variant);

		if (depth == this->types.size() - 1)
		{
			unsigned G_Value = this->Graph_G->calculateCost(variantStack);
			unsigned H_Value = this->Graph_H->calculateCost(variantStack);
			if (G_Value * H_Value < this->bestValue)
			{
				this->bestValue = G_Value * H_Value;
				this->bestCombination = variantStack;
			}
		}
		else if (depth < this->types.size())
		{
			FindSinglethread(depth + 1, variantStack); // Going deeper into the "tree"
		}

		variantStack.pop_back();
	}
}

void AlgorithmManager::FindMultithread(unsigned depth, std::vector<Variant*> variantStack)
{
	auto variantVector = this->types[depth]->GetVariants();
	unsigned short varAmount = variantVector.size();

	std::vector<std::thread> ThreadPool;

	for (int i = 0; i < varAmount; i++)
	{
		variantStack.push_back(variantVector[i]);

		if (i == varAmount - 1)
		{
			// Parent
			if (depth == this->types.size() - 1)
			{
				CalculateCosts(variantStack);
			}
			else
			{
				FindMultithread(depth + 1, variantStack);
			}
		}
		else
		{
			// Children
			if (depth == this->types.size() - 1)
			{
				ThreadPool.push_back(std::thread(&AlgorithmManager::CalculateCosts, this, variantStack));
			}
			else
			{
				ThreadPool.push_back(std::thread(&AlgorithmManager::FindMultithread, this, depth + 1, variantStack));
			}
		}
		variantStack.pop_back();
	}

	for (auto& thread : ThreadPool)
	{
		if(thread.joinable())
			thread.join();
	}

}

void AlgorithmManager::CalculateCosts(std::vector<Variant*> variantStack)
{
	unsigned G_Value = this->Graph_G->calculateCost(variantStack);
	unsigned H_Value = this->Graph_H->calculateCost(variantStack);
	auto value = G_Value * H_Value;

	this->guard.lock();
	if (this->bestValue > value)
	{
		this->bestValue = value;
		this->bestCombination = variantStack;
	}
	this->guard.unlock();
}
