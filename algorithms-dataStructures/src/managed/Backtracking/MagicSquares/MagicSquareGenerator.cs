using System;
using System.Collections.Generic;
using System.Linq;

namespace MagicSquares
{
    public class MagicSquareGenerator
    {
        public MagicSquareGenerator(int squareSize)
        {
            this.squareSize = squareSize;
            this.magicSum = squareSize*(squareSize*squareSize + 1)/2;
        }

        private readonly int squareSize;
        private readonly int magicSum;
        private Dictionary<Tuple<int, int>, HashSet<int>> numbersUsedOnPosition;
        private List<int[,]> generatedSquares;
        private int[,] currentSquare;

        private void MarkPlacedNumberAsUsed(Tuple<int, int> position, int number)
        {
            if (!numbersUsedOnPosition.ContainsKey(position))
            {
                var numbersSet = new HashSet<int> { number };
                numbersUsedOnPosition.Add(position, numbersSet);
            }
            numbersUsedOnPosition[position].Add(number);
        }

        private void MarkPlacedNumberAsAvailable(Tuple<int, int> position, int number)
        {
            numbersUsedOnPosition[position].Remove(number);
        }

        private bool CanPlaceNumber(int row, int col, int number)
        {
            var position = new Tuple<int, int>(row, col);
            var canPlaceInSquare = numbersUsedOnPosition.Values.All(set => !set.Contains(number));

            if (!canPlaceInSquare)
                return false;

            var canPlaceOnPosition = !numbersUsedOnPosition.ContainsKey(position) ||
                                     !numbersUsedOnPosition[position].Contains(number);

            var canPlaceInRow =
                Enumerable
                    .Range(0, squareSize)
                    .All(gridCol => currentSquare[row, gridCol] != number);

            var canPlaceInColumn =
                Enumerable
                    .Range(0, squareSize)
                    .All(gridRow => currentSquare[gridRow, col] != number);


            var canPlaceOnMainDiagonal = true;
            var canPlaceOnAntiDiagonal = true;

            if (IsPositionOnMainDiagonal(position))
            {
                for (int i = 0; i < squareSize && canPlaceOnMainDiagonal; i++)
                {
                    for (int j = 0; j < squareSize && canPlaceOnMainDiagonal; j++)
                    {
                        if (i == j && number == currentSquare[i, j])
                            canPlaceOnMainDiagonal = false;
                    }
                }
            }

            if (IsPositionOnAntiDiagonal(position))
            {
                for (int i = 0; i < squareSize && canPlaceOnAntiDiagonal; i++)
                {
                    for (int j = 0; j < squareSize && canPlaceOnAntiDiagonal; j++)
                    {
                        if (i + j == squareSize + 1 && number == currentSquare[i, j])
                            canPlaceOnAntiDiagonal = false;
                    }
                }
            }

            return 
                canPlaceInRow           &&
                canPlaceInColumn        &&
                canPlaceOnPosition      && 
                canPlaceOnMainDiagonal  && 
                canPlaceOnAntiDiagonal;
        }

        private Tuple<bool, int, int> FindNextUnsolvedPositionIfExists()
        {
            for (var i = 0; i <= currentSquare.GetUpperBound(0); i++)
            {
                for (var j = 0; j <= currentSquare.GetUpperBound(1); j++)
                {
                    if (currentSquare[i, j] == 0)
                        return new Tuple<bool, int, int>(true, i, j);
                }
            }
            return new Tuple<bool, int, int>(false, int.MinValue, int.MinValue);
        }

        private bool IsPositionOnMainDiagonal(Tuple<int, int> position)
            => position.Item1 == position.Item2;

        private bool IsPositionOnAntiDiagonal(Tuple<int, int> position)
            => position.Item1 + position.Item2 == squareSize + 1;

        private bool EnoughNumbersPlacedInRow(int row) =>
            Enumerable
                .Range(0, squareSize)
                .Count(gridCol => currentSquare[row, gridCol] != 0) == squareSize;

        private int SumRow(int row) =>
            Enumerable
                .Range(0, squareSize)
                .Aggregate(0, (sum, squareCol) => sum + currentSquare[row, squareCol]);

        private bool EnoughNumbersPlacedInColumn(int col) =>
            Enumerable
                .Range(0, squareSize)
                .Count(gridRow => currentSquare[gridRow, col] != 0) == squareSize;

        private int SumCol(int col) =>
            Enumerable
                .Range(0, squareSize)
                .Aggregate(0, (sum, squareRow) => sum + currentSquare[squareRow, col]);

