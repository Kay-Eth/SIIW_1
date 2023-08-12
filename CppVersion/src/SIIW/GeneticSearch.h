#pragma once

#include "Search.h"
#include "Random.h"
#include "Selection.h"

namespace SIIW
{
	class GeneticSearch : public Search
	{
	public:
		GeneticSearch(Problem* problem, StopCondition* stopCondition, Selection* selection, int populationSize, float crossoverChance, float mutationChance, unsigned int seed = 0);
		virtual void SearchForBestSolution() override;

	private:
		Random m_random;
		int m_populationSize;
		float m_crossoverChance;
		float m_mutationChance;
		Selection* m_selection;
	};
}