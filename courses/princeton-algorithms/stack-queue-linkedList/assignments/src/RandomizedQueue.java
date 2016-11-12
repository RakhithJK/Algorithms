/**
 * Created by Gabrijel Boduljak on 11/11/2016.
 */

import edu.princeton.cs.algs4.StdRandom;
import java.util.*;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private class RandomizedQueueIterator<Item> implements Iterator<Item> {
        public boolean hasNext() {
            return size() > 0;
        }

        public Item next() {
            ensureQueueHasElements();
            return (Item) dequeue();
        }
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public RandomizedQueue() {
        linkedList = new ArrayList<Item>();
    }

    private List<Item> linkedList;

    public boolean isEmpty() {
        return linkedList.isEmpty();
    }

    public int size() {
        return linkedList.size();
    }

    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator<Item>();
    }

    public void enqueue(Item item) {
        if (item == null) {
            throw new java.lang.NullPointerException();
        }
        linkedList.add(item);
    }

    public Item dequeue() {
        ensureQueueHasElements();
        return linkedList.remove(getRandomIndex());
    }

    public Item sample() {
        ensureQueueHasElements();
        return linkedList.get(getRandomIndex());
    }

    private int getRandomIndex()
    {
        return StdRandom.uniform(size());
    }

    private void ensureQueueHasElements()
    {
        if (isEmpty())
            throw new java.util.NoSuchElementException();
    }
}