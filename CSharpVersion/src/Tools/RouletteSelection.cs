using System;
using System.Collections.Generic;

namespace SIIW_Genetic.Tools
{
    public class RouletteSelection : Selection
    {
        Random _random = new Random();

        public override Solution Select(Dictionary<Solution, double> solutionsMap)
        {
            //double sum = 0;
            //foreach (var kv_pair in solutionsMap)
            //{
            //    sum += kv_pair.Value;
            //}
            //double val = _random.NextDouble() * sum;
            //double pointer = 0.0;

            //foreach (var kv_pair in solutionsMap)
            //{
            //    pointer += kv_pair.Value;
            //    if (val <= pointer)
            //    {
            //        return kv_pair.Key;
            //    }
            //}

            //return null;

            double min = double.PositiveInfinity;
            double max = double.NegativeInfinity;
            foreach (var kv_pair in solutionsMap)
            {
                if (kv_pair.Value < min)
                    min = kv_pair.Value;
                if (kv_pair.Value > max)
                    max = kv_pair.Value;
            }
            double sum_min_max = max + min;

            double sum = 0;
            foreach (var kv_pair in solutionsMap)
            {
                sum += sum_min_max - kv_pair.Value;
            }

            double val = _random.NextDouble() * sum;
            double pointer = 0.0;

            foreach (var kv_pair in solutionsMap)
            {
                pointer += sum_min_max - kv_pair.Value;
                if (val <= pointer)
                {
                    return kv_pair.Key;
                }
            }

            return null;
        }
    }
}
