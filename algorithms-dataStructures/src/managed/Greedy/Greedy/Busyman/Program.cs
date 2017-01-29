using System;
using System.Collections.Generic;

namespace Busyman
{
    public class Activity 
    {
        public int      StartingTime     { get; set; }
        public int      FinishingTime    { get; set; }
    }

    public class SortByFinishingThenStartingTime: IComparer<Activity>
    {
        public int Compare(Activity lhs, Activity rhs)
        {
            var comparisonResult = lhs.FinishingTime.CompareTo(rhs.FinishingTime);
            if (comparisonResult == 0)
            {
                comparisonResult = lhs.StartingTime.CompareTo(rhs.StartingTime);
            }
            return comparisonResult;        
        }
    }

    public class Program
    {
        private static int CalculateMaximumNumberOfActivities(SortedSet<Activity> activities)
        {
            var numberOfActivities = 1;
            var previousActivity   = activities.Min;
            foreach (var activity in activities)
            {
                if (activity.StartingTime >= previousActivity.FinishingTime)
                {
                    numberOfActivities++;
                    previousActivity = activity;
                }
            }
            return numberOfActivities;
        }

        private static void Main(string[] args)
        {
            var testResults   = new List<int>();
            var numberOfTests = int.Parse(Console.ReadLine());

            for (int test = 0; test < numberOfTests; test++)
            {
                var numberOfActivities = int.Parse(Console.ReadLine());
                var testActivities     = new SortedSet<Activity>(new SortByFinishingThenStartingTime());

                for (int i = 0; i < numberOfActivities; i++)
                {
                    var activityParts = Console.ReadLine().Split(' ');
                    testActivities.Add(new Activity
                    {
                        StartingTime  = int.Parse(activityParts[0]),
                        FinishingTime = int.Parse(activityParts[1])
                    });
                }
                testResults.Add(CalculateMaximumNumberOfActivities(testActivities));
            }

            foreach (var testResult in testResults)
            {
                Console.WriteLine(testResult);
            }

            Console.ReadKey();
        }
    }
}
