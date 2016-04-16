using System;
using System.Collections.Generic;

namespace MathExpression.Tests.Ex
{
    public static class EnumerableEx
    {
        public static void ForEach<T>(this IEnumerable<T> collection, Action<T> action)
        {
            foreach (var item in collection)
            {
                action(item);
            }
        }
    }
}