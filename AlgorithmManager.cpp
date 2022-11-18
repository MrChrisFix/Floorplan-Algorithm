#include "AlgorithmManager.h"
#include "TreeNodeLeaf.h"

AlgorithmManager::AlgorithmManager()
{
	this->Graph_G = new GraphNode(true, false);
	this->Graph_H = new GraphNode(true, true);
	this->treeRoot = new TreeNode(nullptr);
}

AlgorithmManager::~AlgorithmManager()
{
	delete this->Graph_G;
	delete this->Graph_H;
	delete this->treeRoot;
}

void AlgorithmManager::setTypes(std::vector<Type*> Types)
{
	this->types = Types;
}

void AlgorithmManager::CreateTree()
{
	std::vector<Variant*> VariantStack;

	AddTreeBranch(0, VariantStack, this->treeRoot);

	/* Old stuff
	std::vector<TreeNode*> tempRoots;
	for (int i = 0; i < this->types.size(); i++)
	{
		TreeNode* node = new TreeNode(nullptr, 0);

		for (int j = 0; j < this->types[i]->GetVariants().size(); j++)
		{
			node->AddNewBranch(0);	//TODO: cost
			//Create bush of options and then combine them together in a chain

			//Note: ale jak i gdzie ja tu niby sprawdzam, czy te elementy pasuj� obok siebie?
			//Chyba b�d� musia� jeszcze przerobi� to jako� ten Type, 
			//�eby wiedzie�, co jest na prawo, lewo, w d�, g�r�, �eby wykorzysta� algorytm z zeszytu.

			//Musia�bym chyba wtedy dla ka�dego w�z�a osobno rozparza� sytauacj�(patrz zeszyt).
			//Ale wci�� musz� znale�� algortym na ieracj� to tych w�z�ach aby dodawa� nowe.
			//Obawiam si�, �e b�dzie jednak potrzebna funkcja rekurencyjna
		}
		tempRoots.push_back(node);
	}
	//Next: combine together
	*/
}

void AlgorithmManager::AddTreeBranch(unsigned int depth, std::vector<Variant*> &variantStack, TreeNode* ptr) //< first ptr is root
{
	for (auto variant : this->types[depth]->GetVariants())
	{
		variantStack.push_back(variant);

		if (depth == this->types.size() - 1) //last type -> leaf
		{
			TreeNodeLeaf* leaf = new TreeNodeLeaf(ptr, 1, variantStack);
			ptr->AddLeaf(leaf);
		}
		else if (depth < this->types.size())
		{
			TreeNode* newNode = ptr->AddNewBranch();
			AddTreeBranch(depth + 1, variantStack ,newNode); // Going deeper into the tree
		}

		variantStack.pop_back();

		/* Old cost calculatons
		unsigned int cost;
		if (ptr->cost == UINT32_MAX)
			cost = UINT32_MAX;
		else
		{
			Check the value and if the elements are good size ergo use my notebook alg
			if (ptr == nullptr)
				cost = variant->GetCost();
			else
			{
				bool doesFit = false;
				doesFit = variant->Height() <= this->types[depth]->GetRequirements(); //TODO


				if (doesFit)
					cost = variant->GetCost();
				else
					cost = UINT32_MAX;
			}
		}
		*/
	}

}