        private bool EnoughNumbersPlacedOnMainDiagonal()
        {
            var count = 0;
            for (int i = 0; i < squareSize; i++)
            {
                for (int j = 0; j < squareSize; j++)
                {
                    if (i == j && currentSquare[i, j] != 0)
                        count++;
                }
            }
            return count == squareSize;
        }

        private int SumMainDiagonal()
        {
            var sum = 0;
            for (int i = 0; i < squareSize; i++)
            {
                for (int j = 0; j < squareSize; j++)
                {
                    if (i == j)
                        sum += currentSquare[i, j];
                }
            }
            return sum;
        }

        private bool EnoughNumbersPlacedOnAntiDiagonal()
        {
            var count = 0;
            for (int i = 0; i < squareSize; i++)
            {
                for (int j = 0; j < squareSize; j++)
                {
                    if ((i + j == squareSize - 1) && currentSquare[i, j] != 0)
                        count++;
                }
            }
            return count == squareSize;
        }

        private int SumAntiDiagonal()
        {
            var sum = 0;
            for (int i = 0; i < squareSize; i++)
            {
                for (int j = 0; j < squareSize; j++)
                {
                    if (i + j == squareSize - 1)
                        sum += currentSquare[i, j];
                }
            }
            return sum;
        }

        public bool CanFillUnusedPositions()
        {
            var nextUnsolvedPosition = FindNextUnsolvedPositionIfExists();
            if (!nextUnsolvedPosition.Item1)
                return true; // solved square

            var position = new Tuple<int, int>(nextUnsolvedPosition.Item2, nextUnsolvedPosition.Item3);
            var possibleNumbers =
                Enumerable
                    .Range(1, 9)
                    .Where(number => CanPlaceNumber(position.Item1, position.Item2, number));

            foreach (var possibleNumber in possibleNumbers)
            {
                currentSquare[position.Item1, position.Item2] = possibleNumber;
                MarkPlacedNumberAsUsed(position, possibleNumber);

                var enoughNumbersPlacedInRow = EnoughNumbersPlacedInRow(position.Item1);
                var enoughNumbersPlacedInCol = EnoughNumbersPlacedInColumn(position.Item2);
                var enoughNumbersPlacedOnMainDiagonal = EnoughNumbersPlacedOnMainDiagonal();
                var enoughNumbersPlacedOnAntiDiagonal = EnoughNumbersPlacedOnAntiDiagonal();


                if (enoughNumbersPlacedOnAntiDiagonal && SumAntiDiagonal() != magicSum)
                {
                    currentSquare[position.Item1, position.Item2] = 0;
                    MarkPlacedNumberAsAvailable(position, possibleNumber);
                    continue;
                }

                if (enoughNumbersPlacedOnMainDiagonal && SumMainDiagonal() != magicSum)
                {
                    currentSquare[position.Item1, position.Item2] = 0;
                    MarkPlacedNumberAsAvailable(position, possibleNumber);
                    continue;
                }

                if (
                    !enoughNumbersPlacedInRow && 
                    !enoughNumbersPlacedInCol           && 
                    !enoughNumbersPlacedOnMainDiagonal &&
                    !enoughNumbersPlacedOnAntiDiagonal
                )
                {
                    if (CanFillUnusedPositions())
                        return true;
                }

                if (
                    enoughNumbersPlacedInRow &&
                    SumRow(position.Item1) == magicSum
                    && CanFillUnusedPositions())
                {
                    return true;
                }

                if (
                    enoughNumbersPlacedInCol &&
                    SumCol(position.Item2) == magicSum &&
                    CanFillUnusedPositions())
                {
                    return true;
                }

                currentSquare[position.Item1, position.Item2] = 0;
                MarkPlacedNumberAsAvailable(position, possibleNumber);
            }

            currentSquare[position.Item1, position.Item2] = 0; 
            return false;
        }

        public Result Generate()
        {
            numbersUsedOnPosition = new Dictionary<Tuple<int, int>, HashSet<int>>();
            generatedSquares = new List<int[,]>();
            currentSquare = new int[squareSize, squareSize];

            var canBeSolved = CanFillUnusedPositions();
            while (canBeSolved)
            {
                generatedSquares.Add(currentSquare);
                currentSquare = new int[squareSize, squareSize];
                canBeSolved = CanFillUnusedPositions();
            }

            return generatedSquares.Count > 0
                ? new Result(true, generatedSquares)
                : new Result(false, null);
        }

        public class Result
        {
            public Result(
                bool canBeGenerated,
                IEnumerable<int[,]> magicSquares )
            {
                this.CanBeGenerated = canBeGenerated;
                this.MagicSquares = magicSquares;
            }

            public bool         CanBeGenerated { get; private set; }
            public IEnumerable<int[,]> MagicSquares { get; private set; }
        }
    }
}