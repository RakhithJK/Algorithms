using System;
using System.Collections.Generic;
using System.Linq;

namespace FindWordInMatrix
{
    public class Finder
    {
        public Finder(char[,] letters, string word)
        {
            this.letters    = letters;
            this.wordToFind = word;
        }

        public class Result
        {
            public Result(bool isFound, int[,] path)
            {
                IsFound = isFound;
                Path        = path;
            }

            public bool   IsFound     { get; private set; }
            public int[,] Path        { get; private set; }
        }

        private readonly char[,] letters;
        private readonly string  wordToFind;

        private int[,] solutionMatrix;
        private int    wordLength;

        private bool IsInMatrix(int row, int col) 
            => row >= 0 && col >= 0 && row <= letters.GetUpperBound(0) && col <= letters.GetUpperBound(1);

        public bool FindRestRecursively(int currentRow, int currentColumn)
        {            
            if (wordLength >= wordToFind.Length)
                return true;
            if (wordToFind[wordLength] != letters[currentRow, currentColumn])
                return false;

            wordLength++;
            solutionMatrix[currentRow, currentColumn] = wordLength;

            var rowOffsets    = new[] { 0, 0,  1, -1, 1, 1, -1, -1 };
            var columnOffsets = new[] {1, -1, 0, 0, 1, -1, 1, -1};

            for (int i = 0; i < 8; i++)
            {
                var direction = new Tuple<int, int>(currentRow + rowOffsets[i], currentColumn + columnOffsets[i]);
                if (

                    IsInMatrix(direction.Item1, direction.Item2)          && // in matrix
                    solutionMatrix[direction.Item1, direction.Item2] == 0 && // not visited
                    FindRestRecursively(direction.Item1, direction.Item2)    // letters after found
                )
                {
                    return true;
                }
            }

            wordLength--;
            solutionMatrix[currentRow, currentColumn] = 0;
            return false;
        }

        public Result TryFind()
        {
            wordLength     = 0;
            solutionMatrix = new int[letters.GetUpperBound(0) + 1, letters.GetUpperBound(1) + 1];
            for (int i = 0; i < letters.GetUpperBound(0); i++)
            {
                for (int j = 0; j < letters.GetUpperBound(1); j++)
                {
                    if (letters[i, j] == wordToFind[0])
                    {
                        var isFound = FindRestRecursively(i, j);
                        if (isFound)
                            return new Result(true, solutionMatrix);
                    }
                }
            }
            return new Result(false, null);
        }
    }               
}