using System;
using System.Collections.Generic;
using System.Linq;

namespace NxMMatrixArrange2
{
 public class Solver
    {
        public Solver(int[,] matrixToArrange)
        {
            this.matrixToArrange = matrixToArrange;
            this.arrangedMatrix  = new int[matrixToArrange.GetUpperBound(0) + 1, matrixToArrange.GetUpperBound(1) + 1];

            var increment = 1;

            for (int i = 0; i <= matrixToArrange.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= matrixToArrange.GetUpperBound(1); j++)
                {
                    this.arrangedMatrix[i, j] = increment;
                    increment++;
                }
            }
        }

        private readonly int[,] matrixToArrange;
        private readonly int[,] arrangedMatrix;

        private List<Tuple<int, int>>   steps;
        private List<int[,]>            visitedStates;

        private void Swap(Tuple<int, int> lhs, Tuple<int, int> rhs)
        {
            var temp = matrixToArrange[lhs.Item1, lhs.Item2];
            matrixToArrange[lhs.Item1, lhs.Item2] = matrixToArrange[rhs.Item1, rhs.Item2];
            matrixToArrange[rhs.Item1, rhs.Item2] = temp;

        }

        private void StoreCurrentState()
        {
            var state = new int[matrixToArrange.GetUpperBound(0) + 1, matrixToArrange.GetUpperBound(1) + 1];
            Array.Copy(matrixToArrange, state, (matrixToArrange.GetUpperBound(0) + 1) * (matrixToArrange.GetUpperBound(1) + 1));
            visitedStates.Add(state);
        }

        private bool DeepEqualsToCurrentMatrixArrangement(int[,] state)
        {
            for (int i = 0; i <= matrixToArrange.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= matrixToArrange.GetUpperBound(1); j++)
                {
                    if (matrixToArrange[i, j] != state[i, j])
                        return false;
                }
            }
            return true;
        }

        private bool VisitedCurrentState() => visitedStates.Any(DeepEqualsToCurrentMatrixArrangement);

        private bool IsCorrect(Tuple<int, int> position)
            => matrixToArrange[position.Item1, position.Item2] == arrangedMatrix[position.Item1, position.Item2];


        private Tuple<bool, IEnumerable<Tuple<int, int>>> FindNextIncorrectValuePositions()
        {
            var incorrectPositions = new List<Tuple<int, int>>();
            for (int i = 0; i <= matrixToArrange.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= matrixToArrange.GetUpperBound(1); j++)
                {
                    if(matrixToArrange[i, j] != arrangedMatrix[i, j])
                        incorrectPositions.Add(new Tuple<int, int>(i, j));
                }
            }
            return incorrectPositions.Count > 0
                ? new Tuple<bool, IEnumerable<Tuple<int, int>>>(true, incorrectPositions)
                : new Tuple<bool, IEnumerable<Tuple<int, int>>>(false, null);
        }

        private bool IsInMatrix(int row, int col)
            => row >= 0 && col >= 0 && row <= matrixToArrange.GetUpperBound(0) && col <= matrixToArrange.GetUpperBound(1);

        private bool CanArrangeRest(int currentDepth, int maxDepth)
        {     
            var findNextIncorrectResult = FindNextIncorrectValuePositions();
            if (!findNextIncorrectResult.Item1) 
                return true;

            if (currentDepth > maxDepth)
                return false;

            var incorrectPosition = findNextIncorrectResult.Item2.First();

            var rowOffsets = new int[] { 0, 1, 1 };
            var colOffsets = new int[] { 1, 1, 0 };

            var possibleSwapPositions = new List<Tuple<int, int>>();
            for (int i = 0; i < 3; i++)
            {
                var rowToSwap = incorrectPosition.Item1 + rowOffsets[i];
                var colToSwap = incorrectPosition.Item2 + colOffsets[i];
                var possibleSwapPosition = new Tuple<int, int>(rowToSwap, colToSwap);

                if (IsInMatrix(rowToSwap, colToSwap) && !IsCorrect(possibleSwapPosition))
                {
                    possibleSwapPositions.Add(possibleSwapPosition);
                }
            }

            foreach (var possibleSwapPosition in possibleSwapPositions)
            {
                var numbersToSwap = new Tuple<int, int>(
                    matrixToArrange[incorrectPosition.Item1, incorrectPosition.Item2],
                    matrixToArrange[possibleSwapPosition.Item1, possibleSwapPosition.Item2]
                );

                steps.Add(numbersToSwap);
                Swap(incorrectPosition, possibleSwapPosition);
            }

            if (VisitedCurrentState())
                return false;

            StoreCurrentState();

            return CanArrangeRest(currentDepth + 1, maxDepth);
        }

        public Result TryArrange()
        {
            var canBeArranged   = false;
            var maxSearchDepth  = ((matrixToArrange.GetUpperBound(0) + 1)*(matrixToArrange.GetUpperBound(1) + 1));
 
            for (int maxDepth = 1; maxDepth <= maxSearchDepth && !canBeArranged; maxDepth++)
            {
                steps           = new List<Tuple<int, int>>();
                visitedStates   = new List<int[,]>();
                canBeArranged   = CanArrangeRest(0, maxDepth);
            }
            
            return canBeArranged
                ? new Result(true, visitedStates, steps, visitedStates.Count)
                : new Result(false, null, null, null);
        }


        public class Result
        {
            public Result(
                bool                            canBeArranged,
                IEnumerable<int[,]>             visitedStates,
                IEnumerable<Tuple<int, int>>    steps,
                int ?                           arrangedAtDepth
            )
            {
                this.CanBeArranged   = canBeArranged;
                this.VisitedStates   = visitedStates;
                this.Steps           = steps;
                this.ArrangedAtDepth = arrangedAtDepth;
            }

            public bool                         CanBeArranged   { get; private set; }
            public IEnumerable<int[,]>          VisitedStates   { get; private set; }
            public IEnumerable<Tuple<int, int>> Steps           { get; private set; }
            public int?                         ArrangedAtDepth { get; private set; }
        }
    }
}
