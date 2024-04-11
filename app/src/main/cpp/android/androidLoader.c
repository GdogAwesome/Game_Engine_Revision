#include <alloca.h>
/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// The original code is from https://github.com/netguy204/gambit-game-lib
#include "androidLoader.h"
#include <errno.h>
#include <android/asset_manager.h>
#include <stdio.h>
#include "../deps/libpng/png.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include <android/asset_manager_jni.h>
#include <malloc.h>

#include <android/log.h>
#define LOG_TAG "libgl2jni"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static AAssetManager* android_asset_manager = NULL;

void android_set_asset_manager(AAssetManager* manager) {
    android_asset_manager = manager;
}

void open_image(const char* fname, unsigned char** buffer,size_t* size){
    AAsset* asset = AAssetManager_open(android_asset_manager, fname, 0);
    if(asset == NULL){
        LOGE("asset is null");
    }
    *size = (size_t)AAsset_getLength(asset);
    *buffer = (unsigned char*)malloc((sizeof(char) * (*size)));
    AAsset_read(asset, *buffer, *size);
    AAsset_close(asset);
}

void android_fopen(const char* fname, char** buffer, size_t* size, const char* mode) {

    AAsset* asset = AAssetManager_open(android_asset_manager, fname, 0);
    *size = (size_t)AAsset_getLength(asset);
    *buffer = (char*) malloc(sizeof(char)*(*size));
    AAsset_read(asset, *buffer, *size);

    AAsset_close(asset);

}