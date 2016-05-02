using System;
using System.Text;

namespace TowersOfHanoi
{
    public static class TowersOfHanoiSolver
    {      
        public static Tuple<int, string> Solve(int numberOfDiscs, char sourcePeg, char destinationPeg, char operationsPeg = 'O')
        {
            NumberOfMoves = 0;
            StringBuilder instructions = new StringBuilder();
            SolveRecursively(numberOfDiscs - 1, sourcePeg, destinationPeg, operationsPeg, instructions);
            return new Tuple<int, string>(NumberOfMoves, instructions.ToString());
        }

        private static int  NumberOfMoves { get; set; } = 0;
        private static void SolveRecursively(int numberOfDiscs, char sourcePeg, char destinationPeg, char operationsPeg, StringBuilder instructions)
        {
            if (numberOfDiscs == 0)
            {
                instructions.Append($"Moving last disc from {sourcePeg} peg to {destinationPeg} peg.");
                NumberOfMoves++;
            }
            else
            {
                instructions.Append($"Moving {numberOfDiscs - 1}. disc from {sourcePeg} peg to {operationsPeg} peg. \n");
                SolveRecursively(numberOfDiscs - 1, sourcePeg, operationsPeg, destinationPeg, instructions);

                instructions.Append($"Moving {numberOfDiscs}. disc from {sourcePeg} peg to {operationsPeg} peg, \n");
                NumberOfMoves++;

                instructions.Append($"Moving {numberOfDiscs - 1}. disc from {operationsPeg} peg to {destinationPeg} peg. \n");
                SolveRecursively(numberOfDiscs - 1, operationsPeg, destinationPeg, sourcePeg, instructions);
            }
        }
    }
}
