#include "Type.h"

Type::Type()
{

}

Type::~Type()
{
	for (auto varinat : this->variants)
	{
		delete varinat;
	}
	this->variants.clear();
}
