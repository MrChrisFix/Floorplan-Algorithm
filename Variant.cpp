#include "Variant.h"

Variant::Variant(unsigned hei, unsigned wid)
{
	this->height = hei;
	this->width = wid;
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
