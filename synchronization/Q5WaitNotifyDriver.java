package synchronization;

public class Q5WaitNotifyDriver {
    public static void main(String[] args) {
        SharedNum5 sn = new SharedNum5();

        // Unnamed thread receiver
        (new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("got " + sn.getVal());
            }
        })).start();

        try {
            Thread.sleep(2); 
        } catch (InterruptedException ie) {
        }

        // Unnamed thread sender
        (new Thread(new Runnable() {
            @Override
            public void run() {
                sn.setVal(2021);
            }
        })).start();

        // Since there's no reference, we don't need to care about join
        System.out.println("from main");
    }
}

class SharedNum5 {
    private int val = 0;
    Object lock;

    SharedNum5() {
        val = 0;
        lock = this;
    }

    synchronized int getVal() {
        try {
            lock.wait();
        } catch (InterruptedException ie) {
        }
        return val;
    }

    synchronized void setVal(int x) {
        val = x;
        lock.notifyAll();
    }
}

