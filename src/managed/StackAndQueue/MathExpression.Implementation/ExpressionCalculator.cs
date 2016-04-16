using System.Collections.Generic;
using MathExpression.Implementation.Ex;

namespace MathExpression.Implementation
{
    using customStack = StackAndQueue.Implementation;
    public class ExpressionCalculator
    {
        public ExpressionCalculator()
        {
            _operatorsStack    = new customStack::Stack<char>();
            _expressionBuilder = new List<char>();
        }

        private bool IsOperator(char maybeOperator)
        {
            return maybeOperator == Operators.Plus       ||
                   maybeOperator == Operators.Minus      ||
                   maybeOperator == Operators.Multiplier ||
                   maybeOperator == Operators.Divider    ||
                   maybeOperator == Operators.Power;
        }

        private bool IsRightParenthesis(char maybeRightParenthesis) => maybeRightParenthesis == Parenthesis.Right;
        private bool IsLeftParenthesis(char maybeLeftParenthesis) => maybeLeftParenthesis == Parenthesis.Left;

        private bool IsNumber(char maybeNumber)
        {
            int number;
            return int.TryParse(maybeNumber.ToString(), out number);
        }

        public char[] PrepareExpression(string expressionAsString) => expressionAsString.RemoveWhitespaces().ToCharArray();

        public char[] CalculatePostfixExpression(char[] expressionAsArray)
        {
            _operatorsStack.Clear();
            _expressionBuilder.Clear();
           
            foreach (var character in expressionAsArray)
            {
                if (IsNumber(character))
                {
                    _expressionBuilder.Add(character);
                }

                else if (IsLeftParenthesis(character))
                {
                    _operatorsStack.Push(character);
                }

                else if (IsRightParenthesis(character))
                {
                    if (!_operatorsStack.IsEmpty())
                    {
                        var operatorAsCharacter = _operatorsStack.Pop();
                        while (!_operatorsStack.IsEmpty() && operatorAsCharacter != Parenthesis.Left)
                        {
                            _expressionBuilder.Add(operatorAsCharacter);
                            if (!_operatorsStack.IsEmpty())
                            {
                                operatorAsCharacter = _operatorsStack.Pop();
                            }
                        }
                    } 
                }

                else if (IsOperator(character))
                {
                    if (!_operatorsStack.IsEmpty())
                    {
                        while (!_operatorsStack.IsEmpty() && _precedence[_operatorsStack.Peek()] >= _precedence[character])
                        {
                            _expressionBuilder.Add(_operatorsStack.Pop());
                        }
                    }
                    _operatorsStack.Push(character);
                }
            }
            while (!_operatorsStack.IsEmpty())
            {
                _expressionBuilder.Add(_operatorsStack.Pop());
            }

            return _expressionBuilder.ToArray();
        }

        private readonly customStack::Stack<char> _operatorsStack;
        private readonly List<char>               _expressionBuilder;
        private readonly Dictionary<char, int>    _precedence = new Dictionary<char, int>()
        {
            { Operators.Multiplier, 3 },
            { Operators.Divider,    3 },
            { Operators.Power,      3 },
            { Operators.Plus,       2 },
            { Operators.Minus,      2 },
            { Parenthesis.Left,     1 }
        }; 

        public static class Operators
        {
            public const char Plus       = '+';
            public const char Minus      = '-';
            public const char Multiplier = '*';
            public const char Divider    = '/';
            public const char Power      = '^';
        }

        public static class Parenthesis
        {
            public const char Left      = '(';
            public const char Right     = ')';
        }
    }
}