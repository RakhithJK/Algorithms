using System.Collections.Generic;

namespace LinkedListPractice.Impl
{
    public class LinkedListNode<T>
    {
        public LinkedListNode(T value)
        {
            Value = value;
        }
        public LinkedListNode(T value, LinkedListNode<T> next) : this(value)
        {
            Next = next;
        } 
        public T                 Value { get; set; }
        public LinkedListNode<T> Next  { get; set; }
    }

    public class LinkedList<T>
    {
        public LinkedListNode<T> Head  { get; private set; }
        public LinkedListNode<T> Tail  { get; private set; }
        public int               Count { get; private set; } = 0;

        public void AddFront(LinkedListNode<T> nodeToAdd)
        {
            var headHolder = Head;
            Head = nodeToAdd;
            Head.Next = headHolder;
            Count++;

            if (Count == 1)
            {
                Tail = Head;
            }
        }
        public void AddBack(LinkedListNode<T> nodeToAdd)
        {
            if (Count == 0)
            {
                Head = nodeToAdd;
            }
            else
            {
                Tail.Next = nodeToAdd;
            }
            Tail = nodeToAdd;
            Count++;
        }

        public T PopFirst()
        {
            Head = Head.Next;
            Count --;

            if (Count == 0)
            {
                Tail = null;
            }

            return Head.Value;
        }
        public T PopLast()
        {
            T valueHolder = default(T);
            if (Count != 0)
            {
                if (Count == 1)
                {
                    valueHolder = Head.Value;
                    Head = null;
                    Tail = null;
                }
                else
                {
                    var currentNode = Head;
                    while (currentNode != null)
                    {
                        currentNode = currentNode.Next;
                    }
                    currentNode.Next = null;
                    Tail = currentNode;

                    valueHolder = Tail.Value;
                }
            }
            Count --;
            return valueHolder;
        }

        public IEnumerable<T> TraverseRecursively()
        {
            var valuesHolder = new List<T>();
            TraverseRecursively(Head, valuesHolder);
            return valuesHolder;
        } 
        public void TraverseRecursively(LinkedListNode<T> current, IList<T> valuesHolder)
        {
            if (current != null)
            {
                valuesHolder.Add(current.Value);
                TraverseRecursively(current.Next, valuesHolder);
            }
        }
        public IEnumerator<T> GetEnumerator()
        {
            var current = Head;
            while (current != null)
            {
                yield return current.Value;
                current = current.Next;
            }
        } 
    }
}
