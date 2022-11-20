#pragma once
#include <vector>
#include "Variant.h"
#include <string>

class Type
{
private:
	std::vector<Variant*> variants;

	std::string name;	//Only for cosmetic purposes

public:
	Type(std::string typeName);
	~Type();

	//Requirements
	std::vector<Type*> right;
	std::vector<Type*> down;
	std::vector<Type*> left;
	std::vector<Type*> up;

	void setName(std::string newName);
	std::string GetName();

	std::vector<Variant*> GetVariants();
	void AddVariant(Variant* variant);
	void AddVariant(unsigned varWidth, unsigned varHeight);

};

