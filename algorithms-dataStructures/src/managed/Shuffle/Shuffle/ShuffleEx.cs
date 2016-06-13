using System;
using System.Collections.Generic;
namespace Shuffle
{
    public static class ShuffleEx
    {
        public static void Shuffle<T>(this IList<T> enumerable, ShuffleType shuffleType)
        {
            if (shuffleType == ShuffleType.Random)
            {
                PerformRandomShuffle(enumerable);
            }
            else
            {
                PerformSpecialShuffle(enumerable);
            }
        }
        private static void PerformRandomShuffle<T>(this IList<T> enumerable)
        {
            if (enumerable.Count == 1)
            {
                return;
            }
            if (enumerable.Count == 2)
            {
                var temp = enumerable[0];
                enumerable[0] = enumerable[1];
                enumerable[1] = temp;
                return;
            }

            for (int i = 0; i < enumerable.Count; i++)
            {
                var randomSwapIndex = random.Next(0, enumerable.Count - 1);
                var temp = enumerable[i];
                enumerable[i] = enumerable[randomSwapIndex];
                enumerable[randomSwapIndex] = temp;
            }
        }
        private static void PerformSpecialShuffle<T>(this IList<T> enumerable)
        {
            if (enumerable.Count == 1)
            {
                return;
            }
            if (enumerable.Count == 2)
            {
                var temp = enumerable[0];
                enumerable[0] = enumerable[1];
                enumerable[1] = temp;
                return;
            }

            var positionsDictionary = new Dictionary<T, SortedSet<int>>();
            for (var i = 0; i < enumerable.Count; i++)
            {
                var elementPositions = new SortedSet<int> { i };
                positionsDictionary.Add(enumerable[i], elementPositions);
            }

            for (var i = 0; i < enumerable.Count; i++)
            {
                var element = enumerable[i];
                var randomSwapIndex = random.Next(0, enumerable.Count - 1);
                while (randomSwapIndex != i &&
                    !PositionsContainValue(positionsDictionary[element], randomSwapIndex) &&
                    !PositionsContainValue(positionsDictionary[enumerable[randomSwapIndex]], randomSwapIndex))
                {
                    randomSwapIndex = random.Next(0, enumerable.Count - 1);
                }

                var temp = enumerable[i];
                enumerable[i] = enumerable[randomSwapIndex];
                enumerable[randomSwapIndex] = temp;
                positionsDictionary[element].Add(randomSwapIndex);
            }
        }

        private static          bool    PositionsContainValue(SortedSet<int> set, int value) => set.Contains(value);
        private static readonly Random  random = new Random();
    }

    public enum ShuffleType
    {
        Random,
        AllElementsShouldBeOnDifferentPositions
    }
}
