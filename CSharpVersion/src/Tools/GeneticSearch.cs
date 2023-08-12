using System;
using System.Collections.Generic;
using System.IO;

namespace SIIW_Genetic.Tools
{
    public class GeneticSearch : Search
    {
        public const string FILE_PREFIX = "results/Genetic_Search_";
        public const string FILE_POSTFIX = ".txt";
        public readonly string _fileName;

        Random _random;
        int _populationSize;
        double _crossoverChance;
        double _mutationChance;
        Selection _selection;

        StreamWriter _streamWriter;

        public GeneticSearch(Problem problem, StopCondition stopCondition, Selection selection, int populationSize, double crossoverChance, double mutationChance, int seed = 0)
            : base(problem, stopCondition)
        {
            _selection = selection;
            _populationSize = populationSize;
            _crossoverChance = crossoverChance;
            _mutationChance = mutationChance;
            _random = new Random();

            var now = DateTime.Now;
            _fileName = $"{FILE_PREFIX}{now.Year}_{now.Month}_{now.Day}_{now.Hour}_{now.Minute}_{now.Second}_{now.Millisecond}{FILE_POSTFIX}";

            _streamWriter = new StreamWriter(_fileName);
        }

        public override void SearchForBestSolution()
        {
            Dictionary<Solution, double> population = new Dictionary<Solution, double>();
            for (int i = 0; i < _populationSize; i++)
            {
                Solution solution = _problem.CreateRandomSolutionObject();
                double quality = _problem.GetQuality(solution);

                population.Add(solution, quality);
            }

            int count = 0;
            while (!_stopCondition.StopConditionSatisfied())
            {
                count++;
                Dictionary<Solution, double> new_population = new Dictionary<Solution, double>();
                while (new_population.Count != _populationSize)
                {
                    Solution p1 = _selection.Select(population);
                    Solution p2 = _selection.Select(population);
                    Solution new_solution;

                    if (_random.NextDouble() < _crossoverChance)
                        new_solution = _problem.Crossover(p1, p2);
                    else
                        new_solution = _problem.CopySolution(_random.Next(0, 2) == 0 ? p1 : p2);

                    if (_random.NextDouble() < _mutationChance)
                        _problem.Mutate(new_solution);

                    double quality = _problem.GetQuality(new_solution);
                    new_population.Add(new_solution, quality);

                    if (quality < _bestSolutionQuality)
                    {
                        _bestSolutionQuality = quality;
                        _bestSolution = new_solution;
                    }
                }

                population = new_population;

                //if (count % 100 == 0)
                //    Console.WriteLine(count);

                _streamWriter.WriteLine(count.ToString() + ";" + _bestSolutionQuality.ToString());
            }
        }

        public void Clean()
        {
            _streamWriter.Close();
        }
    }
}
