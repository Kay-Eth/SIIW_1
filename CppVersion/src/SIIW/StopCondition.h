#pragma once

namespace SIIW
{
	class StopCondition
	{
	public:
		virtual bool StopConditionSatisfied() = 0;
	};
}