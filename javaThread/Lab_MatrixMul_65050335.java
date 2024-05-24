
import java.util.Arrays;

public class Lab_MatrixMul_65050335 {
    public static void main(String[] args) {
        int[][] inputA = { { 5, 6, 7 }, { 4, 8, 9 } };
        int[][] inputB = { { 6, 4 }, { 5, 7 }, { 1, 1 } };
        MyData matA = new MyData(inputA);
        MyData matB = new MyData(inputB);
        int matC_r = matA.data.length;
        int matC_c = matB.data[0].length;
        MyData matC = new MyData(matC_r, matC_c);
        /*
         * Q4 construct 2D array for each "thread"
         * with respected to each cell in matC,
         * then start each thread
         */

        for (int i = 0; i < matC_r; i++) {
            for (int j = 0; j < matC_c; j++) {
                Thread t = new Thread(new MatrixMulThread(i, j, matA, matB, matC));
                t.start();
                try {// Q5 join each thread
                    t.join();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }
        }
        matC.show();
    }
}

class MatrixMulThread implements Runnable {
    int processing_row;
    int processing_col;
    MyData datA;
    MyData datB;
    MyData datC;

    MatrixMulThread(int tRow, int tCol,
            MyData a, MyData b, MyData c) {
        // Q1 code here
        this.processing_row = tRow;
        this.processing_col = tCol;
        this.datA = a;
        this.datB = b;
        this.datC = c;
    }

    /* Q2 */ public void run() {
        // Q3
        int sum = 0;
        for (int i = 0; i < datA.data[0].length; i++) {
            sum += datA.data[processing_row][i] * datB.data[i][processing_col];
        }
        datC.data[processing_row][processing_col] = sum;
        System.out.println("perform sum of multiplication of assigned row:" + processing_row + " and col:"
                + processing_col + " = " + sum);
    }
}

// class
class MyData {
    int[][] data;

    MyData(int[][] m) {
        data = m;
    }

    MyData(int r, int c) {
        data = new int[r][c];
        for (int[] aRow : data)
            Arrays.fill(aRow, 9);
        // 9 will be overwritten anyway
    }

    void show() {
        System.out.println(Arrays.deepToString(data));
    }
} // class
/*
 * if uncomment line 19 the output will be
 * From worker1 thread 13 x value is 3
 * From worker2 thread 14 x value is 7
 * from main x value is 7
 */