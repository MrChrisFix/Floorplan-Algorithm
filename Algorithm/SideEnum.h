#pragma once

namespace FPA {

	/**
	 * Enum describing possible sides
	*/
	enum class SIDE {
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	/**
	 * Method for converting char to SIDE
	 * @param direction The char to convert
	 * @return SIDE based on given char
	*/
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

	/**
	 * Method for converting SIDE to char
	 * @param side The SIDE that should be converted
	 * @return Uppercase char representing the SIDE
	*/
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