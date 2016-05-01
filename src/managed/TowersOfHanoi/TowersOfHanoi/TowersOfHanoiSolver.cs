using System;
using System.Text;

namespace TowersOfHanoi
{
    public static class TowersOfHanoiSolver
    {

        private static int NumberOfMoves { get; set; } = 0;
        public static Tuple<int, string> Solve(int numberOfDiscs, char sourcePeg, char destinationPeg, char operationsPeg = 'o')
        {
            NumberOfMoves = 0;
            StringBuilder instructions = new StringBuilder();
            SolveRecursively(numberOfDiscs - 1, sourcePeg, destinationPeg, operationsPeg, instructions);
            return new Tuple<int, string>(NumberOfMoves, instructions.ToString());
        }
            
        public static void SolveRecursively(int numberOfDiscs, char sourcePeg, char destinationPeg, char operationsPeg, StringBuilder instructions)
        {
            if (numberOfDiscs == 0)
            {
                instructions.Append($"Moving single disc from {sourcePeg} to {destinationPeg}");
                NumberOfMoves++;
            }
            else
            {
                instructions.Append($"Moving {numberOfDiscs - 1} discs from {sourcePeg} to {operationsPeg} \n");
                SolveRecursively(numberOfDiscs - 1, sourcePeg, operationsPeg, destinationPeg, instructions);

                instructions.Append($"Moving {numberOfDiscs} disc from {sourcePeg} to {operationsPeg} \n");
                NumberOfMoves++;

                instructions.Append($"Moving {numberOfDiscs - 1} discs from {operationsPeg} to {destinationPeg} \n");
                SolveRecursively(numberOfDiscs - 1, operationsPeg, destinationPeg, sourcePeg, instructions);
            }
        }
    }
}
