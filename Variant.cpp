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

unsigned Variant::GetHeight()
{
	return this->height;
}

unsigned Variant::GetWidth()
{
	return this->width;
}

Type* Variant::GetType()
{
	return this->type;
}
