// Created by Denys on 04.07.2023.

#pragma once
#include <jni.h>
#include <vector>

class NativeBridge {
private:
    static const char* TAG;
    static bool isShouldRunThread;
    static JavaVM* mJvm;
    static JNIEnv* mEnv;
    static jobject mEspView;
    static jmethodID mUpdateEspData;
    static jfloatArray mEmptyEspData;

    // changes cue power and spin according to GlobalSettings
    static void* cuePropertiesThread(void*);
    // runs prediction and updates EspView
    static void* predictorThread(void*);

    static void initEmptyEspData();

    // AimTabViewModel methods
    static void updateAimSettings(
            JNIEnv*,
            jclass,
            jboolean drawLinesEnabled,
            jboolean drawShotStateEnabled,
            jboolean drawOpponentsLinesEnabled,
            jboolean preciseTrajectoriesEnabled,
            jint cuePower,
            jint cueSpin
            );

    // PredictorService methods
    static jfloatArray getPocketPositionsInScreen(
            JNIEnv* env,
            jclass,
            jfloat left,
            jfloat top,
            jfloat right,
            jfloat bottom
            );

    // creates a GlobalRef for EspView instance, starts predictorThread()
    static void setEspView(JNIEnv* env, jclass, jobject espView);

    // obtains fun updateEspData(data: FloatArray) method ID
    static int setUpdateEspDataMethodId(JNIEnv* env);

    // updates EspView shotState (trajectories and shot shotState)
    static void updateEspData(float* espData, int size);

    // clears EspView
    static void clearEspData();

    // releases GlobalRef to mEspView
    static void releaseGlobalRefs(JNIEnv* env);

    static void exitThread(JNIEnv*, jclass);

public:
    static int registerNativeMethods(JNIEnv* env);

};
