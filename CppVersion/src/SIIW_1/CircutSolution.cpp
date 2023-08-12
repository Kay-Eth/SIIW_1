#include "CircutSolution.h"
#include "../SIIW/Exception.h"

#include <iostream>

namespace SIIW_1
{
	CircutSolution::CircutSolution(int pathCount)
		: m_pathCount(pathCount), m_paths(new Path*[pathCount])
	{
	}

	CircutSolution::CircutSolution(const CircutSolution& other)
		: m_pathCount(other.m_pathCount), m_paths(new Path*[other.m_pathCount])
	{
		for (int i = 0; i < m_pathCount; i++)
		{
			m_paths[i] = new Path(*(other.m_paths[i]));
		}
	}

	CircutSolution::~CircutSolution()
	{
		for (int i = 0; i < m_pathCount; i++)
		{
			delete m_paths[i];
		}

		delete[] m_paths;
	}

	void CircutSolution::SetPath(int index, Path* path)
	{
		if (index < 0 || index >= m_pathCount)
			throw SIIW::Exception("Index out of bounds");
		
		m_paths[index] = path;
	}

	Path* CircutSolution::GetPath(int index)
	{
		if (index < 0 || index >= m_pathCount)
			throw SIIW::Exception("Index out of bounds");
		
		return m_paths[index];
	}

	void CircutSolution::PrettyPrint()
	{
		for (int i = 0; i < m_pathCount; i++)
		{
			std::cout << "Path " << i << ": " << std::endl << "\t";

			for (auto segment : m_paths[i]->segments)
			{
				if (segment->direction == Segment::UP)
					std::cout << "UP ";
				else if (segment->direction == Segment::DOWN)
					std::cout << "DOWN ";
				else if (segment->direction == Segment::LEFT)
					std::cout << "LEFT ";
				else
					std::cout << "RIGHT ";

				std::cout << segment->length << "; ";
			}
			std::cout << std::endl << std::endl;
		}
	}
}