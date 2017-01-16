using System;

namespace ShortestPath
{
    class Program
    {
        static void Display(char[,] cityMap)
        {
            for (int i = 0; i <= cityMap.GetUpperBound(0); i++)
            {
                for (int j = 0; j <= cityMap.GetUpperBound(1); j++)
                {
                    if (cityMap[i, j] / 10 == 0)
                        Console.Write(' ');

                    Console.Write(cityMap[i, j]);
                    Console.Write(' ');
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            var testMap = new[,]
           {
                { 'X', 'X', 'X', 'X', 'X', 'X' },
                { 'X', '0', '.', 'X', '.', 'X' },
                { 'X', 'X', '.', '.', '.', 'X' },
                { 'X', 'X', 'X', '.', '.', 'X' },
                { 'X', 'X', 'X', 'X', '.', 'X' },
                { 'X', 'X', '.', '.', '.', 'X' },
                { 'X', 'X', 'X', '0', 'X', 'X' }
            };

            Display(testMap);
            Console.WriteLine();

            var solution = new Solver(testMap).Calculate();

            if (solution.CanReachDestinationFromStart)
            {
                foreach (var position in solution.Path)
                {
                    Console.WriteLine($"Visit ({position.Row}, {position.Column})");
                }
            }
            else
                Console.WriteLine("Cannot reach destination! :(");

            Console.ReadKey();
        }
    }
}
