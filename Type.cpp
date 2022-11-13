#include "Type.h"

Type::Type()
{

}

Type::~Type()
{
	for (auto varinat : this->variants)
	{
		delete varinat;
	}
	this->variants.clear();
}

void Type::AddNewRequirement(Requirement* requirement)
{
	this->requirements.push_back(requirement);
}
