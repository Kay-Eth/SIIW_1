using SIIW_Genetic.Tools;
using System;
using System.Collections.Generic;
using System.IO;

namespace SIIW_Genetic.Exercise
{
    public class CircutProblem : Problem
    {
        public const string PATH_TO_FILE = "data/SIIW_1/data.txt";
        public const int INTERSECTION_PENALTY = 10;

        int _boardSizeX;
        int _boardSizeY;
        StartDestination[] _startDestinations;

        float _mutationAChance;

        Random _random;

        public CircutProblem(float mutationAChance)
        {
            LoadDataFromFile();

            _random = new Random();
            _mutationAChance = mutationAChance;
        }

        private void LoadDataFromFile()
        {
            List<StartDestination> temp_sdlist = new List<StartDestination>();
            using(StreamReader file = new StreamReader(PATH_TO_FILE))
            {
                string line = file.ReadLine();
                var temp = line.Split(';');
                _boardSizeX = int.Parse(temp[0]);
                _boardSizeY = int.Parse(temp[1]);

                while ((line = file.ReadLine()) != null)
                {
                    var temp_arr = line.Split(';');

                    temp_sdlist.Add(new StartDestination(
                        int.Parse(temp_arr[0]),
                        int.Parse(temp_arr[1]),
                        int.Parse(temp_arr[2]),
                        int.Parse(temp_arr[3])
                    ));
                }  
                file.Close();
            }

            _startDestinations = new StartDestination[temp_sdlist.Count];
            for (int i = 0; i < _startDestinations.Length; i++)
            {
                _startDestinations[i] = temp_sdlist[i];
            }
        }

        public override Solution CopySolution(Solution solution)
        {
            return ((CircutSolution)solution).Copy();
        }

