using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NxMMatrixArrange2
{
    class Program
    {
        static readonly Random random = new Random();

        // Fisher-Yates shuffle
        static void Shuffle<T>(T[] array)
        {
            int n = array.Length;
            for (int i = 0; i < n; i++)
            {
                int r = i + (int)(random.NextDouble() * (n - i));
                T t = array[r];
                array[r] = array[i];
                array[i] = t;
            }
        }

        static IEnumerable<int[,]> GenerateMatrixes(int n, int m)
        {
            var numbersInOrder = Enumerable.Range(1, n * m).ToArray();

            for (int i = 0; i < 5; i++)
            {
                Shuffle(numbersInOrder);
                var matrix = new int[n, m];

                int currentRow = 0;
                int currentChunkSize = 0;
                int numbersPlaced = 0;

                while (numbersPlaced < n * m)
                {
                    if (currentChunkSize == m)
                    {
                        currentChunkSize = 0;
                        currentRow++;
                    }
                    for (int col = 0; col < m; col++)
                    {
                        matrix[currentRow, col] = numbersInOrder[numbersPlaced];
                        currentChunkSize++;
                        numbersPlaced++;
                    }

                }

                yield return matrix;
            }
        }
        static void DisplayMatrix(int[,] matrix)
        {
            for (int i = 0; i <= matrix.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= matrix.GetUpperBound(1); j++)
                {
                    if (matrix[i, j] / 10 == 0)
                        Console.Write(' ');

                    Console.Write(matrix[i, j]);
                    Console.Write(' ');
                }
                Console.WriteLine();
            }
        }

        static void DisplayTurns(IEnumerable<Tuple<int, int>> turns)
        {
            Console.WriteLine("Steps to arrange:");

            var step = 1;
            foreach (var tuple in turns)
            {
                Console.WriteLine($"\t Step {step}: Swap number {tuple.Item1} with {tuple.Item2}.");
                step++;
            }

            Console.WriteLine("Arranged!");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Enter first matrix dimension :");
            int n = int.Parse(Console.ReadLine());
            Console.WriteLine("Enter second matrix dimension :");
            int m = int.Parse(Console.ReadLine());

            var matrixes = GenerateMatrixes(n, m);

            Console.WriteLine("Arranging 5 random generated matrixes of given dimens!");

            foreach (var matrix in matrixes)
            {
                Console.WriteLine("Matrix to arrange : ");
                DisplayMatrix(matrix);
                Console.WriteLine("Arranging...");
                var result = new Solver(matrix).TryArrange();

                if (result.CanBeArranged)
                    DisplayTurns(result.Steps);
                else
                    Console.WriteLine("Generated matrix cannot be arranged!");
                Console.WriteLine("\n");
            }

            Console.WriteLine("Arranging matrix that can be arranged!");

            var arrangleableMatrix = new int[,]
            {
                {1, 2, 3},
                {9, 6, 8},
                {4, 7, 5 }
            };
            DisplayMatrix(arrangleableMatrix);
            var resultOfArrangement = new Solver(arrangleableMatrix).TryArrange();
            DisplayTurns(resultOfArrangement.Steps);

            Console.ReadKey();
        }
    }
}
