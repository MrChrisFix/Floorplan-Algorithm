#pragma once

namespace FPA {

	enum class SIDE {
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	inline SIDE CharToSide(char direction)
	{
		switch (direction)
		{
			case 'U': case 'u':
				return SIDE::UP;
			case 'D': case 'd':
				return SIDE::DOWN;
			case 'R': case 'r':
				return SIDE::RIGHT;
			case 'L': case 'l':
				return SIDE::LEFT;
		}
	}

	inline char SideToChar(SIDE side)
	{
		switch (side)
		{
			case FPA::SIDE::UP:
				return 'U';
			case FPA::SIDE::LEFT:
				return 'L';
			case FPA::SIDE::DOWN:
				return 'D';
			case FPA::SIDE::RIGHT:
				return 'R';
		}
	}
}