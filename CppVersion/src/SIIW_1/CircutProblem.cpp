#include "CircutProblem.h"
#include "../SIIW/Exception.h"
#include "../SIIW/Random.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

namespace SIIW_1
{
	const char* CircutProblem::PATH_TO_FILE = "data/SIIW_1/data.txt";

	CircutProblem::CircutProblem(float mutationAChance)
		: m_mutationAChance(mutationAChance)
	{
		LoadDataFromFile();
	}

	CircutProblem::~CircutProblem()
	{
		for (auto sd : m_startDestinations)
		{
			if (sd != nullptr)
				delete sd;
		}

	}

	double CircutProblem::GetQuality(SIIW::Solution* solution, bool& error)
	{
		CircutSolution* sol = (CircutSolution*)solution;
		double result = 0;

		int** map = new int* [m_sizeX];
		for (int i = 0; i < m_sizeX; i++)
		{
			map[i] = new int[m_sizeY];

			for (int j = 0; j < m_sizeY; j++)
			{
				map[i][j] = 0;
			}
		}

		long long length = 0;
		long long count_of_segments = 0;

		for (int i = 0; i < m_startDestinations.size(); i++)
		{
			Point* current_point = new Point(m_startDestinations[i]->start);
			Path* path = sol->GetPath(i);

			map[current_point->x][current_point->y] += 1;
			for (auto segment : path->segments)
			{
				length += segment->length;
				count_of_segments += 1;

				Point* increment;
				if (segment->direction == Segment::UP)
					increment = new Point(0, -1);
				else if (segment->direction == Segment::DOWN)
					increment = new Point(0, 1);
				else if (segment->direction == Segment::LEFT)
					increment = new Point(-1, 0);
				else
					increment = new Point(1, 0);
				
				for (int j = 0; j < segment->length; j++)
				{
					current_point->x += increment->x;
					current_point->y += increment->y;
					map[current_point->x][current_point->y] += 1;
				}

				delete increment;
			}

			delete current_point;
		}

		long long intersections = 0;

		for (int x = 0; x < m_sizeX; x++)
		{
			for (int y = 0; y < m_sizeY; y++)
			{
				if (map[x][y] > 1)
					intersections += ((long long)(map[x][y])) * 10;
			}
		}

		for (int x = 0; x < m_sizeX; x++)
		{
			delete[] map[x];
		}
		delete[] map;

		result = length + count_of_segments + intersections;

		return -result;
	}

	bool CircutProblem::ConstraintsSatisfied(SIIW::Solution* solution)
	{
		return false;
	}

	SIIW::Solution* CircutProblem::CreateSolutionObject()
	{
		return new CircutSolution(m_startDestinations.size());
	}

