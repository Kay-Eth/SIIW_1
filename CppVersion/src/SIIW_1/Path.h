#pragma once

#include <vector>

#include "Segment.h"

namespace SIIW_1
{
	struct Path
	{
		std::vector<Segment*> segments;

		Path()
		{

		}

		Path(const Path& other)
		{
			for (auto s : other.segments)
			{
				segments.push_back(new Segment(*s));
			}
		}

		~Path()
		{
			for (auto s : segments)
			{
				if (s != nullptr)
					delete s;
			}
		}

		bool IsCorrect()
		{
			if (segments.size() == 1)
				return true;

			for (size_t i = 1; i < segments.size(); i++)
			{
				if (segments[i]->direction == segments[i - 1]->direction || segments[i]->direction == Segment::GetReverseDirection(segments[i - 1]->direction))
					return false;
			}

			return true;
		}

		void FixPath()
		{
			if (segments.size() == 1)
				return;

			size_t current_index = 0;
			Segment* current_segment = segments[current_index];
			while (current_segment != segments.back())
			{
				Segment* next_segment = segments[current_index + 1];
				if (current_segment->direction == next_segment->direction)
				{
					current_segment->length += next_segment->length;
					delete next_segment;
					segments.erase(segments.begin() + current_index + 1);
				}
				else if (current_segment->direction == Segment::GetReverseDirection(next_segment->direction))
				{
					if (current_segment->length > next_segment->length)
					{
						current_segment->length -= next_segment->length;
						delete next_segment;
						segments.erase(segments.begin() + current_index + 1);
					}
					else if (current_segment->length < next_segment->length)
					{
						next_segment->length -= current_segment->length;
						delete current_segment;
						segments.erase(segments.begin() + current_index);
					}
					else
					{
						delete current_segment;
						delete next_segment;
						segments.erase(segments.begin() + current_index);
						segments.erase(segments.begin() + current_index);
					}
				}
				else
				{
					current_index++;
				}

				if (current_index >= segments.size())
					current_segment = segments[segments.size() - 1];
				else
					current_segment = segments[current_index];
			}
		}
	};
}