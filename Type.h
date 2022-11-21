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

	/// <summary>
	/// Adds a requirement to the type invoked on and the type given
	/// </summary>
	/// <param name="side">The side of the requirement.<br/> Options: 'U'(Up), 'D'(Down), 'R'(Right), 'L'(Left)</param>
	/// <param name="type">The type of the requirement</param>
	void AddRequirement(char side, Type* type, bool onBoth = true);
};

