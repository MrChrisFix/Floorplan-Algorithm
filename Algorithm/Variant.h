#pragma once

class Type; //<- avoiding a #include deadlock

class Variant
{
private:

	unsigned int height, width;
	Type* type;

public:
	Variant(unsigned hei, unsigned wid, Type* parentType);
	~Variant();

	unsigned GetHeight();
	void SetHeight(unsigned hei);
	unsigned GetWidth();
	void SetWidth(unsigned wid);

	Type* GetType();
};