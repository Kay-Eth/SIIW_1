namespace SIIW_Genetic.Tools
{
    public abstract class Search
    {
        protected double _bestSolutionQuality;
        protected Problem _problem;
        protected Solution _bestSolution;
        protected StopCondition _stopCondition;

        public Search(Problem problem, StopCondition stopCondition)
        {
            _bestSolution = null;
            _bestSolutionQuality = double.PositiveInfinity;
            _stopCondition = stopCondition;
            _problem = problem;
        }

        public abstract void SearchForBestSolution();

        public Solution GetBestSolution() { return _bestSolution; }
        public double GetBestQuality() { return _bestSolutionQuality; }
    }
}