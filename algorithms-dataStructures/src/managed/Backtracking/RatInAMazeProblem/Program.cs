using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RatInAMazeProblem
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
                        Console.Write("0");

                    Console.Write(path[i, j]);
                    Console.Write(" ");
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            var maze = new[,]
            {
                {true, false, true, true, true},
                {true, true, true, false, true},
                {false, false, false, true, true},
                {false, false, false, true, false},
                {false, false, false, true, true}
            };
            var startPosition       = new Tuple<int, int>(0,0);
            var destinationPosition = new Tuple<int, int>(maze.GetUpperBound(0), maze.GetUpperBound(1));
            var result              = new Finder(maze, startPosition, destinationPosition).TryFind();

            if (result.IsFound)
                Display(result.Path);
            else
                Console.WriteLine("not found");
            Console.ReadKey();
        }
    }
}
