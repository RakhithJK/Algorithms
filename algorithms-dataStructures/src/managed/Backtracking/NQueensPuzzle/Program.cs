using System;

namespace NQueensPuzzle
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
            for (int i = 0; i <= 20; i++)
            {
                Console.WriteLine("------------------------------");
                Console.WriteLine($"Solving puzzle for {i} queens on {i} * {i} chessboard...");
                var result = new Solver(i).TrySolve();
                if(!result.CanBeSolved)
                    Console.WriteLine($"Puzzle cannot be solved for {i} queens on {i} * {i} chessboard!");
                else
                {
                    Display(result.Chessboard);
                }

                Console.WriteLine("------------------------------ \n");
            }
            Console.ReadKey();
        }
    }
}
