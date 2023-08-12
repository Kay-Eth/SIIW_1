namespace SIIW_Genetic.Exercise
{
    public enum Direction
    {
        Invalid = 0,
        Up = 1,
        Down = 2,
        Left = 3,
        Right = 4,
        Last = 5
    }

    public static class DirectionExtensions
    {
        public static Direction GetReversed(this Direction direction)
        {
            if (direction == Direction.Up) return Direction.Down;
            if (direction == Direction.Down) return Direction.Up;
            if (direction == Direction.Left) return Direction.Right;
            if (direction == Direction.Right) return Direction.Left;

            return Direction.Invalid;
        }
    }
}