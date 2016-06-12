package com.deao.io.android;

/**
 * Created by root on 16-5-14.
 */
public interface PowerHttpListener<T, E> {

    public void onSuccess(T sucess);

    public void onFailed(E failed);
}
