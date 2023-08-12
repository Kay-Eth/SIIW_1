#pragma once

#include <random>
#include <limits>

namespace SIIW
{
	class Random
	{
	public:
		const static int BITS_OF_RANDOMNES = 10;

		Random();
		Random(unsigned int seed);

		void SetSeed(unsigned int seed);

		template<typename T> T GetRandomInt();
		template<typename T> T GetRandomIntLeftBounded(T begin, T end);
		template<typename T> T GetRandomIntRightBounded(T begin, T end);
		template<typename T> T GetRandomIntBounded(T begin, T end);

		template<typename T> T GetRandomReal();
		template<typename T> T GetRandomRealLeftBounded(T begin, T end);
		template<typename T> T GetRandomRealRightBounded(T begin, T end);
		template<typename T> T GetRandomRealBounded(T begin, T end);

	private:
		std::default_random_engine m_defaultRandomEngine;
	};

	template<typename T>
	T Random::GetRandomInt()
	{
		std::uniform_int_distribution<T> dis;
		return dis(m_defaultRandomEngine);
	}

	template<typename T>
	inline T Random::GetRandomIntLeftBounded(T begin, T end)
	{
		return GetRandomIntBounded<int>(begin, end - 1);
	}

	template<typename T>
	inline T Random::GetRandomIntRightBounded(T begin, T end)
	{
		return GetRandomIntBounded<int>(begin - 1, end);
	}

	template<typename T>
	T Random::GetRandomIntBounded(T begin, T end)
	{
		std::uniform_int_distribution<T> dis(begin, end);
		return dis(m_defaultRandomEngine);
	}

	template<typename T>
	T Random::GetRandomReal()
	{
		std::uniform_real_distribution<T> dis;
		return dis(m_defaultRandomEngine);
	}

	template<typename T>
	inline T Random::GetRandomRealLeftBounded(T begin, T end)
	{
		return std::generate_canonical<T, Random::BITS_OF_RANDOMNES>(m_defaultRandomEngine) * (end - begin) + begin;
	}

	template<typename T>
	inline T Random::GetRandomRealRightBounded(T begin, T end)
	{
		return (1 - std::generate_canonical<T, Random::BITS_OF_RANDOMNES>(m_defaultRandomEngine)) * (end - begin) + begin;
	}

	template<typename T>
	T Random::GetRandomRealBounded(T begin, T end)
	{
		std::uniform_real_distribution<T> dis(begin, end);
		return dis(m_defaultRandomEngine);
	}
}