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

void AlgorithmManager::Populate_G_Graph(GraphNode* currentNode)
{
	auto currentType = currentNode->GetType();

	if (currentType == nullptr) throw;

	if (currentType->up.empty())
	{
		//TODO: add end node
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
			GraphNode* newUp = new GraphNode(up, false);
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
		//TODO: add end node
	}

	if (currentType->left.empty())
	{
		this->Graph_H->AddNodeToGraph(currentNode);
		return;
	}

	for (auto left : currentType->left)
	{
		auto foundLeft = this->Graph_H->FindNodeByType(left); //is the type upwards already in the graph?
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

void AlgorithmManager::importTypesFromXML(std::string pathToXml)
{
	//TODO: XMLFileManager object here
}

void AlgorithmManager::PopulateGraphs()
{
	for (auto type : this->types)
	{
		//Check if the type is already in the graphs
		if (this->Graph_G->FindNodeByType(type) != nullptr)
			continue;


		//G Graph
		auto newNode = new GraphNode(type, false);
		this->Populate_G_Graph(newNode);



		//H Graph
		newNode = new GraphNode(type, true);
		this->Populate_H_Graph(newNode);

		//GraphNode* endHnode = new GraphNode(false, true);
	}
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
	*/
}

void AlgorithmManager::AddTreeBranch(unsigned int depth, std::vector<Variant*> &variantStack, TreeNode* ptr) //< first ptr is root
{
	for (auto variant : this->types[depth]->GetVariants())
	{
		variantStack.push_back(variant);

		if (depth == this->types.size() - 1) //last type -> leaf
		{
			unsigned G_Value = this->Graph_G->calculateCost(variantStack);
			unsigned H_Value = this->Graph_H->calculateCost(variantStack);
			TreeNodeLeaf* leaf = new TreeNodeLeaf(ptr, G_Value * H_Value, variantStack);
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

