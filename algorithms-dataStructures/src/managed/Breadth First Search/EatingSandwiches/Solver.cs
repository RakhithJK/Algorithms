using System;
using System.Collections.Generic;
using System.Linq;

namespace EatingSandwiches
{
    public class Solver
    {

        public Solver(char[,] map)
        {
            this.map      = new Dictionary<Position, Location>();
            this.mapSizeX = map.GetUpperBound(0);
            this.mapSizeY = map.GetUpperBound(1);

            for (int row = 0; row <= mapSizeX; row++)
            {
                for (int col = 0; col <= mapSizeY; col++)
                {
                    var position = new Position { Row = row, Column = col };
                    var location = new Location { LocationType = GetLocationType(map[row, col]) };

                    if (location.LocationType == LocationType.Person)
                    {
                        personStartingPosition = position;
                        location.DistanceFromPerson = 0;
                        location.LocationColor = Color.Grey;
                    }
             
                    this.map.Add(position, location);
                }
            }

        }

        private readonly int                            mapSizeX;
        private readonly int                            mapSizeY;
        private readonly Position                       personStartingPosition;
        private readonly Dictionary<Position, Location> map;

        public Result Calculate()
        {
            var positionsToVisit = new Queue<Position>();
            var sandwiches       = new List<Position>();
            var stepsCount       = 0;
            var rowOffset        = new[] { 1, -1, 0, 0 };
            var colOffset        = new[] { 0, 0, 1, -1 };

            positionsToVisit.Enqueue(personStartingPosition);

            while (positionsToVisit.Count > 0)
            {
                var currentPosition = positionsToVisit.Dequeue();
                var currentLocation = map[currentPosition];

                if (currentLocation.LocationColor == Color.Grey)
                {
                    if(currentLocation.LocationType == LocationType.Sandwich)
                        sandwiches.Add(currentPosition);

                    for (int i = 0; i < 4; i++)
                    {
                        var possibleNextPosition = new Position
                        {
                            Row    = currentPosition.Row + rowOffset[i],
                            Column = currentPosition.Column + colOffset[i]
                        };

                        if (
                            !IsInMap(possibleNextPosition)                              || 
                            map[possibleNextPosition].LocationType == LocationType.Wall || // cannot move to wall
                            map[possibleNextPosition].LocationColor != Color.White         // not discovered yet
                        ) continue;

                        map[possibleNextPosition].DistanceFromPerson = currentLocation.DistanceFromPerson + 1;
                        map[possibleNextPosition].LocationColor      = Color.Grey;

                        positionsToVisit.Enqueue(possibleNextPosition);
                    }
                    stepsCount++;
                }

                currentLocation.LocationColor = Color.Black;
            }


            if(sandwiches.Count == 0)
                return new Result(false, stepsCount, sandwiches, null, int.MaxValue);

            var mostDistantSandwich         = sandwiches.Last();
            var mostDistantSandwichDistance = map[mostDistantSandwich].DistanceFromPerson;

            return new Result(true, stepsCount, sandwiches, mostDistantSandwich, mostDistantSandwichDistance);
        }

        private enum Color        { White, Grey, Black }
        private enum LocationType { Wall, Road, Person, Sandwich }

        private LocationType GetLocationType(char locationChar)
        {
            switch (locationChar)
            {
                case 'X' : return LocationType.Wall;
                case '-': return LocationType.Person;
                case '0': return LocationType.Sandwich;
                case '.': return LocationType.Road;
                default: throw new NotSupportedException();
            }
        }

        private bool IsInMap(Position position) =>
            position.Row    >= 0        && 
            position.Column >= 0        && 
            position.Row    <= mapSizeX && 
            position.Column <= mapSizeY;

        public class Position : IEquatable<Position>
        {
            public int      Row         { get; set; }
            public int      Column      { get; set; }

            public bool Equals(Position other) => Row == other.Row && Column == other.Column;

            public override     int     GetHashCode()       => int.Parse($"{Row}{Column}");
            public override     bool    Equals(object obj)  => Equals(obj as Position);
        }

        private class Location
        {
            public LocationType LocationType { get; set; }
            public Color LocationColor { get; set; } = Color.White;
            public int DistanceFromPerson { get; set; } = int.MinValue;
        }

        public class Result
        {
            public Result (
                bool                    canEatAnySandwich,
                int                     stepsCount,
                IEnumerable<Position>   sandwichPositions,
                Position                mostDistantSandwichPosition,
                int                     mostDistantSandwichDistance
            )
            {
                this.StepsCount                  = stepsCount;
                this.CanEatAnySandwich           = canEatAnySandwich;
                this.SandwichPositions           = sandwichPositions;
                this.MostDistantSandwichPosition = mostDistantSandwichPosition;
                this.MostDistantSandwichDistance = mostDistantSandwichDistance;
            }

            public int                      StepsCount                      { get; private set; }
            public bool                     CanEatAnySandwich               { get; private set; }
            public IEnumerable<Position>    SandwichPositions               { get; private set; }
            public Position                 MostDistantSandwichPosition     { get; private set; }
            public int                      MostDistantSandwichDistance     { get; private set; }
        }
    }
}
