#pragma once

#include "StopCondition.h"

namespace SIIW
{
	class CountStopCondition : public StopCondition
	{
	public:
		CountStopCondition(unsigned int repeats)
			: m_count(0), m_repeats(repeats)
		{

		}

		virtual bool StopConditionSatisfied() override
		{
#ifdef _DEBUG
			std::cout << "CountStopCondition: " << m_count << std::endl;
#endif

			if (m_count >= m_repeats)
				return true;
			m_count += 1;
			return false;
		}

	private:
		unsigned int m_count;
		unsigned int m_repeats;
	};
}