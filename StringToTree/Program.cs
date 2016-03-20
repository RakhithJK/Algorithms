using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringToTree
{
    class Program
    {
        public static void RenderTree(Node tree)
        {
            Console.WriteLine($"VALUE --- {tree.Value}");
            if (tree.HasParent)
            {
                Console.WriteLine($"PARENT --- {tree.Parent}");
            }
            foreach (var child in tree.Children)
            {
                RenderTree(child);
            }
        }

        public static Node Parse(string input)
        {
            Node current = new Node();

            for (int i = 0; i < input.Length - 1; i++)
            {
                char currentChar = input[i];
                if (currentChar == '{')
                {
                    Node node = new Node
                    {
                        Value = input[i + 1],
                        Parent = current
                    };
                    current.Children.Add(node);
                    current = node;
                }
                if (currentChar == '}')
                {
                    current = current.Parent;
                }
            }

            return current;
        }

        internal class Node
        {
            public Node()
            {
                Children = new Collection<Node>();
            }

            public char Value { get; set; } = ' ';
            public Node Parent { get; set; }
            public ICollection<Node> Children { get; set; }

            public bool HasParent => Parent != null;

            public override string ToString()
            {
                return Value.ToString();
            }
        }

        static void Main(string[] args)
        {
            const string input = "{A{B{C}{D}{E}}{F{G}{H}}}";
            RenderTree(Parse(input));
            Console.ReadKey();
        }

   
    }
}
