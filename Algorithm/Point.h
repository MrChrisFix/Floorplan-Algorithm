#pragma once

namespace FPA
{
	/**
	 * Struct for definign a point on a 2D plane
	*/
	struct Point
	{
		int X, Y;
		Point(int x, int y) : X(x), Y(y) {};
	};
}