//
// Created by bradley on 1/16/22.
//

#ifndef LOADER_H
#define LOADER_H

#include "Common.h"
#include <stdio.h>
#include "TextureUtil.h"

//TODO another non dynamic include
#include "../../android/androidLoader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint;
typedef struct {
    uint textureId;
    uint verticesId;
    uint texCoordId;
} gVAO;


gVAO loadObject(float vertices[], uint noOfVertices, float texCoords[], uint noOfTexCoords,
                const char *location, int textureNameSize);
uint loadAdditionalTexture(const char* location, long size);
uint loadVBOf(float* data, int sizeOfData);
uint loadVBOi(int* data, int sizeOfData);
uint loadVBOg(void* data, int sizeOfData);
void loadFile(const char *location, char **data, size_t *size);
uint submitMap(int* mapTiles, int mapSize);

#ifdef __cplusplus
}
#endif


#endif //RENDERERD_DREAM_LOADER_H
