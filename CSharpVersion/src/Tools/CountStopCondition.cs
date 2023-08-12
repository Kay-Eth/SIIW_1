namespace SIIW_Genetic.Tools
{
    public class CountStopCondition : StopCondition
    {
        uint _count;
        uint _repeats;

        public CountStopCondition(uint repeast)
        {
            _count = 1;
            _repeats = repeast;
        }

        public override bool StopConditionSatisfied()
        {
            if (_count > _repeats)
                return true;
            _count += 1;
            return false;
        }
    }
}