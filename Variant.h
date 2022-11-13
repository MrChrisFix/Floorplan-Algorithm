#pragma once
class Variant
{
private:

	unsigned int height, width;

public:
	Variant(unsigned hei, unsigned wid);
	~Variant();

	unsigned int GetCost();

	unsigned Height();
	unsigned Width();
};