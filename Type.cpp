#include "Type.h"

Type::Type(std::string typeName)
{
	this->name = typeName;
}

Type::~Type()
{
	for (auto varinat : this->variants)
	{
		delete varinat;
		varinat = nullptr;
	}
	this->variants.clear();
}

void Type::setName(std::string newName)
{
	this->name = newName;
}

std::string Type::GetName()
{
	return this->name;
}

std::vector<Variant*> Type::GetVariants()
{
	return this->variants;
}

void Type::AddVariant(Variant* variant)
{
	this->variants.push_back(variant);
}

void Type::AddVariant(unsigned varWidth, unsigned varHeight)
{
	Variant* var = new Variant(varHeight, varWidth, this);
	this->variants.push_back(var);
}
