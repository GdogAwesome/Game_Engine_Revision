#ifndef GDGARCADE_H
#define GDGARCADE_H

#include "../core/GDGEngine.h"
#include "EntityContainer.h"
#include <sys/time.h>
#include "CurrentMap.h"

using namespace gdg;
class ArcadeGame : public gdg::gCore{
public:
    ArcadeGame();
    ~ArcadeGame();
    void initEntities();
    void on_change_surface(int width, int height);
    void init_core();
    void tick();
private:
    double timeCurrent;
    bool readyToRender;
    long timeSinceLastFrame = 0;
    long timeRemainder = 0;
    long totalTime = 0 ;

    long getCpuTime();
    EntityContainer* enemyContainer = new EntityContainer(16);
};

#endif
