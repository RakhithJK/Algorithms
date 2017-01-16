using System;
using System.Collections.Generic;

namespace ShortestPath
{
    public class Solver
    {
        public Solver(char[,] map)
        {
            this.mapSizeX = map.GetUpperBound(0) + 1;
            this.mapSizeY = map.GetUpperBound(1) + 1;
            this.map      = new Dictionary<Position, Location>();

            for (int row = 0; row < mapSizeX; row++)
            {
                for (int col = 0; col < mapSizeY; col++)
                {
                    var position = new Position {
                        Row     = row,
                        Column  = col
                    }; 

                    var location = new Location
                    {
                        LocationType = GetLocationType(map[row, col])
                    };

                    if (location.LocationType == LocationType.StartOrDestinationPosition && this.start == null)
                    {
                        this.start                 = position;
                        location.DistanceFromStart = 0;
                        location.LocationColor     = Color.Grey;
                    }

                    else if (location.LocationType == LocationType.StartOrDestinationPosition && this.start != null && destination == null)
                    {
                        this.destination = position;
                    }

                    this.map.Add(position, location);
                }
            }
        }

        private readonly int                            mapSizeX;
        private readonly int                            mapSizeY;
        private readonly Position                       start;
        private readonly Position                       destination;
        private readonly Dictionary<Position, Location> map;


        private IEnumerable<Position> ReconstructPathFromDestinationToStart(Position currentPosition, List<Position> visitedPositions)
        {
            if (currentPosition.Equals(start))
            {
                visitedPositions.Reverse();
                return visitedPositions;
            }

            visitedPositions.Add(currentPosition);
            return ReconstructPathFromDestinationToStart(currentPosition.Previous, visitedPositions);
        }

        public Result Calculate()
        {
            if (start == null || destination == null)
                throw new NotSupportedException();

            var foundPath        = false;
            var positionsToVisit = new Queue<Position>();
            positionsToVisit.Enqueue(start);

            var rowOffsets = new [] { 0, 0, 1, -1 };
            var colOffsets = new [] { 1, -1, 0, 0 };

            while (positionsToVisit.Count > 0 && !foundPath)
            {
                var currentPosition = positionsToVisit.Dequeue();
                var currentLocation = map[currentPosition];

                if(currentLocation.LocationColor != Color.Grey)
                    continue;

                if (currentPosition.Equals(destination))
                {
                    map[destination].LocationColor = Color.Black;
                    this.destination.Previous = currentPosition.Previous;
                    foundPath = true;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        var maybePositionToVisit = new Position
                        {
                            Row         = currentPosition.Row       +   rowOffsets[i],
                            Column      = currentPosition.Column    +   colOffsets[i],
                            Previous    = currentPosition
                        };

                        if (
                            IsInMap(maybePositionToVisit)                               &&
                            map[maybePositionToVisit].LocationType  != LocationType.Wall &&
                            map[maybePositionToVisit].LocationColor == Color.White
                        )
                        {
                            map[maybePositionToVisit].DistanceFromStart = currentLocation.DistanceFromStart + 1;
                            map[maybePositionToVisit].LocationColor     = Color.Grey;
                            positionsToVisit.Enqueue(maybePositionToVisit);
                        }
                    }
                }

                currentLocation.LocationColor = Color.Black;
            }

            return foundPath
                ? new Result(true, ReconstructPathFromDestinationToStart(currentPosition: destination, visitedPositions: new List<Position>()))
                : new Result(false, null);
        }


        private enum Color          { White, Grey, Black }
        private enum LocationType   { Wall, Road, StartOrDestinationPosition }

        private LocationType GetLocationType(char locationChar)
        {
            switch (locationChar)
            {
                case 'X': return LocationType.Wall;
                case '0': return LocationType.StartOrDestinationPosition;
                case '.': return LocationType.Road;
                default:  throw new NotSupportedException();
            }
        }

        private bool IsInMap(Position position) =>
            position.Row        >= 0        &&
            position.Column     >= 0        &&
            position.Row        < mapSizeX  &&
            position.Column     < mapSizeY;

        public class Position : IEquatable<Position>
        {
            public int      Row         { get; set; }
            public int      Column      { get; set; }
            public Position Previous    { get; set; }

            public          bool    Equals(Position other)  => Row == other.Row && Column == other.Column;
            public override bool    Equals(object obj)      => Equals(obj as Position);
            public override int     GetHashCode()           => int.Parse($"{Row}{Column}").GetHashCode();

        }
        private class Location
        {
            public LocationType LocationType        { get; set; }
            public Color        LocationColor       { get; set; } = Color.White;
            public int          DistanceFromStart   { get; set; } = int.MinValue;
        }

        public class Result
        {
            public Result(
                bool                    canReachDestinationFromStart,
                IEnumerable<Position>   path
            )
            {
                this.CanReachDestinationFromStart = canReachDestinationFromStart;
                this.Path                         = path;
            }

            public bool                     CanReachDestinationFromStart    { get; private set; }
            public IEnumerable<Position>    Path                            { get; private set; }
        }
    }
}