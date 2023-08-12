using System.Collections.Generic;

namespace SIIW_Genetic.Tools
{
    public abstract class Selection
    {
        public abstract Solution Select(Dictionary<Solution, double> solutionsMap);
    }
}
