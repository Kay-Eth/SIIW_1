using System;
using System.Collections.Generic;

namespace SIIW_Genetic.Exercise
{
    public class Path
    {
        public List<Segment> segments;

        public Path()
        {
            segments = new List<Segment>();
        }

        public Path Copy()
        {
            Path copy = new Path();
            foreach (var segment in segments)
            {
                copy.segments.Add(segment.Copy());
            }
            return copy;
        }

        public bool IsCorrect()
        {
            if (segments.Count < 2)
                return true;

            for (int i = 1; i < segments.Count; i++)
            {
                if (segments[i].direction == segments[i - 1].direction || segments[i].direction == segments[i - 1].direction.GetReversed())
                    return false;
            }

            return true;
        }

        public void CheckCorrectness(Point start)
        {
            Point current_point = start.Copy();
            foreach (Segment segment in segments)
            {
                Point increment;
                if (segment.direction == Direction.Up)
                    increment = new Point(0, -1);
                else if (segment.direction == Direction.Down)
                    increment = new Point(0, 1);
                else if (segment.direction == Direction.Left)
                    increment = new Point(-1, 0);
                else
                    increment = new Point(1, 0);

                for (int j = 0; j < segment.length; j++)
                {
                    current_point.x += increment.x;
                    current_point.y += increment.y;
                    if (current_point.x < 0 || current_point.x > 15 || current_point.y < 0 || current_point.y > 15)
                        throw new System.Exception();
                }
            }
        }

        public void Print(Point start)
        {
            Point current_point = start.Copy();
            Console.WriteLine(current_point.ToString());
            for (int i = 0; i < segments.Count; i++)
            {
                Segment segment = segments[i];
                if (segment.direction == Direction.Up)
                    current_point.y -= segment.length;
                else if (segment.direction == Direction.Down)
                    current_point.y += segment.length;
                else if (segment.direction == Direction.Left)
                    current_point.x -= segment.length;
                else
                    current_point.x += segment.length;

                Console.WriteLine($"[{i}]\t{segment.direction} {segment.length} -> {current_point.ToString()}");
            }
        }

        public void FixPath()
        {
            if (segments.Count < 2)
                return;

            int current_index = 0;
            Segment current_segment = segments[current_index];
            while (current_segment != segments[segments.Count - 1])
            {
                Segment next_segment = segments[current_index + 1];
                if (current_segment.direction == next_segment.direction)
                {
                    current_segment.length += next_segment.length;
                    segments.Remove(next_segment);
                }
                else if (current_segment.direction == next_segment.direction.GetReversed())
                {
                    if (current_segment.length > next_segment.length)
                    {
                        current_segment.length -= next_segment.length;
                        segments.Remove(next_segment);
                    }
                    else if (current_segment.length < next_segment.length)
                    {
                        next_segment.length -= current_segment.length;
                        segments.Remove(current_segment);
                    }
                    else
                    {
                        segments.Remove(current_segment);
                        segments.Remove(next_segment);
                    }
                }
                else
                {
                    current_index++;
                }

                if (current_index >= segments.Count)
                    current_segment = segments[segments.Count - 1];
                else
                    current_segment = segments[current_index];
            }
        }
    }
}