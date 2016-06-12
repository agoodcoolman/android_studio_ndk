package com.deao.io.android.executor;

/**
 * Created by Administrator on 2016/5/13.
 */
public class ThreadPoolManager {
    private static ThreadPoolManager ourInstance = new ThreadPoolManager();
    private final PowerExecutor powerExecutor;

    public static ThreadPoolManager getInstance() {
        return ourInstance;
    }

    private ThreadPoolManager() {
        powerExecutor = new PowerExecutor();
    }



}
