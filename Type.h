#pragma once
#include <vector>
#include "Variant.h"
#include "Requirement.h"
#include <string>

class Type
{
private:
	std::vector<Variant*> variants;
	std::vector<Requirement*> requirements;

	std::string Name;

public:
	Type();
	~Type();

	void AddNewRequirement(Requirement* requirement);
	void RemoveRequirement(Requirement* requirement);
	std::vector<Requirement*> GetRequirements();

	void setName(std::string name);
	std::string GetName();

	std::vector<Variant*> GetVariants();
	void AddVariant(Variant* variant); //TODO: add overload with variant creation info;

};

