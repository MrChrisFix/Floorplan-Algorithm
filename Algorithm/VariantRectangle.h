#pragma once
#include "Variant.h"
#include "SideEnum.h"
#include "Point.h"

namespace FPA {

class VariantRectangle
{
private:
	Variant* _variant;			/// The representing variant
	Point _topLeft;				/// The top left point of the rectangle

public:
	/**
	 * Constructor with only the variant. Will be positioned in (0,0)
	 * @param variant The representing variant
	*/
	VariantRectangle(Variant* variant);

	/**
	 * Constructor with the variant and point of the top left point
	 * @param variant The representing variant
	 * @param TopLeft The top left point of the rectangle
	*/
	VariantRectangle(Variant* variant, Point TopLeft);
	
	/**
	 * Constructor 
	 * @param variant The representing variant
	 * @param topLeftX The X coordinate of the top left point of the rectangle
	 * @param topLeftY The Y coordinate of the top left point of the rectangle
	*/
	VariantRectangle(Variant* variant, int topLeftX, int topLeftY);

	/**
	 * Destructor
	*/
	~VariantRectangle();

	/**
	 * Getter for the top left point
	 * @return The top left point of the rectangle
	*/
	Point TopLeft();

	/**
	 * Getter for the top right point
	 * @return The top right point of the rectangle
	*/
	Point TopRight();

	/**
	 * Getter for the bottom left point
	 * @return The bottom left point of the rectangle
	*/
	Point BottomLeft();

	/**
	 * Getter for the bottom right point
	 * @return The bottom right point of the rectangle
	*/
	Point BottomRight();

	/**
	 * Moves the rectangle by the given delta in the X axis. Negative delta is left, positive right
	 * @param delta The amount the rectangle should move. The sign deterines the direction
	*/
	void MoveXAxis(int delta);

	/**
	 * Moves the rectangle by the given delta in the Y axis. Negative delta is up, positive down
	 * @param delta The amount the rectangle should move. The sign deterines the direction
	*/
	void MoveYAxis(int delta);

	/**
	 * Checks whether the rectangle is intersecting with the given rectangle
	 * @param other The rectangle thet shuld be checked
	 * @return True if intersecting, otherwise false
	*/
	bool isIntersecting(VariantRectangle* other);
	/**
	 * Checks is the given rectangle is on the given side
	 * @param other The rectangle that should be chekced
	 * @param side The side on which 'other' shuld be
	 * @return boolean
	*/
	bool isOtherBySide(VariantRectangle* other, SIDE side);

	/**
	 * Getter for the variant
	 * @return Pointer of the representing variant
	*/
	Variant* GetVariant();
};

} //namespace FPA


