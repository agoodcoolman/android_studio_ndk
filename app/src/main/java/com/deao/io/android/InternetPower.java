package com.deao.io.android;

import com.deao.io.android.anntion.GetParame;

import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.concurrent.Executor;

/**
 * Created by Administrator on 2016/5/13.
 * 初始化的类
 */
public  class InternetPower {
    private String BaseUri = null;
    private Executor executor;
    private  InternetPower() {
    }

    public static void initialization() {

    }



    public <T> T getUri(Class<T> clazz) {
        return (T)Proxy.newProxyInstance(clazz.getClassLoader(), new Class<?>[]{clazz}, new InvocationHandler() {

            @Override
            public Object invoke(Object o, Method method, Object[] args) throws Throwable {
                Annotation[] annotations = method.getAnnotations();
                String uri = BaseUri;
                for (Annotation a: annotations ) {
                    uri += a;
                }
                uri += "?";
                Annotation[][] parameterAnnotations = method.getParameterAnnotations();

                for (int i = 0; i < parameterAnnotations.length; i++) {
                    for (int j = 0; j < parameterAnnotations[i].length; j++) {
                        GetParame annotation = (GetParame)parameterAnnotations[i][j];

                        uri += args[i] + " = " + annotation.parame();
                    }
                }
                System.out.println(uri);
                return method.invoke(o, args);
            }
        });
    }



    public static class Builder {

        private final InternetPower internetPower;

        public Builder() {
            internetPower = new InternetPower();
        }

        public Builder setBaseUri(String baseUri) {
            internetPower.BaseUri = baseUri;
            return this;
        }


        public InternetPower build() {
            if (internetPower.BaseUri == null)
                throw new NullPointerException("baseuri not initialization...");


            return internetPower ;
        }
    }

}
