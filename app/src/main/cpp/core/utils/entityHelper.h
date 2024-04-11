//
// Created by b_hul on 10/29/2022.
//

#ifndef RENDERERD_DREAM_ENTITYHELPER_H
#define RENDERERD_DREAM_ENTITYHELPER_H

#include "Common.h"
#include "Loader.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    int noOfAdditionalVBOs;
    char** location;
    float* animationMap;
    float* textureCoords;
    gVAO vao;
}RawEntityData;

typedef struct{
    uint mapId;
    int noOfTextures;
    int widthOfSource;
    int heightOfSource;
    int xPos;
    int widthOfMap;
    int yPos;
    int heightOfMap;
    int sizeOfMatrix;
    float* animationMap;
    float* textureCoords;
}t_tileMapAssets;

typedef struct{
    int startX;
    int startY;
    int horizontalQuads;
    int verticalQuads;
    int horizontalAnimFrames;
    int verticalAnimFrames;
    int framerate;
    int pixelWidth;
    int pixelHeight;
    int imageCount;
    float quadWidth;
    float quadHeight;
    float objectBounds[4];
    uint* textureTypes;
    bool leftAlign;
    bool topAlign;
    bool mat;
    int* material;
    RawEntityData* entityData;
    t_tileMapAssets* _mapAssets;
}entitySpecs2d;




entitySpecs2d genEntitySpecs(int startX, int startY, int horizontalQuads, int verticalQuads, int horizontalFrames, int verticalFrames, int framerate, int pixelWidth, int pixelHeight, float quadWidth, float quadHeight, int imageCount, char** imageLocations,bool leftAlign, bool topAlign, int materialCount, int materialTypes[]);

#ifdef __cplusplus
}
#endif

#endif //RENDERERD_DREAM_ENTITYHELPER_H
