#include "Search.h"

namespace SIIW
{
	Search::Search(Problem* problem, StopCondition* stopCondition)
		: m_bestSolution(nullptr), m_bestSolutionQuality(-1), m_stopCondition(stopCondition)
	{
		m_problem = problem;
	}

	Search::~Search()
	{
		if (m_bestSolution != nullptr)
			delete m_bestSolution;
	}

	Solution* Search::GetBestSolution()
	{
		return m_bestSolution;
	}

	double Search::GetBestSolutionQuality()
	{
		return m_bestSolutionQuality;
	}
}