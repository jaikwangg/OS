package Lab11;

class Lab11_Q2Consumer extends Thread {
    int id;
    Lab11_ApdxBlockingQueue<Element> queue;

    Lab11_Q2Consumer(int x, Lab11_ApdxBlockingQueue<Element> q) {
        id = x;
        queue = q;
    }

    public void run() {
        try {
            Element e = queue.take();
            System.out.println("Customer " + id + " takes dish " + e.val);
        } catch (InterruptedException ie) {
            System.out.println("Customer " + id + " INTERRUPTED");
        }
    }
}

class Lab11_Q2Producer extends Thread {
    int id;
    Lab11_ApdxBlockingQueue<Element> queue;
    int numCook = 0;

    Lab11_Q2Producer(int x, Lab11_ApdxBlockingQueue<Element> q) {
        id = x;
        queue = q;
    }

    public void run() {
        if (id % 2 == 0) {
            int i = -1;
            while (i < 30) { // last dish no.30
                i += 2;
                try {
                    queue.put(new Element(i));
                    numCook++;
                    System.out.println("Chef " + id + " cooks dish " + i + " size = " + queue.size());
                } catch (InterruptedException ie) {
                    System.out.println("Chef " + id + " INTERRUPTED");
                }
            }
        } else {
            int i = 0;
            while (i < 29) { // before the last dish
                i += 2;
                try {
                    queue.put(new Element(i));
                    numCook++;
                    System.out.println("Chef " + id + " cooks dish " + i + " size = " + queue.size());
                } catch (InterruptedException ie) {
                    System.out.println("Chef " + id + " INTERRUPTED");
                }
            }
        }
    }
}

public class Lab11_Q2Driver {
    public static void main(String[] args) {
        int numProducers = 2;
        int numCustomers = 15 * numProducers;

        Lab11_Q2Producer[] producers = new Lab11_Q2Producer[numProducers];
        Lab11_Q2Consumer[] customers = new Lab11_Q2Consumer[numCustomers];

        Lab11_ApdxBlockingQueue<Element> syncQueue = new Lab11_ApdxBlockingQueue<>(10);

        for (int i = 0; i < numProducers; i++) {
            producers[i] = new Lab11_Q2Producer(i, syncQueue);
            producers[i].start();
        }

        for (int j = 2; j < numCustomers + 2; j++) {
            customers[j - 2] = new Lab11_Q2Consumer(j, syncQueue);
            customers[j - 2].start();
        }

        try {
            for (int i = 0; i < numProducers; i++)
                producers[i].join();
        } catch (InterruptedException ie) {
        }

        try {
            for (int j = 2; j < numCustomers + 2; j++)
                customers[j - 2].join();
        } catch (InterruptedException ie) {
        }

        for (int i = 0; i < numProducers; i++) {
            System.out.printf("Chef %d cooks %d dishes\n", producers[i].id, producers[i].numCook);
        }

        System.out.println("Restaurant is closed.");
    }
}
