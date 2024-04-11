#include <jni.h>
#include <string>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

//TODO this may change in the future ?
#include "../game/gdgArcade.h"

#include "androidLoader.h"

#include <android/log.h>
#include <stdio.h>
#include <sstream>



#define LOG_TAG "libgl2jni"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static ANativeWindow *window;
static FILE *file;

static jboolean reachedEof = JNI_FALSE;
static AAssetManager* asset_manager = NULL;
static jobject android_asset_manager = NULL;

static ArcadeGame gameCore;

extern "C" {
JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1surface_1created(JNIEnv *env, jobject cls, jobject assetManager) {


    android_asset_manager = (*env).NewGlobalRef(assetManager);
    android_set_asset_manager(AAssetManager_fromJava(env,android_asset_manager));
    //window = ANativeWindow_fromSurface(env, surface);
    gameCore = ArcadeGame();
    gameCore.init_core();
}
JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1surface_1changed(JNIEnv *env, jobject cls, int width, int height) {
    (void) (env);
    (void) (cls);
    (width, height);
}
JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1draw_1frame(JNIEnv *env, jobject cls) {
    (void) (env);
    (void) (cls);
    gameCore.tick();
}

}

