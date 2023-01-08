#include "AlgorithmManager.h"

namespace FPA {

AlgorithmManager::AlgorithmManager()
{
	this->Graph_G = new GraphNode(true, true);
	this->Graph_H = new GraphNode(true, false);
	this->Graph_G_End = new GraphNode(false, true);
	this->Graph_H_End = new GraphNode(false, false);

	this->bestValue = -1;
	this->bestWidth = -1;
	this->bestHeight = -1;
	this->caltulateMultithread = false; //TODO: make as argument
}

AlgorithmManager::~AlgorithmManager()
{
	delete this->Graph_G;
	delete this->Graph_H;
}

ResultStruct AlgorithmManager::StartCalculations()
{
	auto start = std::chrono::system_clock::now();
	FixTypeConnections();
	auto fix = std::chrono::system_clock::now();
	PopulateGraphs();
	auto pop = std::chrono::system_clock::now();
	FindOptimal();
	auto end = std::chrono::system_clock::now();

	auto fix_us = std::chrono::duration_cast<std::chrono::microseconds>(fix - start).count();
	auto pop_us = std::chrono::duration_cast<std::chrono::microseconds>(pop - fix).count();
	auto otp_us = std::chrono::duration_cast<std::chrono::microseconds>(end - pop).count();
	auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	ResultStruct results;
	results.bestHeight = this->bestHeight;
	results.bestWidth = this->bestWidth;
	results.bestCombination = this->bestCombination;
	results.time_microsec = elapsed_us;

	return results;
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

void AlgorithmManager::FixTypeConnections()
{
	for (auto type : this->types)
	{
		Type* first, * second;

		if (type->right.size() < 2) 
			continue;

		//Stack top-bottom the types on the right
		auto& right = type->right;
		first = right[0];
		for (int i = 1; i < right.size(); i++)
		{
			second = right[i];
			first->AddRequirement('D', second, true);
			first = second;
		}

		if (type->down.size() < 2)
			continue;

		//Stack left-right the types on the bottom
		auto& down = type->down;
		first = down[0];
		for (int i = 1; i < down.size(); i++)
		{
			second = down[i];
			first->AddRequirement('R', second, true);
			first = second;
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

		unsigned G_Value = this->Graph_G->calculateCost(variantStack);
		unsigned H_Value = this->Graph_H->calculateCost(variantStack);
		
		if (G_Value * H_Value >= this->bestValue)
		{
			variantStack.pop_back();
			continue;
		}

		if (depth == this->types.size() - 1)
		{
			//unsigned G_Value = this->Graph_G->calculateCost(variantStack);
			//unsigned H_Value = this->Graph_H->calculateCost(variantStack);

			if (G_Value * H_Value < this->bestValue)
			{
				this->bestValue = G_Value * H_Value;
				this->bestHeight = G_Value;
				this->bestWidth = H_Value;
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

} //namespace FPA