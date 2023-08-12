#pragma once

#include <iostream>

namespace SIIW_1
{
	struct Segment
	{
		static const int UP = 0;
		static const int RIGHT = 1;
		static const int DOWN = 2;
		static const int LEFT = 3;

		Segment(int dir, int len)
			: direction(dir), length(len)
		{

		}

		Segment(const Segment& other)
			: direction(other.direction), length(other.length)
		{

		}

		static int GetReverseDirection(int dir)
		{
			if (dir == UP)
				return DOWN;
			if (dir == DOWN)
				return UP;
			if (dir == LEFT)
				return RIGHT;
			if (dir == RIGHT)
				return LEFT;

			return -1;
		}

		int direction;
		int length;
	};
}