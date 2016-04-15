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
    }
}