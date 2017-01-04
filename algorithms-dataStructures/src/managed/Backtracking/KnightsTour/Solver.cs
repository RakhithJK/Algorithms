using System.Collections.Generic;
using System.Linq;

namespace KnightsTour
{
    public class Solver
    {
        private int[,] path;
        private int    pathLength;
        
        public class Result
        {
            public Result(bool canBeSolved, int[,] path)
            {
                CanBeSolved = canBeSolved;
                Path        = path;
            }

            public bool   CanBeSolved { get; private set; }
            public int[,] Path        { get; private set; }
        }

        private bool IsInMatrix(int row, int col, int n)
            => row >= 0 && col >= 0 && row < n && col < n;

        public bool Solve(int row, int column, int n)
        {
            pathLength++;
            path[row, column] = pathLength;

            if (pathLength == n*n)
                return true;

            var possibleDirections = new List<int[]>();
            var rowOffsets         = new int[] { 2, 1, -1, -2, -2, -1, 1, 2 };
            var colOffsets         = new int[] { 1, 2, 2, 1, -1, -2, -2, -1 };

            for (int i = 0; i < 8; i++)
            {
                var possibleDirection = new int[] { row + rowOffsets[i], column + colOffsets[i] };
                if(IsInMatrix(possibleDirection[0], possibleDirection[1], n) && path[possibleDirection[0], possibleDirection[1]] == 0)
                    possibleDirections.Add(possibleDirection);
            }

            if (possibleDirections.Any(direction => Solve(direction[0], direction[1], n)))
            {
                return true;
            }

            path[row, column] = 0;
            pathLength--;
            return false;
        }

        public Result Solve(int n)
        {
            path = new int[n,n];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    path[i, j] = 0;
                }
            }

            var canBeSolved = Solve(0, 0, n);
            return new Result(canBeSolved, path);
        }
    }
}
