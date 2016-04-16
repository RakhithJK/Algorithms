using System.Collections.Generic;

namespace MathExpression.Implementation.Ex
{
    public static class StackEx
    {
        public static bool IsEmpty<T> (this Stack<T> stack) => stack.Count == 0;
        public static bool IsEmpty<T>(this DataStructures.Implementation.Stack<T> stack) => stack.Count == 0;
    }
}
