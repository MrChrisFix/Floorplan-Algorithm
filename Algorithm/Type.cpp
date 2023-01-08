#include "Type.h"

namespace FPA {

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

void Type::RemoveVariant(Variant* variant)
{
	auto it = std::find(this->variants.begin(), this->variants.end(), variant);
	if (it != this->variants.end())
	{
		this->variants.erase(it);
	}
}

void Type::AddRequirement(char side, Type* type, bool onBoth)
{
	switch (side)
	{
		case 'U': case 'u':
		{
			this->up.push_back(type);
			if(onBoth) type->down.push_back(this);
			break;
		}
		case 'D': case 'd':
		{
			this->down.push_back(type);
			if (onBoth) type->up.push_back(this);
			break;
		}
		case 'R': case 'r':
		{
			this->right.push_back(type);
			if (onBoth) type->left.push_back(this);
			break;
		}
		case 'L': case 'l':
		{
			this->left.push_back(type);
			if (onBoth) type->right.push_back(this);
			break;
		}
		default:
			break;
	}

}

void Type::RemoveRequirement(Type* toRemove, bool onBoth)
{
	auto it = std::find(up.begin(), up.end(), toRemove);
	if (it != up.end())
	{
		up.erase(it);
		if (onBoth)
		{
			toRemove->RemoveRequirement(this, false);
		}
		return;
	}

	it = std::find(down.begin(), down.end(), toRemove);
	if (it != down.end())
	{
		down.erase(it);
		if (onBoth)
		{
			toRemove->RemoveRequirement(this, false);
		}
		return;
	}

	it = std::find(left.begin(), left.end(), toRemove);
	if (it != left.end())
	{
		left.erase(it);
		if (onBoth)
		{
			toRemove->RemoveRequirement(this, false);
		}
		return;
	}

	it = std::find(right.begin(), right.end(), toRemove);
	if (it != right.end())
	{
		right.erase(it);
		if (onBoth)
		{
			toRemove->RemoveRequirement(this, false);
		}
		return;
	}
}

} //namespace FPA