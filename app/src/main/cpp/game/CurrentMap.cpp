#include "CurrentMap.h"



//TODO this may be just a temporary location for these
size_t size;
char* data;

float testMove = 0.0f;
float* textureIndices;
int mapLength = 0;
int mapHeight = 0;
unsigned short* mIndices;

//gdg::Entity::t_tileMapAssets* mapAssets;
entitySpecs2d* entitySpecs;
entitySpecs2d* backgroundSpecs;
int mapSectionCount = 2;
gdg::TileMap* mapSections[2];



void loadMap(const char* location){
    for(int i = 0; i < mapSectionCount; i++){
        mapSections[i] = new gdg::TileMap();
    }

    loadFile(location, &data, &size);
    loadAssets();
}

void loadAssets(){

    entitySpecs = new entitySpecs2d();
    backgroundSpecs = new entitySpecs2d();
    char* line = (char *)malloc(100 *  sizeof(char));
    int charCount = 0;
    int i = 0;
    int tempU = 0;
    int tempV = 0;
    float tmpAnim = 0.0f;
    bool uIsZero = false;
    bool vIsZero = false;

    //TODO this is hardcoded for now but will change in the future

    //map texture location
    readLine(&line, &i, &charCount);

    //map length
    readLine(&line, &i, &charCount);
    mapLength = atoi(line);

    //map height
    readLine(&line, &i, &charCount);
    mapHeight = atoi(line);



    char** locations = new char* [2];
    locations[0] = "images/cyber_map.png";
    locations[1]="images/cyber_map_norm.png";

    char** backgroundImage = new char* [1];
    backgroundImage[0]="images/city_bgd.png";//"images/cyber_map.png";

    int material[] = {2,2};
    int backgroundMaterial[] = {1};

    *entitySpecs = genEntitySpecs(0, 0, 12, 10, 4, 1, 8,300, 200, 0.25f, 0.3333f, 2, locations, true, true, 2, material );
    *backgroundSpecs = genEntitySpecs(0, 0, 1, 1, 1, 1, 1, 2048, 1080, 2.0f, 2.0f, 1, backgroundImage,true, true, 1, backgroundMaterial);

    entitySpecs->_mapAssets->noOfTextures = 2;
    entitySpecs->_mapAssets->widthOfMap = entitySpecs->horizontalQuads;
    entitySpecs->_mapAssets->heightOfMap = entitySpecs->verticalQuads;
    entitySpecs->_mapAssets->widthOfSource = (mapLength * 2);
    entitySpecs->_mapAssets->heightOfSource = (mapLength * 2);
    entitySpecs->textureTypes = (uint *) malloc(entitySpecs->_mapAssets->noOfTextures * sizeof(uint));

    backgroundSpecs->_mapAssets->noOfTextures = 1;
    backgroundSpecs->_mapAssets->widthOfMap = backgroundSpecs->horizontalQuads;
    backgroundSpecs->_mapAssets->heightOfMap = backgroundSpecs->verticalQuads;
    backgroundSpecs->_mapAssets->widthOfSource = 1;
    backgroundSpecs->_mapAssets->heightOfSource = 1;
    backgroundSpecs->textureTypes = (uint *) malloc(backgroundSpecs->_mapAssets->noOfTextures * sizeof(uint));

    LOGE("after mapassets setup");
    //TODO this needs to probably be allocated elsewhere as it is not a good place to do it here hence previous todo
    int animMapSize = (entitySpecs->_mapAssets->widthOfSource * entitySpecs->_mapAssets->heightOfSource * 4);
    entitySpecs->_mapAssets->animationMap = (float*)malloc(sizeof(float) * animMapSize);

    backgroundSpecs->_mapAssets->animationMap = (float*)malloc(sizeof(float) * 4 * 3);

    for(int i = 0; i < (4 * 3 ); i++) {
        backgroundSpecs->_mapAssets->animationMap[i] = 0;
    }

    backgroundSpecs->_mapAssets->textureCoords = (float*)malloc(sizeof(float) * 3 * 8);

    for(int i = 0; i < backgroundSpecs->_mapAssets->widthOfSource; i++){
        int pastCount = i * 8;
        //for(int j = 0; j < 8; j++){
            backgroundSpecs->_mapAssets->textureCoords[pastCount]     = 0.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 1] = 0.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 2] = 0.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 3] = 1.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 4] = 1.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 5] = 0.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 6] = 1.0f;
            backgroundSpecs->_mapAssets->textureCoords[pastCount + 7] = 1.0f;
       // }

    }

    int textureIndicesSize = (entitySpecs->_mapAssets->widthOfSource * entitySpecs->_mapAssets->heightOfSource * 8 );
    textureIndices = (float *)malloc(textureIndicesSize * sizeof(float));

    entitySpecs->_mapAssets->textureCoords = (float *)malloc(textureIndicesSize * sizeof(float));

        for(int h = 0; h < mapHeight ; h ++) {
             for (int w = 0; w < mapLength * 4; w += 4) {
                 readLine(&line, &i, &charCount);
                 readLine(&line, &i, &charCount);

                 for (int y = 0; y < 2; y++) {
                     for (int x = 0; x < 2; x++) {
                         readLine(&line, &i, &charCount);
                         readLine(&line, &i, &charCount);

                         readLine(&line, &i, &charCount);
                         tempU = atoi(line);
                         //LOGE("tempU: %i", tempU);

                         readLine(&line, &i, &charCount);
                         tempV = atoi(line);


                         if (tempU >= 2048) {
                             tempU = 0;
                             tempV = 0;
                         }

                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8]     = (float)(tempU / 200);
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 1] = (float)(tempV / 150);
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 2] = (float)(tempU / 200);
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 3] = (float)(tempV / 150) + 1;
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 4] = (float)(tempU / 200) + 1;
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 5] = (float)(tempV / 150);
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 6] = (float)(tempU / 200) + 1;
                         textureIndices[(((h * mapLength * 4) + w) + x + (y * 2)) * 8 + 7] = (float)(tempV / 150) + 1;

                         //Obstacle value
                         readLine(&line, &i, &charCount);

                         //isAnimated boolean
                         readLine(&line, &i, &charCount);

                         //TODO this is a bad hack. Fix soon
                         std::string tmpLine = "";
                         tmpLine = convertToString(line, 4);

                         if(strcmp(tmpLine.c_str(), "true") == 0){
                             tmpAnim = 1.0f;
                         }else if(strcmp(tmpLine.c_str(), "fals") == 0){
                             tmpAnim = 0.0f;
                         }

                         entitySpecs->_mapAssets->animationMap[(((h * mapLength * 4 ) + w + x + (y * 2) ) * 4)] = tmpAnim;
                         entitySpecs->_mapAssets->animationMap[(((h * mapLength * 4 ) + w + x + (y * 2) ) * 4) + 1] = tmpAnim;
                         entitySpecs->_mapAssets->animationMap[(((h * mapLength * 4 ) + w + x + (y * 2) ) * 4) + 2] = tmpAnim;
                         entitySpecs->_mapAssets->animationMap[(((h * mapLength * 4 ) + w + x + (y * 2) ) * 4) + 3] = tmpAnim;

                         //obstacle dimensions
                         for (int j = 0; j < 4; j++) {
                             readLine(&line, &i, &charCount);
                         }
                     }
                 }
             }
         }
    int testStartIndex = 0;

        entitySpecs->_mapAssets->textureCoords = textureIndices;


    reorganizeMapFormat((mapLength * 2 ), (mapHeight * 2), 8, textureIndicesSize, animMapSize, entitySpecs->_mapAssets);
    mapSections[0]->generateTileMap(entitySpecs, 3);
    mapSections[1]->generateTileMap(backgroundSpecs,3);

    free(data);
}
void updateMap(double timeCurrent){
    testMove = -.006f;
    //TODO test bring to mapSectionCount later
    for(int i = 0; i < 1; i++) {
        mapSections[i]->scrollTileMap(testMove, 0.0f);
        mapSections[i]->updateAnim(timeCurrent);
    }

    checkMapPos();
}
void checkMapPos(){
    for(int i = 0; i < 1; i++){// mapSectionCount; i ++) {
        if (mapSections[i]->relativeObjectBounds2d()[1] < 0.0f) {
            mapSections[i]->setMatrixValues2d(0.0f, 0.0f);
        }
    }
}
void drawMap(){
    //TODO hack for debugging fix
    mapSections[1]->drawTileMap();
    mapSections[0]->drawMatTileMap();
/*
    for(int i = 0; i < mapSectionCount; i++) {
        mapSections[i]->drawTileMap();
    }
    */

}
void reorganizeMapFormat(int gridWidth, int gridHeight, int valuesPerQuad, int indicesArraySize, int animArraySize, t_tileMapAssets* _mapAssets) {
    //TODO this is all just over-complicated maneuvering to make up for poor map storage. This needs to be fixed
    int quadsPerBlock = 4;
    int animsPerQuad = 4;
    int totalRowSize = mapLength * quadsPerBlock;
    int pTextureIndex = 0;
    int animPTextureIndex = 0;
    int block = 0;
    int textureIndicesIndex = 0;
    int realY = 0;

    //int endPointX = startIndex + mapSections[0]->mapAssets->widthOfMap;
    //int endPointY = mapSections[0]->mapAssets->heightOfMap;

    float tempIndices[indicesArraySize];
    bool tempAnimMap[animArraySize];

    for (int h = 0; h < (mapHeight * 2); h += 2) {
        for (int w = 0; w < (mapLength * 2); w += 2) {

            if (h == 0) {
                realY = 0;
            } else {
                realY = h / 2;
            }

            block = ((totalRowSize * realY) + (w * 2));

            for (int qh = 0; qh < 2; qh++) {
                for (int qw = 0; qw < 2; qw++) {

                    pTextureIndex = (block + (qh * 2) + qw);
                    animPTextureIndex = (block + (qh * 2) + qw);
                    textureIndicesIndex = ((h * mapLength * 2) + w) + ((qh * (mapLength * 2)) + qw)  ;

                    for(int iIndexAdd = 0; iIndexAdd < valuesPerQuad; iIndexAdd++) {
                        tempIndices[(textureIndicesIndex * valuesPerQuad) + iIndexAdd] = _mapAssets->textureCoords[(pTextureIndex * valuesPerQuad) + iIndexAdd];
                    }

                    for(int aIndexAdd = 0; aIndexAdd < animsPerQuad; aIndexAdd++){
                        tempAnimMap[(textureIndicesIndex * animsPerQuad) + aIndexAdd] = _mapAssets->animationMap[(animPTextureIndex * animsPerQuad) + aIndexAdd];
                    }
                }
            }
        }
    }


    for (int i = 0; i < indicesArraySize; i++) {
        _mapAssets->textureCoords[i] = tempIndices[i];
    }

    for(int i = 0; i < animArraySize; i++){
        _mapAssets->animationMap[i] = tempAnimMap[i];
    }


}
void loadMapDrawIndices(float* inIndices, size_t size){

    entitySpecs->_mapAssets->textureCoords = inIndices;

}
void loadAnimationMap(float* inAnimMap, size_t mapSize){


}


std::string convertToString(char* charArray, int size){
    std::string tmp = "";
    for(int i = 0; i < size; i++){
        tmp += charArray[i];
    }

    return tmp;
}
void readLine(char** line, int* index, int* _charCount){
    int lineCount = 0;
    for(int _index = *index; _index < size; _index++) {
        if (data[_index] == '\n' || data[_index] == '\0') {
            for (int d = 0; d < 100 - 1; d++) {
                *(*line + d) = NULL;
            }
            for (int c = ((_index) - (*_charCount)); c < (_index); c++) {
                *(*line + lineCount) = data[c];
                lineCount++;
            }
            *index = _index + 1;
            *_charCount = 0;
            return;

        } else {
            *_charCount += 1;

        }
    }

}
