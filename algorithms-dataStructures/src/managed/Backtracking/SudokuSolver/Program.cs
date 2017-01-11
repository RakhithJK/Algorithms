using System;

namespace SudokuSolver
{
    class Program
    {
        static void Display(int[,] path)
        {
            for (int i = 0; i <= path.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= path.GetUpperBound(1); j++)
                {
                    if (path[i, j] / 10 == 0)
                        Console.Write(' ');

                    Console.Write(path[i, j]);
                    Console.Write(' ');
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            var gridToSolve = new [,]
            {
                { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                { 8, 0, 0, 0, 6, 0, 0, 0, 3 }, 
                { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                { 7, 0, 0, 0, 2, 0, 0, 0, 6 }, 
                { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
            };
               
            Console.WriteLine("grid to solve :");
            Display(gridToSolve);
            Console.WriteLine();

            var result = new Solver(gridToSolve).TrySolve();

            if (result.CanBeSolved)
            {
                Console.WriteLine("solved grid :");
                Display(result.SolvedGrid);
            }
            else
                Console.WriteLine("cant be solved");

            Console.ReadKey();
        }
    }
}

