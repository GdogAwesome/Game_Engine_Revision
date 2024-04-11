//
// Created by bradley on 12/11/21.
//

#ifndef TEXTUREUTIL_H
#define TEXTUREUTIL_H

#ifdef __cplusplus
extern "C"{
#endif

#include "Common.h"
#include "Loader.h"

//TODO these are going to be dynamic in the future
#include "../../glInterface/textureLoader.h"

//TODO this will be removed in final build
#include <android/log.h>
#define LOG_TAG "Texture Util"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static bool tFirstLoad = true;
static int totalTextures = 0;
//const int maxObjects = 16;
static uint textureId[16];
static int textureHash[16];
static int objectList[16];


uint LoadTexture(const char *location, long size);

#ifdef __cplusplus
}
#endif


#endif //TEXTUREUTIL_H
