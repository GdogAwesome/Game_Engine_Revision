#include <jni.h>
#include "glInterface/renderer.h"
#include <string>


extern "C" {

JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1surface_1created(JNIEnv * env, jobject cls){
    (void)(env);
    (void)(cls);
    on_surface_created();
}
JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1surface_1changed(JNIEnv * env, jobject cls, int width, int height){
    (void)(env);
    (void)(cls);
    on_surface_changed(width, height);
}
JNIEXPORT void JNICALL Java_com_gdogawesome_rendererddream_JNIWrapper_on_1draw_1frame(JNIEnv * env, jobject cls){
    (void)(env);
    (void)(cls);
    on_draw_frame();
}

}
