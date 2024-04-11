//
// Created by bradley on 11/30/21.
//

#include "Loader.h"


//TODO I will make another utility program to handle the object loading in the future
#include "../../glInterface/glRend.h"

#include <android/log.h>
#define LOG_TAG "Loader"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

gVAO loadComplex2dObject(float vertice[], uint noOfVerts, float texCoords[], uint noOfTexCoords, const char* location){

}

gVAO loadObject(float vertices[], uint noOfVerts, float texCoords[], uint noOfTexCoords, const char* location, int textureNameSize){
    long size = 6;

    gVAO tmp = {
            LoadTexture(location, textureNameSize),
            //TODO "usage" is hardcoded. make some sort of universal standard that will accommodate my own enums
            create_vbo(noOfVerts, vertices, VERTEX_VBO, 0x88E4),
            create_vbo(noOfTexCoords, texCoords, TEXTURE_VBO, 0x88E4)
    };
    return tmp;
}

uint loadVBOf(float* data, int sizeOfData){
    return loadVBO(sizeOfData,data, 0x88E4);//create_vbo(sizeOfData, data, VERTEX_VBO, 0x88E4);
}
uint loadVBOi(int* data, int sizeOfData){
    return create_vbo(sizeOfData, data, VERTEX_VBO, 0x88E4);
}
uint loadVBOg(void* data, int sizeOfData){
    return create_vbo(sizeOfData, data, VERTEX_VBO, 0x88E4);
}
uint loadAdditionalTexture(const char* location, long size){
    return LoadTexture(location, size);
}
uint submitMap(int* mapTiles, int mapSize){
    return createTileIndex(mapTiles, mapSize);
}
void loadFile(const char* location, char** data, size_t* size){
    //TODO rename to make non-platform-specific
    android_fopen(location, data, size,NULL);
}
