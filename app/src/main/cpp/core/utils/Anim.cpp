#include "Anim.h"

void advance2dAnim(TextureAnimation* anim){

    if((anim->currentFrameTime - anim->previousFrameTime) >= anim->frameTimeVariance) {
        switch (anim->AnimType){
            case reciprocating:
                if (!anim->reverse) {
                    if (anim->currentFrame < anim->totalFrames){
                        anim->currentFrame += 1;
                    } else {
                        anim->reverse = true;
                        anim->currentFrame -= 1;
                    }
                }else {
                    if (anim->currentFrame > 0) {
                        anim->currentFrame -= 1;
                    } else if (anim->currentFrame == 0){
                        anim->reverse = false;
                        anim->currentFrame += 1;
                    }
                }
                break;
            default:
                break;
        }
        anim->previousFrameTime = anim->currentFrameTime;
    }

}
static void gen2dAnim(TextureAnimation& anim, int horizontalFrames, int verticleFrames, int animType){

}
