/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jin_jni_JniLoad */

#ifndef _Included_com_jin_jni_JniLoad
#define _Included_com_jin_jni_JniLoad




extern "C" {
#endif
/*
 * Class:     com_jin_jni_JniLoad
 * Method:    what
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_jin_jni_JniLoad_what
        (JNIEnv *, jclass);
JNIEXPORT jstring JNICALL Java_com_jin_jni_JniLoad_setde(JNIEnv *env, jclass type, jint a) {

    jstring pJstring = env->NewStringUTF("deiei");
    int b = 0;
    for (int i = 0; i < a; ++i) {
        b += b;
    }

    return pJstring;
}

JNIEXPORT void JNICALL
Java_com_jin_jni_JniLoad_nativeStartTcpServer(JNIEnv *env, jobject type, jint port);

JNIEXPORT void JNICALL
Java_com_jin_jni_JniLoad_nativeStartUdpServer(JNIEnv *env, jclass type, jint port) {

    // TODO

}
#ifdef __cplusplus
}
#endif
#endif
