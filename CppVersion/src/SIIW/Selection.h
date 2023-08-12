#pragma once

#include <map>
#include "Problem.h"

namespace SIIW
{
	class Selection
	{
	public:
		virtual Solution* Select(std::map<Solution*, double>& solutionsMap) = 0;
	};
}