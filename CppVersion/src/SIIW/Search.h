#pragma once

#include "Problem.h"
#include "StopCondition.h"

namespace SIIW
{
	class Search
	{
	public:
		Search(Problem* problem, StopCondition* stopCondition);
		virtual ~Search();

		virtual void SearchForBestSolution() = 0;

		Solution* GetBestSolution();
		double GetBestSolutionQuality();

	protected:
		Problem* m_problem;
		Solution* m_bestSolution;
		StopCondition* m_stopCondition;
		double m_bestSolutionQuality;
	};
}