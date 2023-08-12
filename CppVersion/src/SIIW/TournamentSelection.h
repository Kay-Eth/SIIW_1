#pragma once
#include "Selection.h"

namespace SIIW
{
	class TournamentSelection : public Selection
	{
	public:
		TournamentSelection(int tournamentSize);

		virtual Solution* Select(std::map<Solution*, double>& solutionsMap) override;

	private:
		int m_tournamentSize;
	};
}