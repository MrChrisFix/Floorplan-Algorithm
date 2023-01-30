#include "AlgorithmManager.h"

namespace FPA {

AlgorithmManager::AlgorithmManager()
{
	this->Graphs = new PlacementGraph();

	this->bestValue = -1;
	this->bestWidth = -1;
	this->bestHeight = -1;
	this->caltulateMultithread = false;
	this->threadNum = 0;
	this->awaliableBufferSpace = 0;
}

AlgorithmManager::~AlgorithmManager()
{
	delete this->Graphs;
}

ResultStruct AlgorithmManager::StartCalculations(unsigned int threads, bool multiThread)
{
	this->caltulateMultithread = multiThread;
	this->threadNum = threads;
	this->awaliableBufferSpace = threads;

	auto start = std::chrono::system_clock::now();
	this->Graphs->CreateGraph(this->types);

	FindOptimal();
	auto end = std::chrono::system_clock::now();

	auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	/*ResultStruct results;
	results.bestHeight = this->bestHeight;
	results.bestWidth = this->bestWidth;
	results.bestCombination = this->bestCombination;
	results.bestPlacement = this->Graphs->GetRectanglePlane(this->bestCombination);*/
	ResultStruct results = GetResults();
	results.time_microsec = elapsed_us;

	return results;
}

void AlgorithmManager::setTypes(std::vector<Type*> Types)
{
	this->types = Types;
}

void AlgorithmManager::FindOptimal()
{
	if (this->caltulateMultithread)
	{
		ManageThreads();
	}
	else
	{
		std::map<Type*, Variant*> VariantStack;
		FindSinglethread(0, VariantStack);
	}
}

void AlgorithmManager::FindSinglethread(unsigned depth, std::map<Type*, Variant*> variantStack)
{
	for (auto variant : this->types[depth]->GetVariants())
	{
		//variantStack.push_back(variant);
		variantStack[types[depth]] = variant;

		auto costs = Graphs->CalculateCost(variantStack);
		unsigned G_Value = costs.first;
		unsigned H_Value = costs.second; 
		if (G_Value * H_Value >= this->bestValue || G_Value == -1 || H_Value == -1)
		{
			//variantStack.pop_back();
			continue;
		}

		if (depth == this->types.size() - 1) //Leaf
		{
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

		//variantStack.pop_back();
	}
	variantStack.erase(types[depth]);
}

void AlgorithmManager::FindMultithread(unsigned depth, std::map<Type*, Variant*> variantStack)
{
	for (auto variant : this->types[depth]->GetVariants())
	{
		variantStack[types[depth]] = variant;

		auto costs = Graphs->CalculateCost(variantStack);
		unsigned G_Value = costs.first;
		unsigned H_Value = costs.second;

		if (G_Value * H_Value >= this->bestValue)
		{
			//variantStack.pop_back();
			continue;
		}


		if (depth == this->types.size() - 1) //Leaf
		{
			CalculateCostsWithMutex(variantStack);
		}
		else if (depth < this->types.size())
		{
			this->bufferSizeGuard.lock();
			if (this->awaliableBufferSpace > 0)
			{
				awaliableBufferSpace--;
				this->WorkToDo.push_back(std::pair<int, std::map<Type*, Variant*>>(depth+1, variantStack));
				this->bufferSizeGuard.unlock();
				//variantStack.pop_back();
				continue;
			}
			else
			{
				this->bufferSizeGuard.unlock();
				FindMultithread(depth + 1, variantStack); // Going deeper into the "tree"
			}
		}
		//variantStack.pop_back();
	}
}

void AlgorithmManager::ManageThreads()
{
	using namespace std::chrono_literals;

	std::vector<std::future<void>> ThreadPool;
	short avaliableThreads = threadNum;

	std::map<Type*, Variant*> VariantStack;
	ThreadPool.push_back(std::async(std::launch::async, [this, VariantStack] {this->FindMultithread(0, VariantStack);}));

	avaliableThreads--;

	while (ThreadPool.size() > 0 && avaliableThreads < threadNum)
	{
		if (WorkToDo.size() > 0 && avaliableThreads > 0)
		{
			int depth = WorkToDo.front().first;
			auto& stack = WorkToDo.front().second;

			ThreadPool.push_back(
				std::async(
					std::launch::async, [this, depth, stack] {this->FindMultithread(depth, stack); }));
			WorkToDo.pop_front();
			avaliableThreads--;

			this->bufferSizeGuard.lock();
			this->awaliableBufferSpace++;
			this->bufferSizeGuard.unlock();
		}

		for (int i = 0; i < ThreadPool.size(); i++)
		{
			std::future_status status;

			try {
				status = ThreadPool[i].wait_for(0ms);
			}
			catch (std::future_error Ex)
			{
				continue;
			}
			if (status == std::future_status::ready)
			{
				ThreadPool[i].get();
				avaliableThreads++;
				ThreadPool.erase(ThreadPool.begin() + i);
				break;
			}
		}
	}
}

void AlgorithmManager::CalculateCostsWithMutex(std::map<Type*, Variant*> variantStack)
{
	auto costs = Graphs->CalculateCost(variantStack);
	unsigned G_Value = costs.first;
	unsigned H_Value = costs.second; 
	auto value = G_Value * H_Value;

	this->guard.lock();
	if (this->bestValue > value)
	{
		this->bestValue = value;
		this->bestHeight = G_Value;
		this->bestWidth = H_Value;
		this->bestCombination = variantStack;
	}
	this->guard.unlock();
}

ResultStruct AlgorithmManager::GetResults()
{
	ResultStruct results;

	if (bestHeight == -1)
	{
		results.bestHeight = 0;
		results.bestWidth = 0;
		results.bestCombination = std::map<Type*, Variant*>();
		results.bestPlacement = std::map<Type*, VariantRectangle*>();
	}
	else
	{
		results.bestHeight = this->bestHeight;
		results.bestWidth = this->bestWidth;
		results.bestCombination = this->bestCombination;
		results.bestPlacement = this->Graphs->GetRectanglePlane(this->bestCombination);
	}

	return results;
}

} //namespace FPA