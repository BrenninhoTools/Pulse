#pragma once

#include <jni.h>

extern "C" {

JNIEXPORT jlong JNICALL Java_com_pulse_app_PulseBridge_nativeCreateNetwork(JNIEnv* env, jobject thiz);

JNIEXPORT void JNICALL Java_com_pulse_app_PulseBridge_nativeDestroyNetwork(JNIEnv* env, jobject thiz, jlong handle);

JNIEXPORT jfloat JNICALL Java_com_pulse_app_PulseBridge_nativeTrainXor(JNIEnv* env, jobject thiz, jlong handle, jint epochs);

JNIEXPORT jfloatArray JNICALL Java_com_pulse_app_PulseBridge_nativePredict(JNIEnv* env, jobject thiz, jlong handle, jfloatArray input);

}