        public override Solution CreateRandomSolutionObject()
        {
            CircutSolution solution = new CircutSolution(_startDestinations.Length);

            for (int i = 0; i < _startDestinations.Length; i++)
            {
                StartDestination current_sd = _startDestinations[i];

                Path path = new Path();

                List<Point> points = new List<Point>();
                points.Add(current_sd.start.Copy());
                Direction last_dir = Direction.Invalid;

                while (!points[points.Count - 1].EqualTo(current_sd.end))
                {
                    Point last_point = points[points.Count - 1];

                    Direction next_dir = last_dir;
                    while (next_dir == last_dir)
                    {
                        next_dir = (Direction)_random.Next(1, (int)Direction.Last);

                        if (next_dir == Direction.Up && last_dir == Direction.Down)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Down && last_dir == Direction.Up)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Left && last_dir == Direction.Right)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Right && last_dir == Direction.Left)
                            next_dir = last_dir;
                        
                        else if (next_dir == Direction.Up && last_point.y == 0)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Down && last_point.y == _boardSizeY - 1)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Left && last_point.x == 0)
                            next_dir = last_dir;
                        else if (next_dir == Direction.Right && last_point.x == _boardSizeX - 1)
                            next_dir = last_dir;
                    }
                    last_dir = next_dir;

                    Point next_point = last_point.Copy();
                    if (next_dir == Direction.Up)
                    {
                        next_point.x = last_point.x;

                        int max = last_point.y;
                        next_point.y -= _random.Next(1, max + 1);
                    }
                    else if (next_dir == Direction.Down)
                    {
                        next_point.x = last_point.x;

                        int max = _boardSizeY - last_point.y - 1;
                        next_point.y += _random.Next(1, max + 1);
                    }
                    else if (next_dir == Direction.Left)
                    {
                        next_point.y = last_point.y;

                        int max = last_point.x;
                        next_point.x -= _random.Next(1, max + 1);
                    }
                    else
                    {
                        next_point.y = last_point.y;

                        int max = _boardSizeX - last_point.x - 1;
                        next_point.x += _random.Next(1, max + 1);
                    }

                    points.Add(next_point);
                }

                for (int j = 1; j < points.Count; j++)
                {
                    Point current_point = points[j];
                    Point last_point = points[j - 1];
                    Segment segment;

                    if (last_point.x == current_point.x)
                    {
                        if (last_point.y > current_point.y)
                            segment = new Segment(Direction.Up, last_point.y - current_point.y);
                        else
                            segment = new Segment(Direction.Down, current_point.y - last_point.y);
                    }
                    else
                    {
                        if (last_point.x > current_point.x)
                            segment = new Segment(Direction.Left, last_point.x - current_point.x);
                        else
                            segment = new Segment(Direction.Right, current_point.x - last_point.x);
                    }

                    path.segments.Add(segment);
                }

                solution.SetPath(i, path);
            }

            return solution;
        }

        public override Solution CreateSolutionObject()
        {
            return new CircutSolution(_startDestinations.Length);
        }

        public override double GetQuality(Solution solution)
        {
            CircutSolution sol = (CircutSolution)solution;

            int[] map = new int[_boardSizeX * _boardSizeY];
            for (int i = 0; i < map.Length; i++)
            {
                map[i] = 0;
            }

            long length = 0;
            long count_of_segments = 0;
            
            for (int i = 0; i < _startDestinations.Length; i++)
            {
                Point current_point = _startDestinations[i].start.Copy();
                Path path = sol.GetPath(i);
                
                map[current_point.x + current_point.y * _boardSizeX] += 1;
                foreach (Segment segment in path.segments)
                {
                    length += segment.length;
                    count_of_segments++;

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
                        map[current_point.x + current_point.y * _boardSizeX]++;
                    }
                }
            }

            long intersections = 0;
            for (int x = 0; x < _boardSizeX; x++)
            {
                for (int y = 0; y < _boardSizeY; y++)
                {
                    if (map[x + y * _boardSizeX] > 1)
                        intersections += map[x + y * _boardSizeX] * INTERSECTION_PENALTY;
                }
            }

            double result = length + count_of_segments + intersections;

            return result;
        }

        public override Solution Crossover(Solution a, Solution b)
        {
            CircutSolution p1 = (CircutSolution)a;
            CircutSolution p2 = (CircutSolution)b;

            CircutSolution result = (CircutSolution)CreateSolutionObject();

            for (int i = 0; i < _startDestinations.Length; i++)
            {
                if (_random.Next() % 2 == 0)
                    result.SetPath(i, p1.GetPath(i).Copy());
                else
                    result.SetPath(i, p2.GetPath(i).Copy());
            }

            return result;
        }

        public override void Mutate(Solution solution)
        {
            if (_random.NextDouble() < _mutationAChance)
                MutateA(solution);
            else
                MutateB(solution);

            //MutateA(solution);
        }

        void MutateA(Solution solution)
        {
            CircutSolution circut_solution = (CircutSolution)solution;
            int path_index = _random.Next(0, _startDestinations.Length);
            Path selected_path = circut_solution.GetPath(path_index);
            List<Segment> segments = selected_path.segments;
            int segments_count = segments.Count;

            Point originalStartPoint = _startDestinations[path_index].start.Copy();
            //selected_path.Print(originalStartPoint);
            int segment_index = _random.Next(0, segments_count);
            Segment current_segment = segments[segment_index];
            for (int i = 0; i < segment_index + 1; i++)
            {
                Segment temp = segments[i];
                if (temp.direction == Direction.Up)
                    originalStartPoint.y -= temp.length;
                else if (temp.direction == Direction.Down)
                    originalStartPoint.y += temp.length;
                else if (temp.direction == Direction.Right)
                    originalStartPoint.x += temp.length;
                else
                    originalStartPoint.x -= temp.length;
            }

            Direction move_dir;
            if (current_segment.direction == Direction.Up || current_segment.direction == Direction.Down)
            {
                if (originalStartPoint.x == 0)
                    move_dir = Direction.Right;
                else if (originalStartPoint.x == _boardSizeX - 1)
                    move_dir = Direction.Left;
                else if (_random.Next() % 2 == 0)
                    move_dir = Direction.Right;
                else
                    move_dir = Direction.Left;
            }
            else
            {
                if (originalStartPoint.y == 0)
                    move_dir = Direction.Down;
                else if (originalStartPoint.y == _boardSizeY - 1)
                    move_dir = Direction.Up;
                else if (_random.Next() % 2 == 0)
                    move_dir = Direction.Down;
                else
                    move_dir = Direction.Up;
            }

            if (segments_count == 1)
            {
                segments.Insert(0, new Segment(move_dir, 1));
                segments.Add(new Segment(move_dir.GetReversed(), 1));
            }
            else
            {
                if (segment_index == segments_count - 1)
                {
                    segments.Add(new Segment(move_dir.GetReversed(), 1));
                }
                else
                {
                    Segment next_segment = segments[segment_index + 1];
                    if (next_segment.direction == move_dir.GetReversed())
                        next_segment.length += 1;
                    else
                    {
                        if (next_segment.length == 1)
                            segments.Remove(next_segment);
                        else
                            next_segment.length--;
                    }
                }

                if (segment_index == 0)
                {
                    segments.Insert(0, new Segment(move_dir, 1));
                }
                else
                {
                    Segment previous_segment = segments[segment_index - 1];
                    if (previous_segment.direction == move_dir)
                        previous_segment.length++;
                    else
                    {
                        if (previous_segment.length == 1)
                            segments.Remove(previous_segment);
                        else
                            previous_segment.length--;
                    }
                }

                //try
                //{
                //    selected_path.CheckCorrectness(_startDestinations[path_index].start);
                //}
                //catch (Exception e)
                //{
                //    selected_path.Print(_startDestinations[path_index].start);
                //    throw new Exception();
                //}

                while (!selected_path.IsCorrect())
                    selected_path.FixPath();
            }
        }

        void MutateB(Solution solution)
        {
            CircutSolution circut_solution = (CircutSolution)solution;
            int path_index = _random.Next(0, _startDestinations.Length);
            Path selected_path = circut_solution.GetPath(path_index);
            List<Segment> segments = selected_path.segments;
            int segments_count = segments.Count;

            Point originalStartPoint = _startDestinations[path_index].start.Copy();
            int segment_index = _random.Next(0, segments_count);
            Segment current_segment = segments[segment_index];
            if (current_segment.length == 1)
                return;

            for (int i = 0; i < segment_index; i++)
            {
                Segment temp = segments[i];
                if (temp.direction == Direction.Up)
                    originalStartPoint.y -= temp.length;
                else if (temp.direction == Direction.Down)
                    originalStartPoint.y += temp.length;
                else if (temp.direction == Direction.Right)
                    originalStartPoint.x += temp.length;
                else
                    originalStartPoint.x -= temp.length;
            }

            Direction move_dir;
            if (current_segment.direction == Direction.Up || current_segment.direction == Direction.Down)
            {
                if (originalStartPoint.x == 0)
                    move_dir = Direction.Right;
                else if (originalStartPoint.x == _boardSizeX - 1)
                    move_dir = Direction.Left;
                else if (_random.Next() % 2 == 0)
                    move_dir = Direction.Right;
                else
                    move_dir = Direction.Left;
            }
            else
            {
                if (originalStartPoint.y == 0)
                    move_dir = Direction.Down;
                else if (originalStartPoint.y == _boardSizeY - 1)
                    move_dir = Direction.Up;
                else if (_random.Next() % 2 == 0)
                    move_dir = Direction.Down;
                else
                    move_dir = Direction.Up;
            }

            int new_segment_length = _random.Next(1, current_segment.length);

            if (segments_count == 1 || segment_index == segments_count - 1)
            {
                current_segment.length -= new_segment_length;

                segments.Add(new Segment(move_dir, 1));
                segments.Add(new Segment(current_segment.direction, new_segment_length));
                segments.Add(new Segment(move_dir.GetReversed(), 1));
            }
            else
            {
                current_segment.length -= new_segment_length;
                segments.Insert(segment_index + 1, new Segment(move_dir, 1));
                segments.Insert(segment_index + 2, new Segment(current_segment.direction, new_segment_length));

                Segment next_segment = segments[segment_index + 3];

                if (next_segment.direction == move_dir)
                {
                    next_segment.length--;
                    if (next_segment.length == 0)
                    {
                        segments.Remove(next_segment);
                    }
                }
                else if (next_segment.direction == move_dir.GetReversed())
                {
                    next_segment.length++;
                }

                while (!selected_path.IsCorrect())
                    selected_path.FixPath();
            }
        }
    }
}