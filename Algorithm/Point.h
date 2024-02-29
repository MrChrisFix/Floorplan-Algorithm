#pragma once
#include <string>

namespace FPA
{
	/**
	 * Struct for definign a point on a 2D plane
	*/
	struct Point
	{
		int X, Y;
		Point(int x, int y) : X(x), Y(y) {};
		std::string toString()
		{
			return std::string("(" + std::to_string(X) + ";" + std::to_string(Y) + ")");
		}
	};
}