#include "RectanglePlacer.h"

namespace FPA
{

void RectanglePlacer::AddNextRect(int tlX, int tlY, GraphNode* node)
{
	for (auto node : node->GetRightNodes())
	{
		Variant* var = configuration[node->GetType()];
		if (var == nullptr)
			var = this->blankVariant;
		VariantRectangle* rect = new VariantRectangle(var, tlX, tlY);
		this->plane[node->GetType()] = rect;
		if (!node->GetRightNodes()[0]->isEndNode())
		{
			AddNextRect(tlX + var->GetWidth(), tlY, node);
		}
		tlY += var->GetHeight();
	}
}

RectanglePlacer::RectanglePlacer()
{
	this->blankVariant = new Variant(0, 0, nullptr);
	this->startNode = nullptr;
}

RectanglePlacer::~RectanglePlacer()
{
}

std::map<Type*, VariantRectangle*> RectanglePlacer::PlaceRectangles(GraphNode* start_H_Node, std::map<Type*, Variant*> variantConfiguration)
{
	this->startNode = start_H_Node;
	this->configuration = variantConfiguration;

	AddNextRect(0, 0, startNode); //The problem here is that the configuration isn't alwas complete, therefore conf[type] gives nullptr

	return this->plane;
}

} //namespace FPA

