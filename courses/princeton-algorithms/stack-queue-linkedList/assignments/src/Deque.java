/**
 * Created by Gabrijel Boduljak on 11/11/2016.
 */

import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {

    private class DequeNode<Item>
    {
        public DequeNode(Item value) {
            this.Value = value;
        }

        public Item            Value;
        public DequeNode<Item> Next;
        public DequeNode<Item> Previous;
    }

    private class DequeIterator<Item> implements Iterator<Item>
    {
        private DequeNode<Item> current = (DequeNode<Item>) head;

        public boolean hasNext() {
            return current !=  null;
        }

        public Item next() {
            if(!hasNext())
                throw new NoSuchElementException();

            Item value = current.Value;
            current    = current.Next;
            return value;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public Deque()
    {
        head = null;
        tail = head;
        size = 0;
    }

    private DequeNode<Item> head;
    private DequeNode<Item> tail;
    private int             size;

    public boolean isEmpty()
    {
        return size == 0;
    }

    public int size()
    {
        return size;
    }

    public Iterator<Item> iterator() {
        return new DequeIterator<Item>();
    }

    public void addFirst(Item value)
    {
        ensureValueNotNull(value);

        if(size == 0)
        {
            this.head = new DequeNode<Item>(value);
            this.tail = this.head;
        }
        else
        {
            DequeNode<Item> previousHead = this.head;
            DequeNode<Item> newHead      = new DequeNode<Item>(value);
            newHead.Next                 = previousHead;
            newHead.Previous             = null;

            this.head             = newHead;
            previousHead.Previous = newHead;
        }

        size++;
    }

    public void addLast(Item value)
    {
        ensureValueNotNull(value);

        if(size == 0)
            addFirst(value);

        else
        {
            DequeNode<Item> previousTail = this.tail;
            DequeNode<Item> newTail      = new DequeNode<Item>(value);
            newTail.Previous             = previousTail;
            newTail.Next                 = null;

            this.tail         = newTail;
            previousTail.Next = newTail;
            size++;
        }

    }

    public Item removeFirst() {
        ensureDequeNotEmpty();

        DequeNode<Item> previousHead = this.head;
        this.head = this.head.Next;

        size--;

        if (size > 0)
            this.head.Previous       = null;

        if(size == 0)
            this.tail = this.head;

        return previousHead.Value;
    }

    public Item removeLast()
    {
        ensureDequeNotEmpty();

        DequeNode<Item> previousTail = this.tail;
        this.tail                    = this.tail.Previous;
        size--;

        if(size > 0)
            this.tail.Next           = null;

        if(size == 0)
            this.head = this.tail;

        return previousTail.Value;
    }

    private void ensureValueNotNull(Item value)
    {
        if(value == null)
            throw new NullPointerException();
    }

    private void ensureDequeNotEmpty()
    {
        if(size == 0)
            throw new NoSuchElementException();
    }

    public static void main(String[] args)
    {
        Deque<Integer> deq = new Deque<Integer>();
        deq.addLast(0);
        deq.addLast(1);
        deq.addLast(2);
        deq.removeLast();
        deq.removeLast();
        deq.removeLast();
        for (Integer d : deq)
            StdOut.println(d);
    }
}