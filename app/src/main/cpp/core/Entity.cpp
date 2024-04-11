//
// Created by bradley on 11/22/21.
//

#include "Entity.h"

//TODO this will be removed in final build
#include <android/log.h>
#define LOG_TAG "Entity"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace gdg;

    Entity::Entity() {

        //TODO this is just temporary and for testing. I am also ignoring the perspective issues for the time being.
        const float eyeX = 0.0f;
        const float eyeY = 0.0f;
        const float eyeZ = -0.5f;

        const float lookX = 0.0f;
        const float lookY = 0.0f;
        const float lookZ = -1.0f;

        const float upX = 0.0f;
        const float upY = 1.0f;
        const float upZ = 0.0f;

        //currentObject = {0};
        mView = glm::lookAt(
                glm::vec3(eyeX, eyeY, eyeZ),
                glm::vec3(lookX, lookY, lookZ),
                glm::vec3(upX, upY, upZ)
        );

        mProjection = glm::frustum( -1.0f, 1.0f,-1.0f, 1.0f, 0.1f, 10.0f);
    }

    Entity::~Entity(){
        freeEntity();

    }

    void Entity::setSimple2dMovement(simpleMoveRoutine* routine){
            entityRoutine = *routine;

            xMoveTotal = routine->maxLeftMove - routine->maxRightMove;
            xMoveAverage = xMoveTotal/2;

            yMoveTotal = routine->maxUpMove - routine->maxDownMove;
            yMoveAverage = yMoveTotal/2;

    }

    void Entity::init2dEntity(entitySpecs2d* specs) {
        LOGE("init specs ok");

        //TODO these are jus temporary until I decide if they are to be global or not.
        this->specs = specs;
        this->mapAssets = specs->_mapAssets;

        anim2d.AnimType = 0;
        anim2d.currentFrame = 0;
        anim2d.currentFrameTime = 0.0f;
        anim2d.frameTimeVariance = (60.0f / specs->framerate)/ 60.0f;
        anim2d.startFrame = 0;
        anim2d.reverse = false;
        anim2d.totalFrames = (specs->horizontalAnimFrames * specs->verticalAnimFrames) - 1;

        mPosition = glm::mat4(1.0f);

        uint vertsSize = 3 * VERTS_PER_QUAD * (specs->horizontalQuads * specs->verticalQuads);
        float verts[vertsSize];

        uint textSize = 2 * VERTS_PER_QUAD * (specs->horizontalAnimFrames * specs->verticalAnimFrames);
        float textCoords[textSize];

        generateQuad(verts, specs);
        quadTextureCoords(textCoords, specs->startX, specs->startY, specs->pixelWidth, specs->pixelHeight, textureSize, textureSize,
                          specs->horizontalAnimFrames, specs->verticalAnimFrames);

        LOGE("size of textCoords: %i", textSize);
        specs->entityData->vao = loadObject(verts, sizeof(verts), textCoords, sizeof(textCoords), specs->entityData->location[0], 12);
        r_list = (renderList*)malloc(sizeof(renderList));

        r_list->noOfObjects = 1;
        generateRenderList(specs, r_list);

        generateDrawIndices(0, 0,  1, 1, specs->horizontalQuads, specs->verticalQuads, 8, r_list);
        genMatrixOffsets(r_list->noOfObjects, specs->objectBounds[1] - specs->objectBounds[0], specs->objectBounds[2] - specs->objectBounds[3], specs->quadWidth, specs->quadHeight);

        LOGE("draw indices success");

    }

    void Entity::updateRoutine(double _currentTime){

        if(motionPercentInc){
            if(movePercentage < 1.0f) {
                movePercentage += 0.02f;
            }else{
                movePercentage -= 0.02f;
                motionPercentInc = false;
            }
        }else{
            if(movePercentage > 0.0f){
                movePercentage -= 0.02f;
            }else{
                movePercentage += 0.02f;
                motionPercentInc =  true;
            }
        }

        float deltaX = (movePercentage * entityRoutine.maxLeftMove) + ((1.0f - movePercentage) * entityRoutine.maxRightMove);
        float deltaY = (movePercentage * entityRoutine.maxDownMove) + ((1.0f - movePercentage) * entityRoutine.maxUpMove);

        deltaMove2d(deltaX, deltaY);
        updateAnim(_currentTime);
    }

    void Entity::updateAnim(double timeCurrent){
        anim2d.currentFrameTime = timeCurrent;
        advance2dAnim(&anim2d);
    }

    void Entity::deltaMove2d(float deltaX, float deltaY){

        for(int i = 0; i < r_list->noOfMatrices; i++){
            r_list->matrices[i][12] += deltaX;
            r_list->matrices[i][13] += deltaY;
        }
    }

    void Entity::setMatrixValues2d(float absX, float absY){

        glm::value_ptr(mPosition)[12] = absX;
        glm::value_ptr(mPosition)[13] = absY;

    }

    gVAO* Entity::getVao() {

        return &vao;
    }

    //void Entity::generateRenderListSimple(entitySpecs2d* inSpecs, )

    void Entity::generateRenderList(entitySpecs2d* inSpecs, renderList* r_list){

        if((inSpecs->_mapAssets->widthOfMap > 1) || (inSpecs->_mapAssets->heightOfMap > 1)){
            r_list->isMap = true;
        }else{
            r_list->isMap = false;
        }

        r_list->leadingTileMap = 0;

        r_list->renderOrder = (int*)malloc(sizeof(int) * r_list->noOfObjects);
        for(int i = 0; i < r_list->noOfObjects; i++){
            r_list->renderOrder[i] = i;
        }

        r_list->swapPointer = (void*)malloc(sizeof(void*));

        if(r_list->isMap) {
            r_list->storageArray = (float **) malloc(sizeof(float **) * r_list->noOfObjects);
            for (int s = 0; s < r_list->noOfObjects; s++) {
                r_list->storageArray[s] = (float *) malloc(
                        mapAssets->widthOfMap * mapAssets->heightOfMap * 8 * sizeof(float));
                loadMapArrays(mapAssets, r_list, s, 2, s, 0);
            }
        }

        mapAssets->xPos = r_list->noOfObjects;

        r_list->noOfTextures = inSpecs->imageCount;
        r_list->textures = (uint*)malloc(r_list->noOfTextures * sizeof(uint));
        r_list->textures[0] = inSpecs->entityData->vao.textureId;

        if(r_list->noOfTextures > 1){
            for(int i = 1; i < r_list->noOfTextures; i++) {
                r_list->textures[i] = loadAdditionalTexture(inSpecs->entityData->location[i], 7);
            }
        }

        r_list->drawIndices = (unsigned short**)malloc(r_list->noOfObjects * sizeof(unsigned short**));

        for(int i = 0; i< r_list->noOfObjects; i ++){
            *(r_list->drawIndices + i) = (unsigned short*)malloc((mapAssets->widthOfMap * mapAssets->heightOfMap * sizeof(unsigned short) * 6) * r_list->noOfObjects);
            //(unsigned short*)malloc((mapAssets->widthOfMap * mapAssets->heightOfMap * sizeof(unsigned short) * 6) * r_list->noOfObjects);
        }

        r_list->noOfTextureAttributes = inSpecs->imageCount;
        r_list->textureAttributes = (uint*)malloc(r_list->noOfTextureAttributes * sizeof(uint));
        r_list->textureAttributes[0] = inSpecs->entityData->vao.texCoordId;

        if(r_list->isMap){
            r_list->hasAnim = (float**)malloc(r_list->noOfObjects * sizeof(float **));

            for (int i = 0; i < r_list->noOfObjects; i++) {
                *(r_list->hasAnim + i) = (float*)malloc(
                        (mapAssets->widthOfMap * mapAssets->heightOfMap * sizeof(float) * 4) *
                        r_list->noOfObjects);
                loadMapArrayAnim(mapAssets, r_list, i, 1, i, 0);
            }
        }

        r_list->noOfVertexAttributes = 1;
        r_list->vertexAttributes = (uint*)malloc(r_list->noOfVertexAttributes * sizeof(uint));
        r_list->vertexAttributes[0] = inSpecs->entityData->vao.verticesId;

        r_list->sizeOfIndices = (inSpecs->_mapAssets->widthOfMap * inSpecs->_mapAssets->heightOfMap * 6);
        //r_list->textureIndices = (unsigned short*)malloc(sizeof(unsigned short) * r_list->sizeOfIndices);

        //TODO this is wierd and needs to be done elsewhere
        r_list->noOfMatrices = r_list->noOfObjects;
        //r_list->matrices = (float*)malloc(sizeof(float) * 16);

    }

    void Entity::genMatrixOffsets(int matrixCount, float widthOfObject, float heightOfObject, float _quadWidth, float _quadHeight){

        r_list->noOfMatrices = matrixCount;
        r_list->matrices = (float**)malloc(sizeof(float**) * matrixCount);

        for(int m = 0; m < matrixCount; m ++){
            *(r_list->matrices + m) = (float*)malloc(sizeof(float) * 16);
            for(int i = 0; i< 16; i++) {
                r_list->matrices[m][i] = glm::value_ptr(mPosition)[i];
            }
            if(m != 0) {
                r_list->matrices[m][12] = (r_list->matrices[m - 1][12] + (widthOfObject * 1.0f));
            }
        }
    }

    /*void Entity::loadMapArrayIndex(float outCoord[], float inCoord[], t_tileMapAssets* _mapAssets, int xPos, int yPos ){


    }*/

    void Entity::loadMapArrayAnim(t_tileMapAssets* _mapAssets, renderList* _r_list, int arrayNo, int valuesPerVertex, int startX, int startY){

        int inCoord = 0;
        int outCoord = 0;
        startX = startX * _mapAssets->widthOfMap;
        int xPadding = 0;
        int yPadding = 0;
        int verticesCount = vertsPerQuad * valuesPerVertex;

        for (int currentY = 0; currentY < (_mapAssets->heightOfMap) ; currentY++) {
            for (int currentX = 0; currentX < (_mapAssets->widthOfMap); currentX++) {

                inCoord  = (currentX + startX + (currentY * _mapAssets->widthOfSource)) * verticesCount;//works with hardcoded 8 but not verticesCount?
                outCoord = (currentX + startY + (currentY * _mapAssets->widthOfMap)) * verticesCount;

                for(int index = 0; index < verticesCount; index++) {
                    _r_list->hasAnim[arrayNo][outCoord + index] = _mapAssets->animationMap[inCoord + index];
                }
            }
        }
    }

    void Entity::loadMapArrays(t_tileMapAssets* _mapAssets, renderList* _r_list,int arrayNo,int valuesPerVertex, int startX, int startY){

        int inCoord = 0;
        int outCoord = 0;
        int verticesCount = vertsPerQuad * valuesPerVertex;

        startX = startX * _mapAssets->widthOfMap;

        for (int currentY = 0; currentY < (_mapAssets->heightOfMap); currentY++) {
            for (int currentX = 0; currentX < (_mapAssets->widthOfMap); currentX++) {

                inCoord  = (currentX + startX + (currentY * _mapAssets->widthOfSource)) * verticesCount;
                outCoord = (currentX + startY + (currentY * _mapAssets->widthOfMap)) * verticesCount;

                for(int index = 0; index < verticesCount; index++) {
                    _r_list->storageArray[arrayNo][outCoord + index] = _mapAssets->textureCoords[inCoord + index];
                }
            }
        }

    }
    void Entity::generateDrawIndices(int startX, int startY, int widthOfSource, int heightOfSource, int widthOfMap, int heightOfMap, int valuesPerQuad, renderList* r_list) {
        LOGE("draw indices start");

        int indicesLength = widthOfMap * heightOfMap * 6;

        int inCoord = 0;
        int outCoord = 0;

        for(int i = 0; i < r_list->noOfObjects; i++) {
            startX = (i * (widthOfMap * heightOfMap));

            for (int currentY = startY; (currentY - startY) < heightOfMap; currentY++) {
                for (int currentX = startX; (currentX - startX) < widthOfMap; currentX++) {

                    inCoord = ((currentX - startX) + ((currentY - startY) * widthOfMap)) * 4;
                    outCoord = ((currentX - startX) + ((currentY - startY) * widthOfMap)) * 6;

                    r_list->drawIndices[i][outCoord] = (unsigned short) (inCoord);
                    r_list->drawIndices[i][outCoord + 1] = (unsigned short) (inCoord + 1);
                    r_list->drawIndices[i][outCoord + 2] = (unsigned short) (inCoord + 2);
                    r_list->drawIndices[i][outCoord + 3] = (unsigned short) (inCoord + 2);
                    r_list->drawIndices[i][outCoord + 4] = (unsigned short) (inCoord + 1);
                    r_list->drawIndices[i][outCoord + 5] = (unsigned short) (inCoord + 3);
                }
            }
        }
        LOGE("after indices");

    }

    float* Entity::relativeObjectBounds2d(){
        float bounds[] = {(objectBounds[0] + glm::value_ptr(mPosition)[12]), objectBounds[1] + glm::value_ptr(mPosition)[12],
                        (objectBounds[2] + glm::value_ptr(mPosition)[13]), (objectBounds[3] + glm::value_ptr(mPosition)[13])};
        return bounds;
    }

    void Entity::generateQuad(float _polyCoords[], entitySpecs2d* specs) {

        float polyWidth = specs->quadWidth;//(_polyWidth / (float) horizontalFrames);
        float polyHeight = specs->quadHeight;//(_polyHeight / (float) verticalFrames);

        float totalWidth = polyWidth * specs->horizontalQuads;
        float totalHeight = polyHeight * specs->verticalQuads;

        float halfWidth = (float)totalWidth / 2.0f;
        float halfHeight = (float)totalHeight / 2.0f;

        float left;
        float right;
        float z = 1.0f;

        if (!specs->leftAlign) {
            left = 0.0f - (halfWidth * polyWidth);
            right = (halfWidth * polyWidth);
        } else {
            left = -halfWidth;
            right = halfWidth;
        }

        float top = 0.0f;
        float bottom = 0.0f;


        if(specs->topAlign) {
            top = 1.0f;//(halfHeight * polyHeight);
            bottom = totalHeight;//0.0f - (halfHeight * polyHeight);
        }else{
            top = (halfHeight * polyHeight);
            bottom = 0.0f - (halfHeight * polyHeight);
        }

        int counter = 0;
        int index = 0;

        for (float y = top; y > (top - totalHeight); y -= polyHeight) {
            for (float x = left; x < (left + totalWidth); x += polyWidth) {
                index = counter * (VERTS_PER_QUAD * 3);

                _polyCoords[index] = x;
                _polyCoords[index + 1] = y;
                _polyCoords[index + 2] = z;
                _polyCoords[index + 3] = x;
                _polyCoords[index + 4] = y - polyHeight;
                _polyCoords[index + 5] = z;
                _polyCoords[index + 6] = x + polyWidth;
                _polyCoords[index + 7] = y;
                _polyCoords[index + 8] = z;
                _polyCoords[index + 9] = x + polyWidth;
                _polyCoords[index + 10] = y - polyHeight;
                _polyCoords[index + 11] = z;

                counter++;
            }
        }
        specs->objectBounds[0] = left;
        specs->objectBounds[1] = right;
        specs->objectBounds[2] = top;
        specs->objectBounds[3] = bottom;
    }

    void Entity::quadTextureCoords(float _textCoords[], int _startX, int _startY, int _tilePWidth,
                                   int _tilePHeight, int textureWidth, int textureHeight,
                                   int _horizontalAnimFrames, int _verticalAnimFrames) {

        float textureFrameHeight = (float) _tilePHeight / (float) textureHeight;
        float textureFrameWidth = (float) _tilePWidth / (float) textureWidth;

        float offsetX = 0.0f;
        float offsetY = 0.0f;

        if (_startX > 0) {
            offsetX = (float)_startX / (float)textureWidth;
        }
        if (_startY > 0) {
            offsetY = (float) _startY / (float)textureHeight;
        }

        int horizontalAnimFrames = _horizontalAnimFrames;
        int verticleAnimFrames = _verticalAnimFrames;

        int textCoordsPerFrame = 2 * VERTS_PER_QUAD;
        int counter = 0;
        int index = 0;


        for (int v = 0; v < verticleAnimFrames; v++) {
            for (int h = 0; h < horizontalAnimFrames; h++) {

                index = counter * textCoordsPerFrame;

                _textCoords[index] = h * textureFrameWidth + offsetX;
                _textCoords[index + 1] = v * textureFrameHeight + offsetY;
                _textCoords[index + 2] = h * textureFrameWidth + offsetX;
                _textCoords[index + 3] = (v * textureFrameHeight) + textureFrameHeight + offsetY;
                _textCoords[index + 4] = (h * textureFrameWidth) + textureFrameWidth + offsetX;
                _textCoords[index + 5] = v * textureFrameHeight + offsetY;
                _textCoords[index + 6] = (h * textureFrameWidth) + textureFrameWidth + offsetX;
                _textCoords[index + 7] = (v * textureFrameHeight) + textureFrameHeight + offsetY;

                counter++;
            }
        }
    }

    void Entity::freeEntity(){

        //TODO I need to consult some documentation or other projects to see if this is even a good way to do things

        if(mapAssets != NULL){
            free(mapAssets);
            /*
            if(mapAssets->textureTypes != NULL) {
                free(mapAssets->textureTypes);
            }
            if(mapAssets->additionalVBOs != NULL){
                free(mapAssets->additionalVBOs);
            }
            if(mapAssets->textureTypes != NULL){
                free(mapAssets->textureTypes);
            }
             */
        }
        if(mapXYArray != NULL){
            free(mapXYArray);
        }

        if(tileMapIndices != NULL){
            free(tileMapIndices);
        }

        if(matrixOffsets != NULL){
            free(matrixOffsets);
        }
        if(textureIndices != NULL){
            free(textureIndices);
        }
        if(r_list != NULL){
            if(r_list->textureAttributes != NULL){
                free(r_list->textureAttributes);
            }
            if(r_list->textures != NULL){
                free(r_list->textures);
            }
            if(r_list->typesOfTextures != NULL){
                free(r_list->typesOfTextures);
            }
            if(r_list->vertexAttributes != NULL){
                free(r_list->vertexAttributes);
            }
            free(r_list);
        }

    }

    void Entity::draw(){
        renderObject((void *) &mView, r_list, anim2d.currentFrame);
    }

    renderList* Entity::getRenderList(){
        return r_list;
    }

