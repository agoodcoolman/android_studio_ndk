//
// Created by root on 16-5-31.
//

#include <com_jin_jni_JniLoad.h>

JNIEXPORT jint JNICALL Java_com_jin_jni_JniLoad_what
        (JNIEnv *env, jclass jclass){
    int a = 1,b = 2;
    jint c = 3;
    return c;
};