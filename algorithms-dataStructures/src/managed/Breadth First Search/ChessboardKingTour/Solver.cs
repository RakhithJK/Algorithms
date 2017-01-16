using System;
using System.Collections.Generic;
using System.Linq;

namespace ChessboardKingTour
{
    public class Solver
    {
        public Solver(
            Position startPosition, 
            Position destinationPosition,
            IReadOnlyCollection<AllowedChessboardSegment> allowedMapSegments
        )
        {
            this.startPosition = startPosition;
            this.destinationPosition = destinationPosition;
            this.allowedMapSegments = allowedMapSegments;

            startPosition.Color = Color.Grey;
            startPosition.DistanceFromStart = 0;
        }

        private readonly int mapSize = (int) Math.Pow(10, 9);
        private readonly Position startPosition;
        private readonly Position destinationPosition;
        private readonly IReadOnlyCollection<AllowedChessboardSegment> allowedMapSegments;

        private bool IsInMap(Position position) =>
            position.Row        >= 0        &&
            position.Column     >= 0        &&
            position.Row        < mapSize   &&
            position.Column     < mapSize;

        private bool IsAllowedPosition(Position position) => allowedMapSegments.Any(segment => segment.IsPositionInSegment(position));

        public Tuple<bool, int> TryFindPath()
        {
            var visitedPositions = new HashSet<Position>();
            var positionsToVisit = new Queue<Position>();

            positionsToVisit.Enqueue(startPosition);

            var rowOffsets = new [] {0, 0, 1, -1,  1, -1, 1, -1 };
            var colOffsets = new[]  {1, -1, 0, 0,  1, -1, -1, 1};
            var foundPath = false;

            while (positionsToVisit.Count > 0 && !foundPath)
            {
                var currentPosition = positionsToVisit.Dequeue();

                if (currentPosition.Color != Color.Grey)
                    continue;

                if (currentPosition.Equals(destinationPosition))
                {
                    foundPath = true;
                    this.destinationPosition.DistanceFromStart = currentPosition.DistanceFromStart;
                    this.destinationPosition.Color = Color.Black;
                }


                for (int i = 0; i < 8; i++)
                {
                    var possibleNextPosition = new Position(
                        row: currentPosition.Row + rowOffsets[i],
                        col: currentPosition.Column + colOffsets[i]
                    );

                    if (
                        IsInMap(possibleNextPosition) &&
                        !visitedPositions.Contains(possibleNextPosition) &&
                        IsAllowedPosition(possibleNextPosition)
                    )
                    {
                        possibleNextPosition.DistanceFromStart = currentPosition.DistanceFromStart + 1;
                        possibleNextPosition.Color = Color.Grey;

                        positionsToVisit.Enqueue(possibleNextPosition); 
                    }    
                }

                currentPosition.Color = Color.Black;
                visitedPositions.Add(currentPosition);
            }

            return foundPath ?
                new Tuple<bool, int>(true, this.destinationPosition.DistanceFromStart) :
                new Tuple<bool, int>(false, -1);
        }

        public class AllowedChessboardSegment
        {
            public AllowedChessboardSegment(int row, int lowerColumnBound, int upperColumnBound)
            {
                this.row = row;
                this.lowerColumnBound = lowerColumnBound;
                this.upperColumnBound = upperColumnBound;
            }

            private readonly int row;
            private readonly int lowerColumnBound;
            private readonly int upperColumnBound;

            public bool IsPositionInSegment(Position position) =>
                position.Row == row &&
                position.Column >= lowerColumnBound &&
                position.Column <= upperColumnBound;
        }

        public enum Color { White, Grey, Black }
        public class Position : IEquatable<Position>
        {
            public Position(
                int row, 
                int col
            )
            {
                this.Row = row;
                this.Column = col;
            }
            public int Row { get; private set; }
            public int Column { get; private set; }
            public Color Color { get; set; } = Color.White;
            public int DistanceFromStart { get; set; } = int.MinValue;

            public bool Equals(Position other) => Row == other.Row && Column == other.Column;
            public override bool Equals(object obj) => Equals(obj as Position);
            public override int GetHashCode() => int.Parse($"{Row}{Column}").GetHashCode();
        }
    }
}