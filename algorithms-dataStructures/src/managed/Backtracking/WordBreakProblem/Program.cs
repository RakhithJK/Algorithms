using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace WordBreakProblem
{
    class Program
    {
        static void SolveAndDisplay(SolutionWithoutDp solution)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            Console.WriteLine($@"Trying to break '{solution.StringToBeBroken}' using solver without DP.");
            var result = solution.TryBreak();
            stopwatch.Stop();

            Console.WriteLine(result.CanBeBroken ? $"Broken as : {result.BrokenString}" : "string cannot be broken!");
            Console.WriteLine($"Elapsed {stopwatch.Elapsed}");
            Console.WriteLine();
        }

        static void SolveAndDisplay(SolutionWithDp solution)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            Console.WriteLine($@"Trying to break '{solution.StringToBeBroken}'. using solver with DP.");
            var result = solution.TryBreak();
            stopwatch.Stop();

            Console.WriteLine(result.CanBeBroken ? $"Broken as : {result.BrokenString}" : "string cannot be broken!");
            Console.WriteLine($"Elapsed {stopwatch.Elapsed}");
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            var dictionary = new HashSet<string> {
                "this", "is", "gabrijel", "boduljak", "the", "problem", "mobile","samsung","sam","sung","man","mango",
                "icecream","and","go","I","like","ice","cream" };

            var stringToBreak1 = "thisisgabrijelboduljak";
            var stringToBreak2 = "Ilikesamsung";
            var stringToBreak3 = "Ilikegabrijelboduljak";

            var solversWithoutDp = new[]
            {
                new SolutionWithoutDp(stringToBreak1, dictionary),
                new SolutionWithoutDp(stringToBreak2, dictionary),
                new SolutionWithoutDp(stringToBreak3, dictionary)
            };

            var solversWithDp = new[]
            {
                new SolutionWithDp(stringToBreak1, dictionary), 
                new SolutionWithDp(stringToBreak2, dictionary),
                new SolutionWithDp(stringToBreak3, dictionary)
            };

            for (int i = 0; i < 3; i++)
            {
                SolveAndDisplay(solversWithoutDp[i]);
                SolveAndDisplay(solversWithDp[i]);
            }

            Console.ReadKey();
        }
    }
}
