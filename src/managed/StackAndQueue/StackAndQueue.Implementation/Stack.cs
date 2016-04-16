namespace StackAndQueue.Implementation
{
    public class StackElement<T>
    {
        public T                 Value  { get; set; }
        public StackElement<T>   Next   { get; set; }
    }
    public class Stack<T>
    {
        public StackElement<T>   Head   { get; set; }
        public int               Count  { get; set; } = 0;

        public void Push(T value)
        {
            Push(new StackElement<T> { Value = value });
        }
           
        public void Push (StackElement<T> element)
        {
            if (Head == null)
            {
                Head = element;
                Count++;
            }
            else
            {
                var nextElement = Head;
                Head = element;
                Head.Next = nextElement;
                Count++;
            }
        }
        public T Pop()
        {
            var nodeToReturn = Head;
            Head = Head.Next;
            Count--;
            return nodeToReturn.Value;
        }
        public T Peek()
        {
            return (Count > 0) ? Head.Value : default(T);
        }

        public bool IsEmpty => Count > 0;
        public void Clear() => Head = null;
    }
}