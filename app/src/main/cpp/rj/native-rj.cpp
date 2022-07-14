#include <jni.h>
#include "rjdva_c.h"
#include <string.h>
#include <stdlib.h>


extern "C" JNIEXPORT jboolean
Java_com_midea_jnitest_hwstk_RJCtrl_rjdva_Init(
        JNIEnv *env,
        jclass cls,
        jstring jstrDeviceId,
        jstring jstrServerIpPor,
        jstring jstrWorkspacePath, jstring jstrConfig, jboolean bPureVision,
        jboolean bCameraFormatMJPEG
) {
    bool ret = 0;
    char *deviceId = jstringToChar(env, jstrDeviceId);
    char *ServerIpPor = jstringToChar(env, jstrServerIpPor);
    char *path = jstringToChar(env, jstrWorkspacePath);
    char *config = jstringToChar(env, jstrConfig);
    //LOGI("deviceId : %s por:%s path:%s config:%s", deviceId, ServerIpPor, path, config);
    ret = rjdva_Init(deviceId, ServerIpPor, path, config, bPureVision, bCameraFormatMJPEG);
    return ret;
}

static char *jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

