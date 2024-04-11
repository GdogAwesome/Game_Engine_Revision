//
// Created by bradley on 11/4/21.
//
#include "renderer.h"
#include <android/log.h>

#define LOG_TAG "Renderer"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


void init_renderer(){
    init();
}
void change_surface(int width, int height){}
void renderObject(void* worldMatrix, renderList* r_list, int animFrame){

    on_draw( worldMatrix, r_list, animFrame);
}
void renderMapObject(void* worldMatrix,renderList* r_list, int animFrame){
    on_draw_map(worldMatrix, r_list, animFrame);
}
void renderMatMapObject( void* worldMatrix,renderList* r_list, int animFrame){
    on_draw_mat_map( worldMatrix, r_list, animFrame);
}
int loadT(const std::string* location){

    return 1;
}
