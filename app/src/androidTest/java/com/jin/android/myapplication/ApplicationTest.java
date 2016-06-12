package com.jin.android.myapplication;

import android.app.Application;
import android.test.ApplicationTestCase;

import com.deao.io.android.InternetPower;

import test.LoginUri;

/**
 * <a href="http://d.android.com/tools/testing/testing_android.html">Testing Fundamentals</a>
 */
public class ApplicationTest extends ApplicationTestCase<Application> {
    public ApplicationTest() {
        super(Application.class);
    }


    public void test(){
        InternetPower internetPower = new InternetPower.Builder().setBaseUri("www.baidu.com").build();
        LoginUri uri = internetPower.getUri(LoginUri.class);
        uri.login("jin", "123456");
    }
}