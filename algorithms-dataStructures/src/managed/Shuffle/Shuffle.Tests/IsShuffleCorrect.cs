using System.Diagnostics;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Shuffle.Tests
{
    [TestClass]
    public class IsShuffleCorrect
    {
        [TestMethod]
        public void TestForSomeLists()
        {
            Enumerable.Range(2, NumberOfLists)
                .ToList()
                .ForEach(numberOfListElements =>
                {
                    var list = Enumerable.Range(1, numberOfListElements).ToList();
                    var beforeListArray = list.ToArray();     
                    list.Shuffle(shuffleType: ShuffleType.AllElementsShouldBeOnDifferentPositions);
                    Debug.WriteLine(list.SequenceEqual(beforeListArray));
                    Assert.AreNotEqual(beforeListArray, list);          
                });
        }

        [TestMethod]
        public void ShuffleHugeList()
        {
            var list = Enumerable.Range(1, 500000).ToList(); // a half million elements 
            var beforeListArray = list.ToArray();
            list.Shuffle(shuffleType: ShuffleType.AllElementsShouldBeOnDifferentPositions);
            Debug.WriteLine(list.SequenceEqual(beforeListArray));
            Assert.AreNotEqual(beforeListArray, list);
        }

        public const int NumberOfLists = 500;
    }
}