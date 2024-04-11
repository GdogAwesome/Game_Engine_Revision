#ifndef _ANIM_H
#define _ANIM_H

#include "Common.h"

//Anim types
static const int reciprocating = 0;
static const int continuous = 1;
static const int looping = 2;

static const bool canInterrupt = false;

typedef struct {
    int AnimType{0};
    double currentFrameTime = 0.0f;
    double previousFrameTime = 0.0f;
    float frameTimeVariance = 0.0f;
    bool reverse = false;
    int totalFrames{0};
    int startFrame{0};
    int currentFrame{0};
}TextureAnimation;

void advance2dAnim(TextureAnimation* anim);
static void gen2dAnim(TextureAnimation& anim, int horizontalFrames, int verticleFrames, int animType);


#endif