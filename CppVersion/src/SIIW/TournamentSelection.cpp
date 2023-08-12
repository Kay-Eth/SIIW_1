#include "TournamentSelection.h"
#include <vector>
#include "Random.h"

namespace SIIW
{
	TournamentSelection::TournamentSelection(int tournamentSize)
		: m_tournamentSize(tournamentSize)
	{

	}

	Solution* TournamentSelection::Select(std::map<Solution*, double>& solutionsMap)
	{
		Solution* result = nullptr;
		std::map<Solution*, double> tempMap(solutionsMap);
		std::vector<Solution*> tournament;

		Random random;
		for (int i = 0; i < m_tournamentSize && i < solutionsMap.size(); i++)
		{
			auto it = tempMap.begin();
			std::advance(it, random.GetRandomInt<int>() % tempMap.size());
			tournament.push_back(it->first);
			tempMap.erase(it->first);
		}

		result = tournament.front();
		double best_val = solutionsMap[result];
		for (size_t i = 1; i < tournament.size(); i++)
		{
			Solution* current = tournament[i];
			double current_val = solutionsMap[current];
			if (current_val > best_val)
			{
				result = current;
				best_val = current_val;
			}
		}

		return result;
	}
}