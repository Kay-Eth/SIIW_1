#include "Random.h"
#include <ctime>

namespace SIIW
{
	Random::Random() :
		m_defaultRandomEngine(std::default_random_engine(std::random_device()()))
	{

	}

	Random::Random(unsigned int seed) :
		m_defaultRandomEngine(std::default_random_engine(seed))
	{

	}

	void Random::SetSeed(unsigned int seed)
	{
		m_defaultRandomEngine.seed(seed);
	}
}