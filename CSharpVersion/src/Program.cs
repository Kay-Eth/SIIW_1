using SIIW_Genetic.Exercise;
using SIIW_Genetic.Tools;
using System;

namespace SIIW_Genetic
{
    class Program
    {
        static void Main(string[] args)
        {
            for (int i = 0; i < 10; i++)
            {
                CircutProblem problem = new CircutProblem(0.5f);
                CountStopCondition stopCondition = new CountStopCondition(1000);
                //TournamentSelection selection = new TournamentSelection(30);
                RouletteSelection selection = new RouletteSelection();
                GeneticSearch search = new GeneticSearch(problem, stopCondition, selection, 500, 0.9, 0.2);
                //RandomSearch search = new RandomSearch(problem, stopCondition);

                var watch = System.Diagnostics.Stopwatch.StartNew();
                search.SearchForBestSolution();
                watch.Stop();
                //search.GetBestSolution().PrettyPrint();

                //Console.Write($"Best solution quality: {search.GetBestQuality()} \n\n");
                
                search.Clean();

                var elapsedMs = watch.ElapsedMilliseconds;
                //Console.WriteLine($"Time: {elapsedMs}ms");
                Console.WriteLine($"{search.GetBestQuality()} - {(double)elapsedMs / 1000.0}s");
            }

            Console.WriteLine($"\nKoniec");
            Console.ReadKey();
        }
    }
}
