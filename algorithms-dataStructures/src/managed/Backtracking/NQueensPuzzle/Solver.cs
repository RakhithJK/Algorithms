using System;
using System.Collections.Generic;
using System.Linq;

namespace NQueensPuzzle
{
    public class Solver
    {
        public Solver(int chessboardSize)
        {
            this.chessboardSize = chessboardSize;
        }

        private readonly    int                     chessboardSize;
        private             List<Tuple<int, int>>   placedQueens;
        private             int[,]                  chessboard;

        public class Result
        {
            public Result(
                bool                            canBeSolved, 
                int[,]                          chessboard, 
                IEnumerable<Tuple<int, int>>    placedQueensPositions
            )
            {
                CanBeSolved             = canBeSolved;
                Chessboard              = chessboard;
                PlacedQueensPositions   = placedQueensPositions;
            }

            public bool                             CanBeSolved             { get; private set; }
            public int[,]                           Chessboard              { get; private set; }
            public IEnumerable<Tuple<int, int>>     PlacedQueensPositions   { get; private set; }
        }

        private bool ArePositionsAttacking(Tuple<int, int> lhs, Tuple<int, int> rhs)
            =>
                lhs.Item1 == rhs.Item1 ||                                           // same row
                lhs.Item2 == rhs.Item2 ||                                           // same column
                Math.Abs(rhs.Item1 - lhs.Item1) == Math.Abs(rhs.Item2 - lhs.Item2); // on diagonals -> on same line actually

        private bool IsPositionAttackedByPlacedQueens(Tuple<int, int> position)
            => placedQueens.Any(queenPosition => ArePositionsAttacking(position, queenPosition));

        private bool CanPlaceQueenAtPosition(Tuple<int, int> position) => !IsPositionAttackedByPlacedQueens(position);

        public bool CanPlaceRestOfTheQueens(int currentRow)
        {
            if (placedQueens.Count == chessboardSize)
                return true;

            var possibleQueenPositionsInCurrentRow = new List<Tuple<int, int>>(chessboardSize);

            for (int column = 0; column < chessboardSize; column++)
            {
                var position = new Tuple<int, int>(currentRow, column);
                if(CanPlaceQueenAtPosition(position))
                    possibleQueenPositionsInCurrentRow.Add(position);
            }

            foreach (var queenPosition in possibleQueenPositionsInCurrentRow)
            {
                placedQueens.Add(queenPosition);
                chessboard[queenPosition.Item1, queenPosition.Item2] = 1;

                if (CanPlaceRestOfTheQueens(currentRow + 1))
                    return true;

                chessboard[queenPosition.Item1, queenPosition.Item2] = 0;
                placedQueens.Remove(queenPosition);
            }

            return false;
        }

        public Result TrySolve()
        {
            this.chessboard   = new int[chessboardSize, chessboardSize];
            this.placedQueens = new List<Tuple<int, int>>(chessboardSize);
            var canBeSolved   = CanPlaceRestOfTheQueens(0);
            return canBeSolved
                ? new Result(true, chessboard, this.placedQueens)
                : new Result(false, null, null);
        }
    }
}
