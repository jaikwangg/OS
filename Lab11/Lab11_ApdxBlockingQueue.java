package Lab11;

import java.util.concurrent.locks.*;

class Lab11_ApdxBlockingQueue<E> {
    private final Object[] items;
    private final Lock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();
    private int putPointer;
    private int takePointer;
    private int curSize;

    public Lab11_ApdxBlockingQueue(int capacity) {
        items = new Object[capacity];
    }

    public void put(E value) throws InterruptedException {
        lock.lock();
        try {
            while (curSize == items.length) {
                System.out.println("Full, waiting");
                notFull.await();
                System.out.println("Stop waiting");
            }
            items[putPointer++] = value;
            if (putPointer == items.length) {
                putPointer = 0;
            }
            curSize++;
            notEmpty.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public E take() throws InterruptedException {
        lock.lock();
        try {
            while (curSize == 0) {
                System.out.println("Empty, waiting");
                notEmpty.await();
                System.out.println("Stop waiting");
            }
            @SuppressWarnings("unchecked")
            E result = (E) items[takePointer++];
            if (takePointer == items.length) {
                takePointer = 0;
            }
            curSize--;
            notFull.signalAll();
            return result;
        } finally {
            lock.unlock();
        }
    }

    int size() {
        return curSize;
    }
}

class Element {
    int val;

    Element(int n) {
        val = n;
    }

    int getVal() {
        return val;
    }
}
