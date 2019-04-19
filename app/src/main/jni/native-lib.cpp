//
// Created by jiaqi on 4/19/2019.
//
#include <jni.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_aeoplayer_MainActivity_helloFromCpp(JNIEnv *env, jobject instance) {
    const char *msg = "Hello From JNI";
    return env->NewStringUTF(msg);
}