	SIIW::Solution* CircutProblem::CreateRandomSolutionObject()
	{
		CircutSolution* solution = new CircutSolution(m_startDestinations.size());

		for (int i = 0; i < m_startDestinations.size(); i++)
		{
			StartDestination* sd = m_startDestinations[i];

			Path* path = new Path();

			std::vector<Point*> points;
			points.push_back(new Point(sd->start));
			int last_dir = -1;

			while (*(points.back()) != sd->end)
			{
				Point* last_point = points.back();

				int next_dir = last_dir;
				while (next_dir == last_dir)
				{
					next_dir = m_random.GetRandomIntBounded<int>(0, 3);

					if (next_dir == Segment::UP && last_dir == Segment::DOWN)
						next_dir = last_dir;
					else if (next_dir == Segment::DOWN && last_dir == Segment::UP)
						next_dir = last_dir;
					else if (next_dir == Segment::LEFT && last_dir == Segment::RIGHT)
						next_dir = last_dir;
					else if (next_dir == Segment::RIGHT && last_dir == Segment::LEFT)
						next_dir = last_dir;
					else if (next_dir == Segment::UP && last_point->y == 0)
						next_dir = last_dir;
					else if (next_dir == Segment::DOWN && last_point->y == m_sizeY - 1)
						next_dir = last_dir;
					else if (next_dir == Segment::LEFT && last_point->x == 0)
						next_dir = last_dir;
					else if (next_dir == Segment::RIGHT && last_point->x == m_sizeX - 1)
						next_dir = last_dir;
				}
				last_dir = next_dir;

				Point* next_point = new Point(*last_point);
				if (next_dir == Segment::UP)
				{
					next_point->x = last_point->x;

					int max = last_point->y;
					next_point->y -= m_random.GetRandomIntBounded(1, max);
				}
				else if (next_dir == Segment::DOWN)
				{
					next_point->x = last_point->x;

					int max = m_sizeY - last_point->y - 1;
					next_point->y += m_random.GetRandomIntBounded(1, max);
				}
				else if (next_dir == Segment::LEFT)
				{
					next_point->y = last_point->y;

					int max = last_point->x;
					next_point->x -= m_random.GetRandomIntBounded(1, max);
				}
				else
				{
					next_point->y = last_point->y;

					int max = m_sizeX - last_point->x - 1;
					next_point->x += m_random.GetRandomIntBounded(1, max);
				}

				points.push_back(next_point);
			}

			for (size_t i = 1; i < points.size(); i++)
			{
				Point* current_point = points[i];
				Point* last_point = points[i - 1];
				Segment* segment;
				if (last_point->x == current_point->x)
				{
					if (last_point->y > current_point->y)
					{
						segment = new Segment(Segment::UP, last_point->y - current_point->y);
					}
					else
					{
						segment = new Segment(Segment::DOWN, current_point->y - last_point->y);
					}
				}
				else
				{
					if (last_point->x > current_point->x)
					{
						segment = new Segment(Segment::LEFT, last_point->x - current_point->x);
					}
					else
					{
						segment = new Segment(Segment::RIGHT, current_point->x - last_point->x);
					}
				}

				path->segments.push_back(segment);
			}

			solution->SetPath(i, path);

			for (auto p : points)
			{
				if (p != nullptr)
				{
					delete p;
				}
			}
		}

		return solution;
	}

	SIIW::Solution* CircutProblem::CopySolution(SIIW::Solution* solution)
	{
		return new CircutSolution(*((CircutSolution*)solution));
	}

	void CircutProblem::LoadDataFromFile()
	{
		std::string line;
		std::ifstream File(PATH_TO_FILE);

		getline(File, line);

		std::istringstream checker;

		size_t pos;
		pos = line.find_first_of(";");

		checker.str(line.substr(0, pos));
		if (!(checker >> m_sizeX))
			throw SIIW::Exception("Wrong format");
		checker.clear(0);

		line.erase(0, pos + 1);

		checker.str(line);
		if (!(checker >> m_sizeY))
			throw SIIW::Exception("Wrong format");
		checker.clear(0);

		std::vector<StartDestination*> temp_vector;

		while (getline(File, line))
		{
			int x1;
			int x2;
			int y1;
			int y2;

			pos = line.find_first_of(";");
			checker.str(line.substr(0, pos));
			if (!(checker >> x1))
				throw SIIW::Exception("Wrong format");
			checker.clear(0);

			line.erase(0, pos + 1);

			pos = line.find_first_of(";");
			checker.str(line.substr(0, pos));
			if (!(checker >> y1))
				throw SIIW::Exception("Wrong format");
			checker.clear(0);

			line.erase(0, pos + 1);

			pos = line.find_first_of(";");
			checker.str(line.substr(0, pos));
			if (!(checker >> x2))
				throw SIIW::Exception("Wrong format");
			checker.clear(0);

			line.erase(0, pos + 1);

			checker.str(line);
			if (!(checker >> y2))
				throw SIIW::Exception("Wrong format");
			checker.clear(0);

			temp_vector.push_back(new StartDestination(x1, y1, x2, y2));
		}

		for (auto sd : temp_vector)
		{
			m_startDestinations.push_back(sd);
		}
		m_startDestinations.shrink_to_fit();
	}

