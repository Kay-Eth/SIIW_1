#include "RandomSearch.h"

namespace SIIW
{
	RandomSearch::RandomSearch(Problem* problem, StopCondition* stopCondition, unsigned int seed)
		: Search(problem, stopCondition), m_random(Random(seed))
	{
		double f;
		m_bestSolutionQuality = (*((long long*)&f)) = ~(1LL << 52);
	}

	void RandomSearch::SearchForBestSolution()
	{
		Solution* currentSolution = NULL;
		while (!(m_stopCondition->StopConditionSatisfied()))
		{
			currentSolution = m_problem->CreateRandomSolutionObject();
			bool error = false;
			double quality = m_problem->GetQuality(currentSolution, error);

			if (!error)
			{
				if (quality > m_bestSolutionQuality)
				{
					if (m_bestSolution != nullptr)
						delete m_bestSolution;

					m_bestSolutionQuality = quality;
					m_bestSolution = currentSolution;

					currentSolution = nullptr;
				}
			}

			if (currentSolution != nullptr)
				delete currentSolution;
		}
	}
}