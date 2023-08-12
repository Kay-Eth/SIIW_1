#pragma once

#include "Search.h"
#include "Random.h"

namespace SIIW
{
	class RandomSearch : public Search
	{
	public:
		RandomSearch(Problem* problem, StopCondition* stopCondition, unsigned int seed = 0);
		virtual void SearchForBestSolution() override;

	private:
		Random m_random;
	};
}