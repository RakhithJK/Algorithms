using System;

namespace MagicSquares
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
            var generator = new MagicSquareGenerator(3);
            var result = generator.Generate();

            if (result.CanBeGenerated)
            {
                foreach (var square in result.MagicSquares)
                {
                    Display(square);
                    Console.WriteLine();
                }
            }
            else
            {
                Console.WriteLine("cannot generate any magic square :(");
            }
            Console.ReadKey();
        }
    }
}