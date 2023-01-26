#include "VariantRectangle.h"
namespace FPA {

VariantRectangle::VariantRectangle(Variant* variant) : _topLeft(0, 0), _variant(variant) {}

VariantRectangle::VariantRectangle(Variant* variant, Coords topLeft) : _topLeft(topLeft), _variant(variant) {}

VariantRectangle::VariantRectangle(Variant* variant, int topLeftX, int topLeftY) : _topLeft(topLeftX, topLeftY), _variant(variant) {}

VariantRectangle::~VariantRectangle()
{
	this->_variant = nullptr;
}

VariantRectangle::Coords VariantRectangle::TopLeft()
{
	return this->_topLeft;
}

VariantRectangle::Coords VariantRectangle::TopRight()
{
	int X = _topLeft.X + _variant->GetWidth();
	int Y = _topLeft.Y;
	return Coords(X, Y);
}

VariantRectangle::Coords VariantRectangle::BottomLeft()
{
	int X = _topLeft.X;
	int Y = _topLeft.Y + _variant->GetHeight();;
	return Coords(X, Y);
}

VariantRectangle::Coords VariantRectangle::BottomRight()
{
	int X = _topLeft.X + _variant->GetWidth();
	int Y = _topLeft.Y + _variant->GetHeight();
	return Coords(X, Y);
}

void VariantRectangle::MoveXAxis(int delta)
{
	this->_topLeft.X += delta;
}

void VariantRectangle::MoveYAxis(int delta)
{
	this->_topLeft.Y += delta;
}

bool VariantRectangle::isIntersecting(VariantRectangle* other)
{
	bool Y = this->TopLeft().Y < other->BottomLeft().Y && this->BottomLeft().Y > other->TopLeft().Y;
	bool X = this->TopLeft().X < other->TopRight().X && this->TopRight().X > other->TopLeft().X;

	if (Y && X)
		return true;

	return false;
}

bool VariantRectangle::isOtherBySide(VariantRectangle* other, SIDE side)
{
	bool X = false, Y = false;

	switch (side)
	{
		case FPA::SIDE::UP:
		{
			X = this->TopLeft().X < other->TopRight().X && this->TopRight().X > other->TopLeft().X;
			Y = this->TopLeft().Y >= other->BottomLeft().Y;
			break;
		}
		case FPA::SIDE::LEFT:
		{
			X = this->TopRight().X <= other->TopLeft().X;
			Y = this->TopLeft().Y < other->BottomLeft().Y && this->BottomLeft().Y > other->TopLeft().Y;
			break;
		}
		case FPA::SIDE::DOWN:
		{
			X = this->TopLeft().X < other->TopRight().X && this->TopRight().X > other->TopLeft().X;
			Y = this->BottomLeft().Y <= other->TopLeft().Y;
			break;
		}
		case FPA::SIDE::RIGHT:
		{
			X = this->TopLeft().X >= other->TopRight().X;
			Y = this->TopLeft().Y < other->BottomLeft().Y && this->BottomLeft().Y > other->TopLeft().Y;
			break;
		}
		default:
			break;
	}

	return X && Y;
}


} //namespace FPA
