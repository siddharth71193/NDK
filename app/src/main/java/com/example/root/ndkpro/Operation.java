package com.example.root.ndkpro;

/**
 * Created by siddharth on 23/12/2018.
 */

public class Operation {

    static {
        System.loadLibrary("native-lib");
    }
    public static native int[] factorial(int n);
    public static native int[] power(int n,int x);
    public static native long fibonacci(long n);


}
