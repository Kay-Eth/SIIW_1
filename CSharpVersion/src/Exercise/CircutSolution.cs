using SIIW_Genetic.Tools;
using System;
using System.Collections.Generic;

namespace SIIW_Genetic.Exercise
{
    public class CircutSolution : Solution
    {
        private int _pathCount;
        private Path[] _paths;

        public CircutSolution(int pathCount)
        {
            _pathCount = pathCount;
            _paths = new Path[pathCount];
        }

        public CircutSolution Copy()
        {
            CircutSolution copy = new CircutSolution(_pathCount);
            for (int i = 0; i < _pathCount; i++)
            {
                copy.SetPath(i, _paths[i].Copy());
            }
            return copy;
        }

        public void SetPath(int index, Path path)
        {
            if (index < 0 || index >= _pathCount)
			    throw new IndexOutOfRangeException();

            _paths[index] = path;
        }

        public Path GetPath(int index)
        {
            if (index < 0 || index >= _pathCount)
			    throw new IndexOutOfRangeException();

            return _paths[index];
        }

        public override void PrettyPrint()
        {
            for (int i = 0; i < _pathCount; i++)
            {
                Console.Write($"Path {i}: \n\t");

                foreach (Segment segment in _paths[i].segments)
                {
                    Console.Write($"{segment.direction} {segment.length}; ");
                }
                Console.Write("\n\n");
            }
        }
    }
}