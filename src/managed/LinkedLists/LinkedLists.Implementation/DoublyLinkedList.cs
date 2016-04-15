using System.Collections.Generic;

namespace LinkedLists.Implementation
{
    public class DoublyLinkedListNode<T>
    {
        public DoublyLinkedListNode(T value)
        {
            Value = value;
        }
        public DoublyLinkedListNode(T value, 
            DoublyLinkedListNode<T> previous,
            DoublyLinkedListNode<T> next
        ) : this(value)
        {
            Previous = previous;
            Next     = next;
        }
        public T Value { get; set; }
        public DoublyLinkedListNode<T> Next     { get; set; }
        public DoublyLinkedListNode<T> Previous { get; set; }
    }

    public class DoublyLinkedList<T>
    {
        private DoublyLinkedListNode<T> Head   { get; set; }  
        private DoublyLinkedListNode<T> Tail   { get; set; }
        public  int                     Count  { get; private set; }     

        public void AddFirst(DoublyLinkedListNode<T> nodeToAdd)
        {
            if (Head == null)
            {
                Head = nodeToAdd;
                Count++;
            }
            else
            {
                var headHolder     = Head;
                Head               = nodeToAdd;
                Head.Next          = headHolder;
                Head.Next.Previous = Head;
                Count++;
            }
            if (Count == 1)
            {
                Head = Tail;
            }
        }
        public void AddLast(DoublyLinkedListNode<T> nodeToAdd)
        {
            if (Count == 0)
            {
                AddFirst(nodeToAdd);
            }
            else
            {
                var previousTail  = Tail;
                Tail.Next         = nodeToAdd;
                Tail              = nodeToAdd;
                Tail.Previous     = previousTail;
                Count++;
            }
        }

        public T PopFirst()
        {
            if (Count > 0)
            {
                Head = Head.Next;
                Head.Previous = null;
                Count--;
                if (Count == 0)
                {
                    Tail = null;
                }
                else
                {
                    Head.Previous = null;
                }
                return Head.Value;
            }
            return default(T);
        }
        public T PopLast()
        {
            if (Count > 0)
            {
                if (Count == 1)
                {
                    Head = null;
                    Tail = null;
                }
                else
                {
                    Tail.Previous.Next = null;
                    Tail = Tail.Previous;
                }
                Count--;
                return Tail != null ? Tail.Value : default(T);
            }
            return default(T);
        }

        public T Remove(DoublyLinkedListNode<T> currentNode, T valueToRemove)
        {
            if (currentNode == null)
            {
                return default(T);
            }
            if (currentNode.Value.Equals(valueToRemove))
            {
                var previousNode = currentNode.Previous;
                var nextNode     = currentNode.Next;

                previousNode.Next = nextNode;
                Count--;
                return currentNode.Value;
            }
            return Remove(currentNode.Next, valueToRemove);
        }

        public IReadOnlyCollection<T> Traverse()
        {
            var valuesHolder = new List<T>();
            TraverseRecursively(Head, valuesHolder);
            return valuesHolder.AsReadOnly();
        }
        private void TraverseRecursively(DoublyLinkedListNode<T> currentNode, IList<T> valuesHolder)
        {
            if(currentNode != null)
            {
                valuesHolder.Add(currentNode.Value);
                TraverseRecursively(currentNode.Next, valuesHolder);
            }
        }
        public void Clear()
        {
            Head = null;
            Tail = null;
        }
    }
}