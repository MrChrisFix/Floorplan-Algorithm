#pragma once
#include <vector>
#include "Variant.h"
#include <string>

class Type
{
private:
	std::vector<Variant*> variants;

	std::string Name;

public:
	Type();
	~Type();

	void setName(std::string name);
	std::string GetName();

	std::vector<Variant*> GetVariants();
	void AddVariant(Variant* variant); //TODO: add overload with variant creation info;

};

