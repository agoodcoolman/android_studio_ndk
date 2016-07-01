package com.jin.jni;

/**
 * Created by root on 16-5-31.
 */
public class JniLoad {
    static {
        System.loadLibrary("what");
    }
    public native static int what();

    public native static String setde(int a);
}
