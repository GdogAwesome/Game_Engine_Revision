//
// Created by b_hul on 10/29/2022.
//
#include "entityHelper.h"

entitySpecs2d genEntitySpecs(int startX, int startY, int horizontalQuads, int verticalQuads, int horizontalFrames, int verticalFrames, int framerate, int pixelWidth, int pixelHeight, float quadWidth, float quadHeight, int imageCount, char** imageLocations,bool leftAlign, bool topAlign,int materialCount, int materialTypes[]){
    entitySpecs2d specs;

    specs.startX = startX;
    specs.startY = startY;
    specs.horizontalQuads = horizontalQuads;
    specs.verticalQuads = verticalQuads;
    specs.horizontalAnimFrames = horizontalFrames;
    specs.verticalAnimFrames = verticalFrames;
    specs.framerate = framerate;
    specs.pixelWidth = pixelWidth;
    specs.pixelHeight = pixelHeight;
    specs.quadWidth = quadWidth;
    specs.quadHeight = quadHeight;
    specs.leftAlign = leftAlign;
    specs.topAlign = topAlign;
    specs.entityData = new RawEntityData ;
    specs.entityData->location = (char**) malloc(sizeof(char*) * imageCount);
    specs.imageCount = imageCount;
    specs.material = (int*)malloc(sizeof(int) * materialCount);
    specs.material = materialTypes;

    //set default values for _mapAssets
    specs._mapAssets = new t_tileMapAssets ;
    specs._mapAssets->heightOfMap = 1;
    specs._mapAssets->widthOfMap = 1;
    specs._mapAssets->heightOfSource = 1;
    specs._mapAssets->widthOfSource = 1;


    for(int o = 0; o < imageCount; o++) {
        specs.entityData->location[o] = imageLocations[o];
    }
    return specs;
}