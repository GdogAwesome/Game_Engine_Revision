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

#ifndef ANDROID_FOPEN_H
#define ANDROID_FOPEN_H
#define  __USE_BSD 1
#include <stdio.h>
#include <android/asset_manager.h>


/* hijack fopen and route it through the android asset system so that
   we can pull things out of our packagesk APK */
#ifdef __cplusplus
extern "C" {
#endif
void android_set_asset_manager(AAssetManager *manager);
void android_fopen(const char *fname, char **buffer, size_t *size, __unused const char *mode);
void open_image(const char *fname, unsigned char **buffer, size_t *size);

#ifdef __cplusplus
}
#endif
//#define fopen(name, mode) android_fopen(name, mode)


#endif