#pragma once
#include "Variant.h"
#include "SideEnum.h"

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

	bool isIntersecting(VariantRectangle* other);
	/**
	 * Checks is the given rectangle is on the given side
	 * @param other The rectangle that should be chekced
	 * @param side The side on which 'other' shuld be
	 * @return boolean
	*/
	bool isOtherBySide(VariantRectangle* other, SIDE side);

};

} //namespace FPA


