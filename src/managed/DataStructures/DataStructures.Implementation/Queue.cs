namespace DataStructures.Implementation
{
    public class QueueElement<T>
    {
        public T               Value    { get; set; }
        public QueueElement<T> Next     { get; set; } 
    }
    public class Queue<T>
    {
        public Queue()
        {
            Head  = null;
            Tail  = null;
            Count = 0;
        }

        private void Enqueue(QueueElement<T> node)
        {
            if (Count > 0)
            {
                Tail.Next = node;
            }
            else
            {
                Head = node;
            }
            Tail = node;
            Count++;
        }

        public void Enqueue(T value)
        {
            Enqueue(new QueueElement<T> { Value = value });
        }

        public T Dequeue()
        {
            var headValue = Head.Value;
            Head          = Head.Next;
            Count --;
            return headValue;
        }

        public bool IsEmpty => Count > 0;

        private QueueElement<T> Head    { get; set; } 
        private QueueElement<T> Tail    { get; set; } 
        public  int             Count   { get; private set; }
    }
}