	SIIW::Solution* CircutProblem::Crossover(SIIW::Solution* a, SIIW::Solution* b)
	{
		CircutSolution* sol_a = (CircutSolution*)a;
		CircutSolution* sol_b = (CircutSolution*)b;

		CircutSolution* result = (CircutSolution*)CreateSolutionObject();

		for (size_t i = 0; i < m_startDestinations.size(); i++)
		{
			if (m_random.GetRandomInt<int>() % 2 == 0)
				result->SetPath(i, new Path(*(sol_a->GetPath(i))));
			else
				result->SetPath(i, new Path(*(sol_b->GetPath(i))));
		}

		return result;
	}

	void CircutProblem::Mutate(SIIW::Solution* solution)
	{
		if (m_random.GetRandomRealBounded<float>(0.0f, 1.0f) < m_mutationAChance)
			MutateA(solution);
		else
			MutateB(solution);
	}

	void CircutProblem::MutateA(SIIW::Solution* solution)
	{
		CircutSolution* circut_solution = (CircutSolution*)solution;
		int path_index = m_random.GetRandomIntBounded<int>(0, m_startDestinations.size() - 1);
		Path* selected_path = circut_solution->GetPath(path_index);
		std::vector<Segment*>& segments = (*selected_path).segments;
		int segments_count = segments.size();

		Point originalStartPoint(m_startDestinations[path_index]->start);
		int segment_index = m_random.GetRandomIntBounded<int>(0, segments_count - 1);
		Segment* current_segment = segments[segment_index];
		for (int i = 0; i < segment_index; i++)
		{
			Segment* temp = segments[i];
			if (temp->direction == Segment::UP)
				originalStartPoint.y -= temp->length;
			else if (temp->direction == Segment::DOWN)
				originalStartPoint.y += temp->length;
			else if (temp->direction == Segment::RIGHT)
				originalStartPoint.x += temp->length;
			else
				originalStartPoint.x -= temp->length;
		}

		int move_dir;
		if (current_segment->direction == Segment::UP || current_segment->direction == Segment::DOWN)
		{
			if (originalStartPoint.x == 0)
				move_dir = Segment::RIGHT;
			else if (originalStartPoint.x == m_sizeX - 1)
				move_dir = Segment::LEFT;
			else if (m_random.GetRandomIntBounded<int>(0, 1) == 0)
				move_dir = Segment::RIGHT;
			else
				move_dir = Segment::LEFT;
		}
		else
		{
			if (originalStartPoint.y == 0)
				move_dir = Segment::DOWN;
			else if (originalStartPoint.y == m_sizeY - 1)
				move_dir = Segment::UP;
			else if (m_random.GetRandomIntBounded<int>(0, 1) == 0)
				move_dir = Segment::DOWN;
			else
				move_dir = Segment::UP;
		}

		if (segments_count == 1)
		{
			segments.insert(segments.begin(), new Segment(move_dir, 1));
			segments.push_back(new Segment(Segment::GetReverseDirection(move_dir), 1));
		}
		else
		{
			if (segment_index == 0)
			{
				Segment* next_segment = segments[1];
				if (next_segment->direction == Segment::GetReverseDirection(move_dir))
					next_segment->length += 1;
				else
				{
					if (next_segment->length == 1)
					{
						delete next_segment;
						segments.erase(segments.begin() + 1);
					}
					else
						next_segment->length--;
				}

				segments.insert(segments.begin(), new Segment(move_dir, 1));

				while (!selected_path->IsCorrect())
					selected_path->FixPath();
			}
			else if (segment_index == segments_count - 1)
			{
				segments.push_back(new Segment(Segment::GetReverseDirection(move_dir), 1));

				Segment* previous_segment = segments[segment_index - 1];
				if (previous_segment->direction == move_dir)
					previous_segment->length++;
				else
				{
					if (previous_segment->length == 1)
					{
						delete previous_segment;
						segments.erase(segments.begin() + segment_index - 1);
					}
					else
						previous_segment->length--;
				}

				while (!selected_path->IsCorrect())
					selected_path->FixPath();
			}
			else
			{
				Segment* next_segment = segments[segment_index + 1];
				if (next_segment->direction == Segment::GetReverseDirection(move_dir))
					next_segment->length += 1;
				else
				{
					if (next_segment->length == 1)
					{
						delete next_segment;
						segments.erase(segments.begin() + segment_index + 1);
					}
					else
						next_segment->length--;
				}

				Segment* previous_segment = segments[segment_index - 1];
				if (previous_segment->direction == move_dir)
					previous_segment->length++;
				else
				{
					if (previous_segment->length == 1)
					{
						delete previous_segment;
						segments.erase(segments.begin() + segment_index - 1);
					}
					else
						previous_segment->length--;
				}

				while (!selected_path->IsCorrect())
					selected_path->FixPath();
			}
		}
	}

