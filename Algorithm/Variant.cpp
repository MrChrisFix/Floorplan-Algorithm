#include "Variant.h"

namespace FPA {

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

void Variant::SetHeight(unsigned hei)
{
	this->height = hei;
}

unsigned Variant::GetWidth()
{
	return this->width;
}

void Variant::SetWidth(unsigned wid)
{
	this->width = wid;
}

Type* Variant::GetType()
{
	return this->type;
}

} //namespace FPA