#include "gdgArcade.h"

using namespace gdg;

ArcadeGame::ArcadeGame(){

}
ArcadeGame::~ArcadeGame(){

}
void ArcadeGame::init_core(){
    timeCurrent = 0;
    readyToRender = false;
    init_renderer();
   // enemyContainer->init2dEntity();
    loadMap("maps/test9.dat");
    LOGE("load map complete");

    readyToRender = true;

}
void ArcadeGame::tick(){
    //TODO fix timing this will not do, for anything other than testing
    timeCurrent += 0.0166666f;
   /* if(timeCurrent >= 1.0f){
        timeCurrent = timeCurrent - 1.0f;
        enemyContainer->addSecond();
    }
    */

    if(readyToRender){
        //enemyContainer->updateEntities(timeCurrent);
        updateMap(timeCurrent);
        drawMap();
        //enemyContainer->drawEntities();

    }
    //totalTime = getCpuTime();

}
long ArcadeGame::getCpuTime(){
    struct timeval val;
    gettimeofday(&val,NULL);
    return val.tv_usec/1000;//((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

void ArcadeGame::initEntities(){

}