	void CircutProblem::MutateB(SIIW::Solution* solution)
	{
		CircutSolution* circut_solution = (CircutSolution*)solution;
		int path_index = m_random.GetRandomIntBounded<int>(0, m_startDestinations.size() - 1);
		Path* selected_path = circut_solution->GetPath(path_index);
		std::vector<Segment*>& segments = (*selected_path).segments;
		int segments_count = segments.size();

		Point originalStartPoint(m_startDestinations[path_index]->start);
		int segment_index = m_random.GetRandomIntBounded<int>(0, segments_count - 1);
		Segment* current_segment = segments[segment_index];
		if (current_segment->length == 1)
			return;

		for (int i = 0; i < segment_index; i++)
		{
			Segment* temp = segments[i];
			if (temp->direction == Segment::UP)
				originalStartPoint.y -= temp->length;
			else if (temp->direction == Segment::DOWN)
				originalStartPoint.y += temp->length;
			else if (temp->direction == Segment::RIGHT)
				originalStartPoint.x += temp->length;
			else
				originalStartPoint.x -= temp->length;
		}

		int move_dir;
		if (current_segment->direction == Segment::UP || current_segment->direction == Segment::DOWN)
		{
			if (originalStartPoint.x == 0)
				move_dir = Segment::RIGHT;
			else if (originalStartPoint.x == m_sizeX - 1)
				move_dir = Segment::LEFT;
			else if (m_random.GetRandomIntBounded<int>(0, 1) == 0)
				move_dir = Segment::RIGHT;
			else
				move_dir = Segment::LEFT;
		}
		else
		{
			if (originalStartPoint.y == 0)
				move_dir = Segment::DOWN;
			else if (originalStartPoint.y == m_sizeY - 1)
				move_dir = Segment::UP;
			else if (m_random.GetRandomIntBounded<int>(0, 1) == 0)
				move_dir = Segment::DOWN;
			else
				move_dir = Segment::UP;
		}

		int new_segment_length = m_random.GetRandomIntBounded<int>(1, current_segment->length - 1);

		if (segments_count == 1 || segment_index == segments_count - 1)
		{
			current_segment->length -= new_segment_length;

			segments.push_back(new Segment(move_dir, 1));
			segments.push_back(new Segment(current_segment->direction, new_segment_length));
			segments.push_back(new Segment(Segment::GetReverseDirection(move_dir), 1));
		}
		else
		{
			current_segment->length -= new_segment_length;
			segments.insert(segments.begin() + segment_index + 1, new Segment(move_dir, 1));
			segments.insert(segments.begin() + segment_index + 2, new Segment(current_segment->direction, new_segment_length));

			Segment* next_segment = segments[segment_index + 3];

			if (next_segment->direction == move_dir)
			{
				next_segment->length--;
				if (next_segment->length == 0)
				{
					delete next_segment;
					segments.erase(segments.begin() + segment_index + 3);
				}
			}
			else if (next_segment->direction == Segment::GetReverseDirection(move_dir))
			{
				next_segment->length++;
			}

			while (!selected_path->IsCorrect())
				selected_path->FixPath();
		}
	}
}