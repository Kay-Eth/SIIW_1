#include "GeneticSearch.h"

#include <map>

namespace SIIW
{
	GeneticSearch::GeneticSearch(Problem* problem, StopCondition* stopCondition, Selection* selection, int populationSize, float crossoverChance, float mutationChance, unsigned int seed)
		: Search(problem, stopCondition), m_random(Random(seed)), m_selection(selection), m_populationSize(populationSize), m_crossoverChance(crossoverChance), m_mutationChance(mutationChance)
	{
		double f;
		m_bestSolutionQuality = (*((long long*)&f)) = ~(1LL << 52);
	}

	void GeneticSearch::SearchForBestSolution()
	{
		std::map<Solution*, double>* population = new std::map<Solution*, double>();
		for (int i = 0; i < m_populationSize; i++)
		{
			bool error = false;
			Solution* s = m_problem->CreateRandomSolutionObject();
			double quality = m_problem->GetQuality(s, error);

			if (!error)
				population->insert(std::pair<Solution*, double>(s, quality));
			else
				i--;
		}

		while (!(m_stopCondition->StopConditionSatisfied()))
		{
			std::map<Solution*, double>* new_population = new std::map<Solution*, double>();
			while (new_population->size() != m_populationSize)
			{
				Solution* p1 = m_selection->Select(*population);
				Solution* p2 = m_selection->Select(*population);
				Solution* new_solution;

				if (m_random.GetRandomRealBounded<float>(0, 1) < m_crossoverChance)
					new_solution = m_problem->Crossover(p1, p2);
				else
					new_solution = m_problem->CopySolution((m_random.GetRandomIntBounded<int>(0, 1) == 0) ? p1 : p2);

				if (m_random.GetRandomRealBounded<float>(0, 1) < m_mutationChance)
					m_problem->Mutate(new_solution);


				bool error = false;
				double quality = m_problem->GetQuality(new_solution, error);
				if (!error)
					new_population->insert(std::pair<Solution*, double>(new_solution, quality));
			}

			for (auto it : *population)
			{
				delete it.first;
			}
			delete population;
			population = new_population;
		}

		for (auto it : *population)
		{
			if (it.second > m_bestSolutionQuality)
			{
				m_bestSolutionQuality = it.second;

				if (m_bestSolution != nullptr)
					delete m_bestSolution;
				m_bestSolution = it.first;
			}
			else
				delete it.first;
		}

		delete population;
	}
}