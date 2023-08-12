#pragma once

#include <vector>
#include "Solution.h"

namespace SIIW
{
	class Problem
	{
	public:
		virtual ~Problem() {}

		virtual double GetQuality(Solution* solution, bool& error) = 0;
		virtual bool ConstraintsSatisfied(Solution* solution) = 0;
		virtual Solution* CreateSolutionObject() = 0;
		virtual Solution* CreateRandomSolutionObject() = 0;
		virtual Solution* CopySolution(Solution* solution) = 0;

		virtual Solution* Crossover(Solution* a, Solution* b) = 0;
		virtual void Mutate(Solution* solution) = 0;
	};
}