#include "AlgorithmManager.h"

void AlgorithmManager::setTypes(std::vector<Type*> Types)
{
	this->types = Types;
}

void AlgorithmManager::CreateTree()
{
	std::vector<TreeNode*> tempRoots;
	for (int i = 0; i < this->types.size(); i++)
	{
		TreeNode* node = new TreeNode(nullptr, 0);

		for (int j = 0; j < this->types[i]->GetVariants().size(); j++)
		{
			node->AddNewBranch(0);	//TODO: cost
			//Create bush of options and then combine them together in a chain

			//Note: ale jak i gdzie ja tu niby sprawdzam, czy te elementy pasuj¹ obok siebie?
			//Chyba bêdê musia³ jeszcze przerobiæ to jakoœ ten Type, 
			//¿eby wiedzieæ, co jest na prawo, lewo, w dó³, górê, ¿eby wykorzystaæ algorytm z zeszytu.

			//Musia³bym chyba wtedy dla ka¿dego wêz³a osobno rozparzaæ sytauacjê(patrz zeszyt).
			//Ale wci¹¿ muszê znaleŸæ algortym na ieracjê to tych wêz³ach aby dodawaæ nowe.
			//Obawiam siê, ¿e bêdzie jednak potrzebna funkcja rekurencyjna
		}
		tempRoots.push_back(node);
	}
	//Next: combine together
}

void AlgorithmManager::AddTreeBranch(unsigned int depth, TreeNode* ptr) //< first ptr is root
{
	// Note to myself:
	// The cost is wrongly done here. Needs rework

	for (auto variant : this->types[depth]->GetVariants())
	{
		//AddNewBranchForTheVariant(unsigned int depth, TreeNode * ptr): algorytm zeszytowy:


		unsigned int cost;
		if (ptr->cost == UINT32_MAX)
			cost = UINT32_MAX;
		else
		{
			//Check the value and if the elements are good size ergo use my notebook alg
			if (ptr == nullptr)
				cost = variant->GetCost();
			else
			{
				bool doesFit = false;
				//doesFit = variant->Height() <= this->types[depth]->GetRequirements(); //TODO


				if (doesFit)
					cost = variant->GetCost();
				else
					cost = UINT32_MAX;
			}
		}

		TreeNode* newNode = ptr->AddNewBranch(cost);

		//Check if there are more types to add below (depth)
		if (depth < this->types.size())
			AddTreeBranch(depth + 1, newNode); //<Wchodzimy g³êbiej
		else
			return;
	}

}

