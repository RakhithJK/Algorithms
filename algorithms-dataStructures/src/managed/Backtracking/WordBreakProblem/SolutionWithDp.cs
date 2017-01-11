using System.Collections.Generic;
using System.Text;

namespace WordBreakProblem
{
    public class SolutionWithDp
    {
        public SolutionWithDp(
            string          stringToBreak,
            HashSet<string> dictionary
        )
        {
            this.stringToBreak  = stringToBreak;
            this.dictionary     = dictionary;
        }

        private readonly    HashSet<string>             dictionary;
        private readonly    string                      stringToBreak;
        private             Dictionary<string, bool>    lookup;
        private             string                      brokenString;

        public              string                      StringToBeBroken => stringToBreak;

        private void AddOrUpdateToLookup(string substring, bool value)
        {
            if (!lookup.ContainsKey(substring))
            {
                lookup.Add(substring, value);
                return;
            }

            lookup[substring] = value;
        }

        private bool CanBreakIntoSubstrings(string subString)
        {
            if (string.IsNullOrEmpty(subString))
                return true;

            if (lookup.ContainsKey(subString))
                return lookup[subString];

            var subStringChars   = subString.ToCharArray();
            var breakIndex       = 0;
            var subStringBuilder = new StringBuilder();

            for (breakIndex = 0; breakIndex < subStringChars.Length; breakIndex++)
            {
                subStringBuilder.Append(subStringChars[breakIndex]);

                if (dictionary.Contains(subStringBuilder.ToString()))
                {
                    brokenString += subStringBuilder + " ";

                    var rest = subString.Substring(breakIndex + 1);
                    if (CanBreakIntoSubstrings(rest))
                    {
                        AddOrUpdateToLookup(subString, true);
                        return true;
                    }

                    AddOrUpdateToLookup(subString, false);
                    brokenString = brokenString.Remove(breakIndex + 1);
                }
            }

            return false;
        }

        public Result TryBreak()
        {
            brokenString = string.Empty;
            lookup       = new Dictionary<string, bool>();

            var canBeBroken = CanBreakIntoSubstrings(stringToBreak);

            return canBeBroken ?
                new Result(true, brokenString) : 
                new Result(false, null) ;
        }

        public class Result
        {
            public Result(
                bool    canBeBroken,
                string  brokenString
            )
            {
                this.CanBeBroken    =   canBeBroken;
                this.BrokenString   =   brokenString;
            }
            public bool     CanBeBroken     { get; private set; }
            public string   BrokenString    { get; private set; }
        }
    }
}
