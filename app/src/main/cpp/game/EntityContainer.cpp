#include "EntityContainer.h"

void EntityContainer::updateEntities(double currentTime) {
    for(int i = 0; i < maxOTypes; i++) {
        entities[i]->updateRoutine(currentTime);
        //entities[i]->deltaMove2d(-0.002f, -0.002f);
        //entities[i]->updateAnim(currentTime);
    }
}
gdg::Entity::simpleMoveRoutine* testRoutine = new gdg::Entity::simpleMoveRoutine;
void EntityContainer::init2dEntity() {


    for(int i = 0; i < maxOTypes; i++) {

        testRoutine->maxLeftMove = -0.02f;
        testRoutine->maxRightMove = 0.02f;
        testRoutine->maxUpMove = 0.02f;
        testRoutine->maxDownMove = -0.02f;
        testRoutine->timeDelta = 0.03f;
        testRoutine->alternateXMove = false;
        testRoutine->alternateYMove = true;

        entities[i] = new gdg::Entity();
        entities[i]->setSimple2dMovement(testRoutine);
        entities[i]->specs = new entitySpecs2d ;

        char** locations = new char*[1];
        locations[0] = "images/ship.png";

        int material[] = {2,2};

        *entities[i]->specs = genEntitySpecs(0, 500,1, 1, 4, 1, 8, 300, 250, .25f, 0.33333f, 1, locations, true,true, 1, material);
        entities[i]->init2dEntity(entities[i]->specs);
    }

    LOGE("entities done");
}
void EntityContainer::drawEntities() {
    for(int i = 0; i < maxOTypes; i++) {
        entities[0]->draw();
    }
}
