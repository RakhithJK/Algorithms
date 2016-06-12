using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace DataStructures.Implementation.Lists
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
        public T Value { get; set; }
        public LinkedListNode<T> Next { get; set; }
    }

    public class LinkedList<T> : ICollection<T>
    {
        public LinkedListNode<T> Head { get; private set; }
        public LinkedListNode<T> Tail { get; private set; }
    
        public int Count              { get; private set; } = 0;
        public bool IsReadOnly        { get; } = false;

        public void AddFront(LinkedListNode<T> nodeToAdd)
        {
            var headHolder = Head;
            Head           = nodeToAdd;
            Head.Next      = headHolder;
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
            Count--;

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
            Count--;
            return valueHolder;
        }

        public  LinkedListNode<T> Find(T value)
        {
            return Find(Head, value);
        }
        private LinkedListNode<T> Find(LinkedListNode<T> currentNode, T value)
        {
            if (currentNode != null && !currentNode.Value.Equals(value))
            {
                return Find(currentNode.Next, value);
            }
            return currentNode;
        }

        public void Add(T item) => AddBack(new LinkedListNode<T>(item));

        public void Clear()
        {
            Head = null;
            Tail = null;
        }

        public bool Contains(T item) => Find(item) != null;
        public void CopyTo(T[] array, int arrayIndex)
        {
            array[arrayIndex] = TraverseRecursively().ToArray()[arrayIndex];
        }

        bool ICollection<T>.Remove(T item) => Remove(item) != null;

        public T RemoveFirst()
        {
            T valueHolder = default(T);
            Head          = Head.Next;
            Count--;
            if (Count == 0)
            {
                Tail = null;
            }
            return valueHolder;
        }
        public T Remove(T value)
        {
            LinkedListNode<T> previous = null;
            LinkedListNode<T> current = Head;
            var valueHolder = default(T);

            while (current != null)
            {
                if (previous != null && current.Value.Equals(value))
                {
                    valueHolder   = current.Value;
                    previous.Next = current.Next;
                    if (current.Next == null)
                    {
                        Tail = previous;
                    }
                    Count--;
                }
                else
                {
                    RemoveFirst();
                }
               
                previous = current;
                current  = current.Next;
            }

            return valueHolder;
        }
        public T RemoveRecursively(T value)
        {
            return RemoveRecursively(null, Head, value);
        }
        public T RemoveRecursively(LinkedListNode<T> previousNode, LinkedListNode<T> currentNode, T value)
        {
            var valueHolder = default(T);
            if (currentNode != null)
            {
                if (previousNode != null && currentNode.Value.Equals(value))
                {
                    valueHolder       = currentNode.Value;
                    previousNode.Next = currentNode.Next;

                    if (currentNode.Next == null)
                    {
                        Tail = previousNode;
                    }

                    Count--;
                }
                else
                {
                    RemoveFirst();
                }
                return RemoveRecursively(currentNode, currentNode.Next, value);
            }
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
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }
}
