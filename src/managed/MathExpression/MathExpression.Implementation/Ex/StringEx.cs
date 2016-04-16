using System.Linq;

namespace MathExpression.Implementation.Ex
{
    public static class StringEx
    {
        public static string RemoveWhitespaces(this string source) => new string(source.Where(character => character != ' ').ToArray());
    }
}
