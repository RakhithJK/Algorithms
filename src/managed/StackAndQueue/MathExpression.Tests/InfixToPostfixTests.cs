using System.Collections.Generic;
using System.Linq;
using MathExpression.Implementation;
using MathExpression.Implementation.Ex;
using MathExpression.Tests.Ex;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MathExpression.Tests
{
    [TestClass]
    public class InfixToPostfixTests
    {
        [TestMethod]
        public void ConversionFromInfixToPostfix()
        {
            ExpressionCalculator expressionCalculator = new ExpressionCalculator();
            Dictionary<int, string> calculatedExpressionsHolder = new Dictionary<int, string>();

            var calculatedExpressions = _infixExpressions
                .Select(pair => expressionCalculator.PrepareExpression(pair.Value))
                .Select(expressionCalculator.CalculatePostfixExpression)
                .Select(expressionAsCharArray => new string(expressionAsCharArray));

            int index = 0;
            foreach (var calculatedExpression in calculatedExpressions)
            {
                calculatedExpressionsHolder.Add(index, calculatedExpression);
                index++;
            }

            foreach (var pair in calculatedExpressionsHolder)
            {
                var expectedTrimmed     = _postfixExpressions[pair.Key].RemoveWhitespaces();
                var calculatedTrimmed   = calculatedExpressionsHolder[pair.Key].RemoveWhitespaces();
                Assert.IsTrue(expectedTrimmed.SequenceEqual(calculatedTrimmed));
            }
        }

        private readonly Dictionary<int, string> _infixExpressions = new Dictionary<int, string>()
        {
            { 0, "( 1 + 0 ) * ( 0 + 1 )" },
            { 1, "( 1 + 1 ) * 0"         },
            { 2, "1 + 0 * 1"             }
        };
        private readonly Dictionary<int, string> _postfixExpressions = new Dictionary<int, string>()
        {
            { 0, "1 0 + 0 1 + *" },
            { 1, "1 1 + 0 *"     },
            { 2, "1 0 1 * +"     }
        };
    }
}
