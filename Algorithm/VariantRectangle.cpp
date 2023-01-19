#include "VariantRectangle.h"
namespace FPA {

VariantRectangle::VariantRectangle(Variant* variant) : _topLeft(0,0)
{
	this->_variant = variant;
}

VariantRectangle::VariantRectangle(Variant* variant, Coords topLeft) : _topLeft(topLeft)
{
	this->_variant = variant;
}

VariantRectangle::VariantRectangle(Variant* variant, int topLeftX, int topLeftY) : _topLeft(topLeftX, topLeftY)
{
	this->_variant = variant;
}

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


} //namespace FPA
