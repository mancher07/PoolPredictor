// Created by Denys on 04.07.2023.

#pragma once
#include <jni.h>
#include <vector>

class NativeBridge {
private:
    static const char* TAG;
    static bool isShouldRunThread;
    static bool isToastShown;
    static JavaVM* mJvm;
    static JNIEnv* mEnv;
    static jobject mEspView;
    static jmethodID mUpdateEspData;

    // runs prediction and updates EspView
    static void* predictor_thread(void*);

    // AimTabViewModel methods
    static void setDrawLines(JNIEnv*, jobject, bool value);
    static void setDrawShotState(JNIEnv*, jobject, bool value);
    static void setDrawOpponentsLines(JNIEnv*, jobject, bool value);
    static void setPowerControlModeEnabled(JNIEnv*, jobject, bool value);
    static void setCuePower(JNIEnv*, jobject, int power);
    static void setCueSpin(JNIEnv*, jobject, int spin);

    // FloatingMenuService methods

    static jfloatArray getPocketPositionsInScreen(JNIEnv* env, jobject, jint left, jint top, jint right, jint bottom);

    // shows toast to user, must be called before predictor_thread
    static void setServiceContext(JNIEnv* env, jobject, jobject serviceContext);

    // creates a GlobalRef for EspView instance, starts predictor_thread()
    static void setEspView(JNIEnv* env, jobject, jobject espView);

    // obtains fun updateEspData(data: FloatArray) method ID
    static int setUpdateEspDataMethodId();

    // updates EspView state (trajectories and shot state)
    static void updateEspData(const std::vector<float>& espData);

    // releases GlobalRef to mEspView
    static void releaseGlobalRefs(JNIEnv* env);

    // FloatingMenuLayout methods
    static jstring getIcon(JNIEnv *env, jobject);

    static void exitThread(JNIEnv*, jobject);

public:
    static int registerNativeMethods(JNIEnv* env);

};
