#pragma once

#include "../SIIW/Problem.h"
#include "../SIIW/Random.h"
#include "StartDestination.h"
#include "CircutSolution.h"
#include <vector>

namespace SIIW_1
{
	class CircutProblem : public SIIW::Problem
	{
	public:
		static const char* PATH_TO_FILE;

		CircutProblem(float mutationAChance);
		~CircutProblem();

		virtual double GetQuality(SIIW::Solution* solution, bool& error) override;
		virtual bool ConstraintsSatisfied(SIIW::Solution* solution) override;
		virtual SIIW::Solution* CreateSolutionObject() override;
		virtual SIIW::Solution* CreateRandomSolutionObject() override;
		virtual SIIW::Solution* CopySolution(SIIW::Solution* solution) override;

		virtual SIIW::Solution* Crossover(SIIW::Solution* a, SIIW::Solution* b) override;
		virtual void Mutate(SIIW::Solution* solution) override;

	private:
		void LoadDataFromFile();

		void MutateA(SIIW::Solution* solution);
		void MutateB(SIIW::Solution* solution);

		int m_sizeX;
		int m_sizeY;
		std::vector<StartDestination*> m_startDestinations;

		float m_mutationAChance;

		SIIW::Random m_random;
	};
}