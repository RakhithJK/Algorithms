using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FindWordInMatrix
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
            var letters = new [,]
            {
                { 't', 'z', 'x', 'c', 'd' },
                { 'a', 'h', 'n', 'z', 'x' }, 
                { 'h', 'w', 'o', 'i', 'o' },
                { 'o', 'r', 'n', 'r', 'n' }, 
                { 'a', 'b', 'r', 'i', 'n' }
            };

            var wordToFind = "horizon";

            var finder = new Finder(letters, wordToFind);
            var result = finder.TryFind();
            if(result.IsFound)
                Display(result.Path);
            else
                Console.WriteLine("not found");
            Console.ReadKey();
        }
    }
}
