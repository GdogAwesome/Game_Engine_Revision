//
// Created by bradley on 11/4/21.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "utils/Loader.h"
#include <string>
#include "../core/utils/Common.h"

//TODO make this list dynamically in cmake after deciding finalizing structure
#include "../glInterface/glRend.h"


void init_renderer();
void change_surface(int width, int height);
void renderObject(void* worldMatrix, renderList* r_list, int animFrame);
int loadT(const std::string* location);
void renderMatMapObject(void* worldMatrix, renderList* r_list, int animFrame);
void renderMapObject(void* worldMatrix,renderList* r_list, int animFrame);

#endif //RENDERERD_DREAM_RENDERER_H
