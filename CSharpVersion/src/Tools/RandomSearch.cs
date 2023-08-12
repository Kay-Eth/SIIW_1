using System;
using System.IO;

namespace SIIW_Genetic.Tools
{
    public class RandomSearch : Search
    {
        public const string FILE_PREFIX = "results/Random_Search_";
        public const string FILE_POSTFIX = ".txt";
        public readonly string _fileName;

        Random _random;

        StreamWriter _streamWriter;

        public RandomSearch(Problem problem, StopCondition stopCondition, int seed = 0)
            : base(problem, stopCondition)
        {
            _random = new Random(seed);

            var now = DateTime.Now;
            _fileName = $"{FILE_PREFIX}{now.Year}_{now.Month}_{now.Day}_{now.Hour}_{now.Minute}_{now.Second}_{now.Millisecond}{FILE_POSTFIX}";

            _streamWriter = new StreamWriter(_fileName);
        }

        public override void SearchForBestSolution()
        {
            Solution current_solution = null;
            int count = 0;
            while (!_stopCondition.StopConditionSatisfied())
            {
                count++;
                current_solution = _problem.CreateRandomSolutionObject();
                double current_quality = _problem.GetQuality(current_solution);

                if (current_quality < _bestSolutionQuality)
                {
                    _bestSolution = current_solution;
                    _bestSolutionQuality = current_quality;
                }

                _streamWriter.WriteLine(count.ToString() + ";" + _bestSolutionQuality.ToString());
            }
        }

        public void Clean()
        {
            _streamWriter.Close();
        }
    }
}