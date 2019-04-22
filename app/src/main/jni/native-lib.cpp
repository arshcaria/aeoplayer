//
// Created by jiaqi on 4/19/2019.
//
#include <jni.h>

extern "C" {
#include <libavcodec/avcodec.h>
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_aeoplayer_MainActivity_helloFromCpp(JNIEnv *env, jobject instance) {
    const char *msg = av_version_info();
    return env->NewStringUTF(msg);
}