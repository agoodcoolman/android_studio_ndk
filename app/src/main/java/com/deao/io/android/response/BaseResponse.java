package com.deao.io.android.response;

import java.util.Objects;

/**
 * Created by root on 16-5-14.
 */
public abstract class BaseResponse<T> {



    public T getResult(T result) {

        return preparse(result);
    };

    public abstract <T>T preparse(T result);

}
