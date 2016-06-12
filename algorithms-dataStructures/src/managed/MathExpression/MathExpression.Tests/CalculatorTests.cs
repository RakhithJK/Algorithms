using MathExpression.Implementation;
using System.Collections.Generic;
using System.Linq;

using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MathExpression.Tests
{
    [TestClass]
    public class CalculatorTests
    {
        [TestMethod]
        public void CalculationTests()
        {
            ExpressionCalculator expressionCalculator    = new ExpressionCalculator();
            Dictionary<int, int> calculatedResultsHolder = new Dictionary<int, int>();

            var calculatedResults = _expressions
                .Select(pair => pair.Value)
                .Select(expressionCalculator.Calculate);

            int index = 0;
            foreach (var result in calculatedResults)
            {
                calculatedResultsHolder.Add(index, result);
                index++;
            }

            foreach (var pair in calculatedResultsHolder)
            {
                var expectedResult = _expressionResults[pair.Key];
                var calculatedResult = pair.Value;
                Assert.AreEqual(expectedResult, calculatedResult);
            }
        }

        private readonly Dictionary<int, string> _expressions = new Dictionary<int, string>()
        {
            { 0, "( 1 + 0 ) * ( 0 + 1 )" },
            { 1, " 5 - 4 + 2"            },
            { 2, " 7 + 9 + / (4 * 2)"    }
        };
        private readonly Dictionary<int, int> _expressionResults = new Dictionary<int, int>()
        {
            { 0, 1  },
            { 1, 3  },
            { 2, 2  }
        };
    }
}
