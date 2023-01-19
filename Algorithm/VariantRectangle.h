#pragma once
#include "Variant.h"

namespace FPA {

class VariantRectangle
{
public:
	struct Coords{
		int X, Y;
		Coords(int x, int y) : X(x), Y(y) {};
	};

private:
	Variant* _variant;
	Coords _topLeft;

public:
	VariantRectangle(Variant* variant);
	VariantRectangle(Variant* variant, Coords TopLeft);
	VariantRectangle(Variant* variant, int topLeftX, int topLeftY);
	~VariantRectangle();

	Coords TopLeft();
	Coords TopRight();
	Coords BottomLeft();
	Coords BottomRight();

	void MoveXAxis(int delta);
	void MoveYAxis(int delta);

};

} //namespace FPA


