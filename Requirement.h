#pragma once
#include "Type.h"
class Requirement
{
public:
	enum class Side
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NOT_UP,
		NOT_DOWN,
		NOT_LEFT,
		NOT_RIGHT,
		NOT_AT_ALL
	};

private:
	Type* type;
	Side side;

public:


	Requirement(Type* type, Side side);
	~Requirement();

	

};

