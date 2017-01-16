using System;
using System.Linq;

namespace ChessboardKingTour
{
    class Program
    {
        static void Main(string[] args)
        {
            var startPosition = new Solver.Position(
                row: 5,
                col: 7
            );
            var destinationPosition = new Solver.Position(
                row: 6,
                col: 11
            );
            var allowedPositions = new[]
            {
                new Solver.AllowedChessboardSegment(5, 3, 8),
                new Solver.AllowedChessboardSegment(6, 7, 11),
                new Solver.AllowedChessboardSegment(5, 2, 5)
            };
       
            var startPosition2 = new Solver.Position(
                row: 3,
                col: 4
            );
            var destinationPosition2 = new Solver.Position(
                row: 3,
                col: 10
            );
            var allowedPositions2 = new[]
            {
                new Solver.AllowedChessboardSegment(3, 1, 4),
                new Solver.AllowedChessboardSegment(4, 5, 9),
                new Solver.AllowedChessboardSegment(3, 10, 10)
            };

            var startPosition3 = new Solver.Position(
                row: 1,
                col: 1
            );
            var destinationPosition3 = new Solver.Position(
                row: 2,
                col: 10
            );
            var allowedPositions3 = new[]
            {
                new Solver.AllowedChessboardSegment(1, 1, 3),
                new Solver.AllowedChessboardSegment(2, 6, 10)
            };

            var solution = new Solver(startPosition, destinationPosition, allowedPositions.ToList().AsReadOnly()).TryFindPath(); // true, 4    
            var solution2 = new Solver(startPosition2, destinationPosition2, allowedPositions2.ToList().AsReadOnly()).TryFindPath(); // true, 6    
            var solution3 = new Solver(startPosition3, destinationPosition3, allowedPositions3.ToList().AsReadOnly()).TryFindPath(); // false, -1

            Console.WriteLine($"{solution.Item1},{solution.Item2}");
            Console.WriteLine($"{solution2.Item1},{solution2.Item2}");
            Console.WriteLine($"{solution3.Item1},{solution3.Item2}");
            Console.ReadKey();
        }
    }
}