using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TowersOfHanoi.Tests
{
    [TestClass]
    public class TowersOfHanoiTests
    {
        [TestMethod]
        public void TestAlgorithm()
        {
            foreach (var pair in _predefinedDictionary)
            {
                _solutionsDictionary.Add(pair.Key, TowersOfHanoiSolver.Solve(pair.Key, 's', 'd'));
            }
            foreach (var pair in _solutionsDictionary)
            {
                Assert.AreEqual(_predefinedDictionary[pair.Key], _solutionsDictionary[pair.Key].Item1);
            }
        }

        private readonly Dictionary<int, Tuple<int, string>> _solutionsDictionary  = new Dictionary<int, Tuple<int,string>>(); 
        private readonly Dictionary<int, int> _predefinedDictionary = new Dictionary<int, int>()
        {
            { 1, 1  },
            { 3, 7  },
            { 4, 15 },
            { 5, 31 },
            { 6, 63 }
        };
    }
}
