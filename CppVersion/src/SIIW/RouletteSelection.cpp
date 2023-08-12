#include "RouletteSelection.h"
#include <cmath>
#include "Random.h"

namespace SIIW
{
	Solution* RouletteSelection::Select(std::map<Solution*, double>& solutionsMap)
	{
		double sum = 0;
		for (auto& s : solutionsMap)
		{
			sum += s.second;
		}
		sum = std::abs(sum);
		Random random;
		double val = random.GetRandomRealBounded<double>(0.0, sum);
		double pointer = 0.0;
		Solution* result = nullptr;

		for (auto it = solutionsMap.cbegin(); it != solutionsMap.cend() && result == nullptr; it++)
		{
			pointer += std::abs((*it).second);
			if (val <= pointer)
			{
				result = (*it).first;
			}
		}
		// solutionsMap.erase(result);

		return result;
	}
}