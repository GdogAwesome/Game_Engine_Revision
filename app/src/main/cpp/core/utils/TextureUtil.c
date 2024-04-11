//
// Created by bradley on 12/11/21.
//
#include "TextureUtil.h"


uint LoadTexture(const char* location, long size){

    int currentTexture = 0;
    bool textureLoaded = false;
    uint tex = 0;
    unsigned int texture = 0;

    //TODO maybe strtoimax is a better solution.
    for(int i=0; i < size; i++){
        texture += (int)((*location + i));
    }

    LOGE("texture id: %i", texture);

    if(tFirstLoad){
        LOGE("tFirstLoad");
        tex = textureId[0] = loadTexture(location);
        textureHash[0] = texture;
        totalTextures += 1;
        tFirstLoad = false;

    }else {

        for (int i = 0; i < totalTextures ; i++) {
            if (textureHash[i] == texture) {
                LOGE("texture already loaded");
                textureLoaded = true;
                currentTexture = i;
                i = totalTextures;

            }else{
                if(i == totalTextures ){

                    currentTexture = totalTextures + 1;
                    i = totalTextures;

                }
            }

        }

        if (textureLoaded) {
            tex = textureId[currentTexture];
        } else {
            tex = textureId[currentTexture] = loadTexture(location);
            totalTextures += 1;
            textureHash[currentTexture] = texture;
        }

    }
    //LOGE("texture hash:%i",textureHash[0]);
    return tex;

}
