namespace LinkedListPractice.Impl
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
        public DoublyLinkedListNode<T> Next { get; set; }
        public DoublyLinkedListNode<T> Previous { get; set; }
    }

    public class DoublyLinkedList<T>
    {
        private DoublyLinkedListNode<T> Head { get; set; }  
        private DoublyLinkedListNode<T> Tail { get; set; }
        public  int                     Count { get; private set; }     

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
        public void Clear()
        {
            Head = null;
            Tail = null;
        }
    }
}
