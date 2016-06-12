package com.deao.io.android.response;

import java.util.Objects;

/**
 * Created by root on 16-5-14.
 */
public class SimpleResponse extends BaseResponse {


    @Override
    public Object preparse(Object result) {
        return result;
    }
}
