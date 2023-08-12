using System;
using System.Collections.Generic;
using System.Linq;

namespace SIIW_Genetic.Tools
{
    public class TournamentSelection : Selection
    {
        int _tournamentSize;
        Random _random = new Random();

        public TournamentSelection(int tournamentSize)
        {
            _tournamentSize = tournamentSize;
        }

        public override Solution Select(Dictionary<Solution, double> solutionsMap)
        {
            Solution result = null;

            Dictionary<Solution, double> tempMap = new Dictionary<Solution, double>(solutionsMap);
            List<Solution> tournament = new List<Solution>();

            for (int i = 0; i < _tournamentSize && i < solutionsMap.Count; i++)
            {
                Solution sol = tempMap.Keys.ToArray()[_random.Next(0, tempMap.Count)];
                tournament.Add(sol);
                tempMap.Remove(sol);
            }

            result = tournament.First();
            double best_val = solutionsMap[result];
            for (int i = 1; i < tournament.Count; i++)
            {
                Solution current = tournament[i];
                double current_val = solutionsMap[current];
                if (current_val < best_val)
                {
                    result = current;
                    best_val = current_val;
                }
            }

            return result;
        }
    }
}
