using System;
using System.Linq;

namespace SudokuSolver
{
    public class Solver
    {
        public Solver(int [,] gridToSolve)
        {
            this.gridToSolve = gridToSolve;
        }
        private readonly int[,] gridToSolve;

        private bool CanPlaceNumber(int row, int col, int number)
        {
            var boxStartRow    = row - row % 3;
            var boxStartColumn = col - col % 3;

            var canPlaceInRow = 
                Enumerable
                    .Range(0, gridToSolve.GetUpperBound(1))
                    .All(gridCol => gridToSolve[row, gridCol] != number);

            var canPlaceInColumn =
                Enumerable
                    .Range(0, gridToSolve.GetUpperBound(0))
                    .All(gridRow => gridToSolve[gridRow, col] != number);

            var canPlaceInBox = true;

            for (var i = 0; i < 3 && canPlaceInBox; i++)
            {
                for (var j = 0; j < 3 && canPlaceInBox; j++)
                {
                    if (gridToSolve[boxStartRow + i, boxStartColumn + j] == number)
                        canPlaceInBox = false;
                }   
            }

            return canPlaceInRow && canPlaceInColumn && canPlaceInBox;
        }

        private Tuple<bool, int, int> FindNextUnsolvedPositionIfExists()
        {
            for (var i = 0; i <= gridToSolve.GetUpperBound(0); i++)
            {
                for (var j = 0; j <= gridToSolve.GetUpperBound(1); j++)
                {
                    if(gridToSolve[i, j] == 0)
                        return new Tuple<bool, int, int>(true, i, j);
                }
            }
            return new Tuple<bool, int, int>(false, int.MinValue, int.MinValue);
        }

        private bool CanFillNextUnsolvedPosition()
        {
            var nextUnsolvedPosition = FindNextUnsolvedPositionIfExists();
            if (!nextUnsolvedPosition.Item1)
                return true;

            var possibleNumbers =
                Enumerable
                    .Range(1, 9)
                    .Where(number => CanPlaceNumber(nextUnsolvedPosition.Item2, nextUnsolvedPosition.Item3, number));

            foreach (var possibleNumber in possibleNumbers)
            {
                gridToSolve[nextUnsolvedPosition.Item2, nextUnsolvedPosition.Item3] = possibleNumber;

                if (CanFillNextUnsolvedPosition())
                    return true;

                gridToSolve[nextUnsolvedPosition.Item2, nextUnsolvedPosition.Item3] = 0;
            }

            return false;
        }

        public Result TrySolve()
        {
            var canBeSolved = CanFillNextUnsolvedPosition();
            return canBeSolved
                ? new Result(true, gridToSolve)
                : new Result(false, null);
        }

        public class Result
        {
            public Result(
                bool    canBeSolved, 
                int[,]  solvedGrid)
            {
                CanBeSolved = canBeSolved;
                SolvedGrid  = solvedGrid;
            }

            public bool     CanBeSolved     { get; private set; }
            public int[,]   SolvedGrid      { get; private set; }
        }
    }
}