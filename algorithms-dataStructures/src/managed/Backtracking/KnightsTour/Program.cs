using System;
using System.Diagnostics;

namespace KnightsTour
{
    class Program
    {
        static void Display(int[,] path)
        {
            for (int i = 0; i <= path.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= path.GetUpperBound(1); j++)
                {
                    if(path[i, j] / 10 == 0)
                        Console.Write("0");

                    Console.Write(path[i, j]);
                    Console.Write(" ");
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("enter chessboard length");
            var chessboardLength = int.Parse(Console.ReadLine());

            var stopwatch = new Stopwatch();
            stopwatch.Start();

            var solverResult = new Solver().Solve(chessboardLength);
            if (solverResult.CanBeSolved)
                Display(solverResult.Path);
            else
                Console.WriteLine("cannot be solved!");

            stopwatch.Stop();
            Console.WriteLine($"solution took {stopwatch.Elapsed}.");
            Console.ReadKey();
        }
    }
}