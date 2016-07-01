//
// Created by 研发 on 2016/6/30.
//
#include "com_jin_jni_JniLoad.h"
jint JNICALL Java_com_jin_jni_JniLoad_what
(JNIEnv *env, jclass jclazz){
    jint a = 1;

    a += 10;
    return a;

};

