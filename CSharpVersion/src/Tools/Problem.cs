namespace SIIW_Genetic.Tools
{
    public abstract class Problem
    {
        public abstract double GetQuality(Solution solution);
        public abstract Solution CreateSolutionObject();
        public abstract Solution CreateRandomSolutionObject();
        public abstract Solution CopySolution(Solution solution);

        public abstract Solution Crossover(Solution a, Solution b);
        public abstract void Mutate(Solution solution);
    }
}