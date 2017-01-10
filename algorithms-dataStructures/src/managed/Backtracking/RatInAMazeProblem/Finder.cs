using System;

namespace RatInAMazeProblem
{
    public class Finder
    {
        public Finder(
            bool[,]         maze, 
            Tuple<int, int> startPosition,
            Tuple<int, int> destinationPosition 
        )
        {
            this.maze                = maze;
            this.startPosition       = startPosition;
            this.destinationPosition = destinationPosition;
        }

        public class Result
        {
            public Result(bool isFound, int[,] path)
            {
                IsFound = isFound;
                Path    = path;
            }

            public bool     IsFound { get; private set; }
            public int[,]   Path { get; private set; }
        }

        private readonly bool[,]            maze;
        private readonly Tuple<int, int>    startPosition;
        private readonly Tuple<int, int>    destinationPosition;
        private          int[,]             solutionMatrix;
        private          int                pathLength;
        private bool IsInMatrix(int row, int col)
            => row >= 0 && col >= 0 && row <= maze.GetUpperBound(0) && col <= maze.GetUpperBound(1);

        private bool CanReachRestOfThePath(int row, int column)
        {
            if (destinationPosition.Item1 == row && destinationPosition.Item2 == column)
            {
                pathLength++;
                solutionMatrix[row, column] = pathLength;
                return true;
            }

            if (maze[row, column] == false)
                return false;

            pathLength++;
            solutionMatrix[row, column] = pathLength;

            var rowOffsets    = new[] { 0, 0, 1, -1 };
            var columnOffsets = new[] { 1, -1, 0, 0 };

            for (int i = 0; i < 4; i++)
            {
                var position = new Tuple<int, int>(row + rowOffsets[i], column + columnOffsets[i]);
                if (
                    IsInMatrix              (position.Item1, position.Item2)          &&
                    solutionMatrix          [position.Item1, position.Item2] == 0     &&
                    CanReachRestOfThePath   (position.Item1, position.Item2)   
                )
                {
                    return true;
                }
            }

            pathLength--;
            solutionMatrix[row, column] = 0;
            return false;
        }

        public Result TryFind()
        {
            solutionMatrix = new int[maze.GetUpperBound(0) + 1, maze.GetUpperBound(1) + 1];
            pathLength     = 0;
            var canReachDestination = CanReachRestOfThePath(startPosition.Item1, startPosition.Item2);
            return canReachDestination
                ? new Result(true, solutionMatrix)
                : new Result(false, null); 
        }
    }
}
