#pragma once

#include "Selection.h"

namespace SIIW
{
	class RouletteSelection : public Selection
	{
	public:
		virtual Solution* Select(std::map<Solution*, double>& solutionsMap) override;
	};
}