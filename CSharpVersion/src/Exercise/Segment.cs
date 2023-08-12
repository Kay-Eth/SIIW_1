using System.Collections.Generic;

namespace SIIW_Genetic.Exercise
{
    public class Segment
    {
        public Direction direction;
        public int length;

        public Segment(Direction dir, int len)
        {
            direction = dir;
            length = len;
        }

        public Segment Copy()
        {
            return new Segment(direction, length);
        }
    }
}