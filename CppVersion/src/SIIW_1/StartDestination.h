#pragma once

#include "Point.h"

namespace SIIW_1
{
	struct StartDestination
	{
		Point start;
		Point end;

		StartDestination(int x1, int y1, int x2, int y2)
			: start(Point(x1, y1)), end(Point(x2, y2))
		{

		}
	};
}