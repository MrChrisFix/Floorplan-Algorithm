#include "Requirement.h"

Requirement::Requirement(Type* type, Side side)
{
	this->type = type;
	this->side = side;
}

Requirement::~Requirement()
{
	this->type = nullptr;
}
