package synchronization;

public class Q1InnerAndNotSyncDriver {
    public static void main(String[] args) {
        int nThread = 100000;
        SharedNum1 sn = new SharedNum1();
        Thread[] thr = new Thread[nThread];
        for (int i = 0; i < nThread; i++) {
            thr[i] = new Thread(new Runnable() {
                @Override
                public void run() {
                    sn.increment();
                }
            });
            thr[i].start();
        }
        for (int i = 0; i < nThread; i++) {
            try {
                thr[i].join();
            } catch (InterruptedException ie) {
            }
        }
        if (sn.getVal() < nThread) {
            System.out.printf("v1 val = %d Not 100,000\n", sn.getVal());
        } else {
            System.out.printf("v1 good job! %d\n", sn.getVal());
        }
    }
}

class SharedNum1 {
    private int val = 0;

    void increment() {
        val++;
    }

    int getVal() {
        return val;
    }
}

