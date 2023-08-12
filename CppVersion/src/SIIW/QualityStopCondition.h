#pragma once

#include "StopCondition.h"
#include "Search.h"

namespace SIIW
{
	class HighestQualityStopCondition : public StopCondition
	{
	public:
		HighestQualityStopCondition(Search* search, double threshold)
			: m_search(search), m_threshold(threshold)
		{

		}

		virtual bool StopConditionSatisfied() override
		{
			return !(m_search->GetBestSolutionQuality() < m_threshold);
		}

		void SetSearch(Search* search)
		{
			m_search = search;
		}

	private:
		Search* m_search;
		double m_threshold;
	};

	class LowestQualityStopCondition : public StopCondition
	{
	public:
		LowestQualityStopCondition(Search* search, double threshold)
			: m_search(search), m_threshold(threshold)
		{

		}

		virtual bool StopConditionSatisfied() override
		{
			return !(m_search->GetBestSolutionQuality() > m_threshold);
		}

		void SetSearch(Search* search)
		{
			m_search = search;
		}

	private:
		Search* m_search;
		double m_threshold;
	};
}