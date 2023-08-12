#pragma once

#include "../SIIW/Solution.h"
#include "Path.h"

namespace SIIW_1
{
	class CircutSolution : public SIIW::Solution
	{
	public:
		CircutSolution(int pathCount);
		CircutSolution(const CircutSolution& other);
		~CircutSolution();

		void SetPath(int index, Path* path);
		Path* GetPath(int index);

		virtual void PrettyPrint() override;

	private:
		int m_pathCount;
		Path** m_paths;
	};
}