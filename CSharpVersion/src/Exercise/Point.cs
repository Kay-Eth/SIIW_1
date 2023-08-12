namespace SIIW_Genetic.Exercise
{
    public class Point
    {
        public int x;
        public int y;

        public Point(int px, int py)
        {
            x = px;
            y = py;
        }

        public Point Copy()
        {
            return new Point(
                x,
                y
            );
        }

        public bool EqualTo(Point other)
        {
            return x == other.x && y == other.y;
        }

        public override string ToString()
        {
            return $"Point ({x} : {y})";
        }
    }
}