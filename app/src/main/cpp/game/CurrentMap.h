#ifndef CURRENTMAP_H
#define CURRENTMAP_H

#include "../core/utils/Loader.h"
#include "../core/Entity.h"
#include "../core/utils/entityHelper.h"
#include "../core/TileMap.h"

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>

//TODO this will be removed in final build
#include <android/log.h>
#define LOG_TAG "Map"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void loadMap(const char* location);
void updateMap(double timeCurrent);
void reorganizeMapFormat(int gridWidth,int gridHeight, int valuesPerQuad, int indicesArraySize, int animArraySize, t_tileMapAssets* _mapAssets);
std::string convertToString(char* charArray, int size);
void checkMapPos();
void loadAssets();
void drawMap();
void readLine(char** line, int* index, int* _charCount );

#endif