//
// Created by jiaqi on 4/23/2019.
//

#ifndef AEOPLAYER_JAVACALLHELPER_H
#define AEOPLAYER_JAVACALLHELPER_H


#include <jni.h>

class JavaCallHelper {
public:
    JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject instance);

    ~JavaCallHelper();

    void onError(int thread, int errorCode);

    void onPrepare(int thread);

private:
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;
    jmethodID onErrorId;
    jmethodID onPrepareId;
};


#endif //AEOPLAYER_JAVACALLHELPER_H
