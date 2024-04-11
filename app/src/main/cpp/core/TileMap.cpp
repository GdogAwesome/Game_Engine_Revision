//
// Created by bradley on 6/23/23.
//
#include "Entity.h"
#include "TileMap.h"


//TODO this will be removed in final build

#define LOG_TAG "TileMap"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace gdg;

    TileMap::TileMap(){

    }

    void TileMap::scrollTileMap(float deltaX, float deltaY){


        for(int i = 0; i < r_list->noOfMatrices; i++){
            r_list->matrices[i][12] += deltaX;
            r_list->matrices[i][13] += deltaY;
        }

        if( deltaX < 0){

            if((r_list->matrices[r_list->leadingTileMap][12] + objectBounds[1]) < -1 ){
                //r_list->matrices[r_list->leadingTileMap][12] = 0.0f;
                swapTileMaps2d(RIGHT);

            }
        }
    }

    void TileMap::swapTileMaps2d(int direction){

        int currentTileMap;
        bool loop = false;
        int previousMapTile = 0;
        int nextMapTile = 0;

        if(direction == RIGHT){
            if(r_list->leadingTileMap == r_list->noOfObjects - 1){

                currentTileMap = r_list->noOfObjects - 1;
                r_list->leadingTileMap = 0;
                previousMapTile = r_list->noOfObjects - 2;
                nextMapTile = 0;
            }else{
                LOGE("before fail");
                currentTileMap = r_list->leadingTileMap;
                r_list->leadingTileMap += 1;
                nextMapTile = r_list->leadingTileMap;
                if(currentTileMap == 0){
                    previousMapTile = r_list->leadingTileMap;
                }else {
                    previousMapTile = currentTileMap - 1;
                }
            }
            mapAssets->xPos += 1;
            r_list->matrices[currentTileMap][12] += r_list->matrices[nextMapTile][12] + (((specs->objectBounds[1] - specs->objectBounds[0]) * 0.5f) + ((specs->objectBounds[1] - specs->objectBounds[0]) * (r_list->noOfObjects - 1)));

            loadMapArrayAnim(mapAssets, r_list, currentTileMap, 1, (mapAssets->xPos + 1), 0);
            loadMapArrays(mapAssets,r_list,currentTileMap,2,(mapAssets->xPos + 1),0);
        }
    }

    void TileMap::generateTileMap(entitySpecs2d* specs, int tileMapCount){

        this->specs = specs;
        this->mapAssets = specs->_mapAssets;

        anim2d.AnimType = reciprocating;
        anim2d.currentFrame = 0;
        anim2d.currentFrameTime = 0.0f;
        anim2d.frameTimeVariance = (60.0f / specs->framerate)/ 60.0f;
        anim2d.startFrame = 0;
        anim2d.reverse = false;
        anim2d.totalFrames = (specs->horizontalAnimFrames * specs->verticalAnimFrames) - 1;

        mPosition = glm::mat4(1.0f);
        uint vertsSize = 3 * VERTS_PER_QUAD * (specs->horizontalQuads * specs->verticalQuads);
        float verts[vertsSize];

        uint textSize = 2 * VERTS_PER_QUAD * (specs->horizontalQuads * specs->verticalQuads);
        float textCoords[textSize];

        generateQuad(verts,specs);
        quadTextureCoords(textCoords,0,0, specs->pixelWidth, specs->pixelHeight, textureSize, textureSize, specs->horizontalAnimFrames, specs->verticalAnimFrames);
        LOGE("h Quads: %i", specs->horizontalQuads);

        for(int i = 0; i < 4; i ++){
            objectBounds[i] = specs->objectBounds[i];
        }

        specs->entityData->vao = loadObject(verts, sizeof(verts), textCoords, sizeof(textCoords), specs->entityData->location[0], 18);
        //specs->text
        r_list = (renderList*)malloc(sizeof(renderList));

        r_list->noOfObjects = tileMapCount;

        generateRenderList(specs, r_list);
        generateDrawIndices(0,0, mapAssets->widthOfSource, mapAssets->heightOfSource, mapAssets->widthOfMap, mapAssets->heightOfMap, 8, r_list);

        genMatrixOffsets(tileMapCount, specs->objectBounds[1] - specs->objectBounds[0], specs->objectBounds[2] - specs->objectBounds[3], specs->quadWidth, specs->quadHeight);
    }
    void TileMap::drawTileMap(){
        renderMapObject((void*) &mPosition, r_list, anim2d.currentFrame);
    }
void TileMap::drawMatTileMap(){

    renderMatMapObject((void*) &mPosition, r_list, anim2d.currentFrame);
}


