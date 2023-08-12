namespace SIIW_Genetic.Exercise
{
    public class StartDestination
    {
        public Point start;
        public Point end;

        public StartDestination(int sx, int sy, int ex, int ey)
        {
            start = new Point(sx, sy);
            end = new Point(ex, ey);
        }
    }
}