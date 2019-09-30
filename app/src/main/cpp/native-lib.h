//
// Created by Jeziel Lago on 2019-09-30.
//

#include <jni.h>
#include <string>
#include "picosha2.h"

#ifndef JNITEST_NATIVE_LIB_H
#define JNITEST_NATIVE_LIB_H

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeziellago_jniteste_MainActivity_getAndroidId(JNIEnv *env, jobject);

#endif //JNITEST_NATIVE_LIB_H
