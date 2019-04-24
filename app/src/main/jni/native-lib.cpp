//
// Created by jiaqi on 4/19/2019.
//
#include <jni.h>
#include "FFmpegMgr.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

JavaVM *javaVM;
FFmpegMgr *ffmpeg;

int JNI_OnLoad(JavaVM *vm, void *r) {
    javaVM = vm;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_aeoplayer_AeoPlayer_native_1prepare(JNIEnv *env, jobject instance,
                                                     jstring dataSource_) {
    const char *dataSource = env->GetStringUTFChars(dataSource_, 0);
    JavaCallHelper *callHelper = new JavaCallHelper(javaVM, env, instance);
    ffmpeg = new FFmpegMgr(callHelper, dataSource);
    ffmpeg->prepare();
    env->ReleaseStringUTFChars(dataSource_, dataSource);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_aeoplayer_AeoPlayer_nativeStart(JNIEnv *env, jobject instance) {

}