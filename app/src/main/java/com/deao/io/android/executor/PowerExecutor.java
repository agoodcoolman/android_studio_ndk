package com.deao.io.android.executor;

import java.util.concurrent.Callable;
import java.util.concurrent.Executor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by Administrator on 2016/5/13.
 */
public class PowerExecutor implements Executor{

    private static final int CORE_POOL_SIZE = 5;
    private static final int MAXIMUM_POOL_SIZE = 56;
    private static final int KEEP_ALIVE_TIME_MIUNTES = 5;
    private final ThreadPoolExecutor mPoolExecutor;

    public PowerExecutor() {
        LinkedBlockingQueue<Runnable> blockingQueue = new LinkedBlockingQueue<Runnable>(MAXIMUM_POOL_SIZE);
        mPoolExecutor = new ThreadPoolExecutor(CORE_POOL_SIZE, MAXIMUM_POOL_SIZE, KEEP_ALIVE_TIME_MIUNTES, TimeUnit.MINUTES, blockingQueue);
    }

    @Override
    public void execute(Runnable command) {
        if (command == null) {
            throw new NullPointerException("runnable is null");
        }

        mPoolExecutor.execute(command);

    }


    public void submit(Callable callable) {
        if (callable == null) {
            throw new NullPointerException("callable is null");
        }
        mPoolExecutor.submit(callable);
    }


}
