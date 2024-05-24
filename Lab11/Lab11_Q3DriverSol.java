package Lab11;

import java.util.Random;

public class Lab11_Q3DriverSol {
    public static void main(String[] args) {
        int numPopper = 1;
        int numPusher = 1;
        int numTurns = 10;
        StackForConcurrent stack = new StackForConcurrent();
        Pusher[] pushArr = new Pusher[numPusher];
        Popper[] poppArr = new Popper[numPopper];
        for (int i = 0; i < numPusher; i++) {
            pushArr[i] = new Pusher(numTurns, stack);
            poppArr[i] = new Popper(numTurns, stack);
            pushArr[i].start();
            poppArr[i].start();
        }
        for (int i = 0; i < numPusher; i++) {
            try {
                pushArr[i].join();
                poppArr[i].join();
            } catch (InterruptedException ie) {
            }
        }
    }

}

class StackForConcurrent {
    Node top;
    int size;

    StackForConcurrent() {
        top = null;
        size = 0;
    }

    synchronized void push(int n) {
        top = new Node(n, top);
        size++;
        if (top.next == null) {
            notifyAll(); 
        }
    }

    synchronized int pop() {
        try {
            while (top == null) {
                System.out.println("Empty stack");
                wait();
            }
            size--;
            int n = top.val;
            top = top.next;
            return n;   
        } catch (InterruptedException ie) {
            System.out.println("Error");
            return 1;
        }
        
    }
}

class Pusher extends Thread {
    int turns;
    StackForConcurrent concurStack;

    Pusher(int t, StackForConcurrent s) {
        turns = t;
        concurStack = s;
    }

    public void run() {
        Random rand = new Random();
        try {
            sleep(rand.nextInt(100));
        } catch (InterruptedException ie) {
        }
        for (int i = 0; i < turns; i++)
            concurStack.push(i);
    }
}

class Popper extends Thread {
    int turns;
    StackForConcurrent concurStack;

    Popper(int t, StackForConcurrent s) {
        turns = t;
        concurStack = s;
    }

    public void run() {
        int x = -1;
        for (int j = 0; j < turns; j++) {
            x = concurStack.pop();
            System.out.println("Got " + x + " from the stack, stack size = " + concurStack.size);
        }
    }
}

class Node {
    int val;
    Node next;

    Node(int v) {
        val = v;
    }

    Node(int v, Node n) {
        val = v;
        this.next = n;
    }

    int getVal() {
        return val;
    }
}
