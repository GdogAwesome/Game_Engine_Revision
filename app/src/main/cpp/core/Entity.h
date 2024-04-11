//
// Created by bradley on 11/22/21.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "renderer.h"
#include "utils/Loader.h"
#include "utils/Anim.h"
#include "utils/entityHelper.h"

//FIXME this will have to change for more efficient use in dreamcast?
#include "../deps/glm-master/glm/glm.hpp"
#include "../deps/glm-master/glm/gtc/type_ptr.hpp"

namespace gdg {

    class Entity {
    private:
        float xMoveAverage = 0;
        float yMoveAverage = 0;

    public:
        Entity();

        typedef struct{
            float maxLeftMove;
            float maxRightMove;
            float maxUpMove;
            float maxDownMove;
            bool alternateXMove;
            bool alternateYMove;
            float timeDelta;
        }simpleMoveRoutine;

        entitySpecs2d* specs = NULL;

        t_tileMapAssets* mapAssets = NULL;
        renderList* r_list = NULL;
        float* mapXYArray = NULL;
        float* textureIndices = NULL;
        float* matrixOffsets = NULL;
        static int totalTileMaps;

        void init2dEntity(entitySpecs2d* specs);
        void loadMapArrayIndex(float outCoord[], float inCoord[], t_tileMapAssets* _mapAssets, int xPos, int yPos);

        void updateRoutine(double _currentTime);
        void setSimple2dMovement(simpleMoveRoutine* routine);
        void updateAnim(double timeCurrent);
        void addSecond();
        void deltaMove2d(float deltaX, float deltaY);
        void setMatrixValues2d(float absX, float absY);
        float* relativeObjectBounds2d();
        void freeEntity();

        ~Entity();

        renderList* getRenderList();
        void draw();


        gVAO *getVao();


    protected:
        //Entity data
        glm::mat4 mPosition;
        //TODO test variables
        glm::mat4 mView;
        glm::mat4 MVPMatrix;
        glm::mat4 mTempPosition;
        glm::mat4 MVMatrix;
        glm::mat4 mProjection;

        bool motionPercentInc = true;
        float xMoveTotal = 0;
        float yMoveTotal = 0;
        float movePercentage = 0.0f;

        const int RIGHT = 0;
        const int LEFT = 1;
        const int UP = 2;
        const int DOWN = 3;

        unsigned int texture[2];
        float objectBounds[4];
        unsigned short* tileMapIndices;

        simpleMoveRoutine entityRoutine;
        static gVAO VAOs[18];
        TextureAnimation anim2d;
        gVAO vao{};

        void generateQuad(float _polyCoords[],entitySpecs2d* specs);

        void quadTextureCoords(float _textCoords[], int _startX, int _startY, int _tilePWidth,
                                 int _tilePHeight, int textureWidth, int textureHeight,
                                 int _horizontalAnimFrames, int _verticalAnimFrames);

        void genMatrixOffsets(int matrixCount, float widthOfObject, float heightOfObject, float _quadWidth, float _quadHeight);
        void generateRenderList(entitySpecs2d* inSpecs, renderList* r_list);
        void generateDrawIndices(int startX, int startY, int widthOfSource, int heightOfSource , int widthOfMap, int heightOfMap, int valuesPerQuad, renderList* r_list);
        void loadMapArrays(t_tileMapAssets* _mapAssets, renderList* _r_list, int arrayNo,int valuesPerVertex, int startX, int startY);
        void loadMapArrayAnim(t_tileMapAssets* _mapAssets, renderList* _r_list, int arrayNo, int valuesPerVertex, int startX, int startY);



    };
}
#endif //RENDERERD_DREAM_ENTITY_H
