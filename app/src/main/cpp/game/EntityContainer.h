#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include "../core/GDGEngine.h"


class EntityContainer{

private:
    const int maxOTypes;
    gdg::Entity* entities[16];

public:
    EntityContainer(int totalObjects) : maxOTypes(totalObjects){

    };
    ~EntityContainer();
    void init2dEntity();
    void updateEntities(double currentTime);
    void drawEntities();
};

#endif