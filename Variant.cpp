#include "Variant.h"

Variant::Variant(unsigned hei, unsigned wid, Type* parentType)
{
	this->height = hei;
	this->width = wid;
	this->type = parentType;
}

Variant::~Variant()
{
	this->type = nullptr;
}

unsigned int Variant::GetCost()
{
	return this->height * this->width;
}

unsigned Variant::Height()
{
	return this->height;
}

unsigned Variant::Width()
{
	return this->width;
}

Type* Variant::GetType()
{
	return this->type;
}
