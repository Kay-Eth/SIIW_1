#pragma once
#include <iostream>

namespace SIIW_1
{
	struct Point
	{
		int x;
		int y;

		Point(int px, int py)
		{
			x = px;
			y = py;
		}

		Point(const Point& other)
		{
			x = other.x;
			y = other.y;
		}

		bool operator==(const Point &other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Point& other) const
		{
			return x != other.x || y != other.y;
		}
	};
}