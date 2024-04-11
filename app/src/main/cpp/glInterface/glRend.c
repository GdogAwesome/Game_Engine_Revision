//
// Created by brad on 9/20/21.
//
#include "glRend.h"

#include "shader.h"
#include "../core/utils/Common.h"
#include <stdio.h>
#include <stdlib.h>

//#include "../deps/glm-master/glm/glm.hpp"
//#include "../deps/glm-master/glm/gtc/type_ptr.hpp"

//#include <android/native_window.h>
//#include <android/native_window_jni.h>

#include <android/log.h>
#define LOG_TAG "glRend"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//TODO This whole program is timed by the automatic render updates. This needs to be run by the core game loop in the future.

static const float rect[] = {-1.0f, -1.0f, 0.0f, 0.0f,
                             -1.0f,  1.0f, 0.0f, 1.0f,
                             1.0f, -1.0f, 1.0f, 0.0f,
                             1.0f,  1.0f, 1.0f, 1.0f};
static const float lightColor[] = {0.75f, 0.45f, 0.75f};
static const float lightPosition[] = {0.25f, .5f, 1.35f};

void setupView();
void setupPerspective(int width, int height);

GLuint texture;
GLuint buffer;

GLuint mMVPMHandle;
GLuint aPositionHandle;
GLuint aTextureCoordinate;
GLuint uTextureHandle;


extern void init() {

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    //glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_NEVER);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glEnable(GL_DEBUG_OUTPUT);
    //glCullFace(GL_NEVER);
    glDisable(GL_CULL_FACE);

    setupView();
    setupPerspective( 16, 9);
    initShaders();

    mMVPMHandle = getMVPMHandle();
    aPositionHandle = getPositionHandle();
    aTextureCoordinate = getTexCoordHandle();
    uTextureHandle = getTexUniformHandle();

}

void setupView() {



}
void setupPerspective(int width, int height){

    float w = (float)width;
    float h = (float)height;
    float aspectRatio = w/h;
    /*
    mProjection = glm::perspective(
            glm::radians(90.0f),
            -1.0f,
            0.1f,
            10.0f
            );
    */

}
GLuint createTileIndices(int* mapValues, int mapSize){

}

GLuint create_vbo(const GLsizeiptr size, const GLvoid* data, int VBOType, const GLenum usage){
    float* temp = (float*)data;
    GLuint VBO;

        if (firstLoad) {
            LOGE("vbo first load");
            //TODO this may cause issues in the future. It may not be a thorough enough check for duplicate quads
            prevQuads = (float*)malloc(2 * sizeof(float));
            prevVBOIds = (int*)malloc(sizeof(int));

            prevQuads[0] = temp[0];
            prevQuads[1] = temp[1];
            LOGE("prvQuads before realloc: %f:",prevQuads[0]);

            VBO = loadVBO(size,data,usage);
            prevVBOIds[0] = (int)VBO;

            numOfUniqueQuads += 1;
            firstLoad = false;
            LOGE("unique quads at first load: %i", numOfUniqueQuads);
        } else {

            for(int i = 0; i < numOfUniqueQuads; i++){
                int refXIndex = i * 2;
                int refYIndex = (i * 2) + 1;

                if((prevQuads[refXIndex] == temp[0]) && (prevQuads[refYIndex] == temp[1])){
                        LOGE("prev vbo: %i, unique quads: %i", prevVBOIds[i], numOfUniqueQuads);
                        VBO =  (GLuint)prevVBOIds[i];
                        i = numOfUniqueQuads + 1;
                }else{
                    if((i + 1) == numOfUniqueQuads){

                        i += 1;

                        refXIndex = i * 2;
                        refYIndex = (i * 2) + 1;

                        prevQuads = (float*)realloc(prevQuads, ((sizeof(float)*numOfUniqueQuads * 2) + (sizeof(float)* 2)));
                        prevVBOIds = (int*)realloc(prevVBOIds, ((sizeof(int)*numOfUniqueQuads) + (sizeof(int))));

                        LOGE("prvQuads after realloc: %f:",prevQuads[0]);

                        VBO = loadVBO(size,data,usage);
                        prevQuads[refXIndex] = temp[0];
                        prevQuads[refYIndex] = temp[1];

                        prevVBOIds[i] = (int)VBO;

                        numOfUniqueQuads += 1;
                        LOGE("unique quads: %i", numOfUniqueQuads);
                        i  = numOfUniqueQuads + 3;

                    }
                }
            }
        }

   // VBO = loadVBO(size,data,usage);
    return VBO;
}
GLuint loadVBO(GLsizeiptr size,const GLvoid* data, GLenum usage){
    GLuint vbo_object;
    //assert(data != NULL);

    glGenBuffers(1, &vbo_object);

    //assert(vbo_object != 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_object);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    LOGE("vbo object %d", vbo_object);
    return vbo_object;
}



void on_surface_changed(int width, int height){
    //setupPerspective(width, height);
}
GLuint createTileIndex(int* mapValues, int mapSize){

}
void on_draw_map(void* wMatrix, renderList* r_list, int animFrame){
    glUseProgram(getShaderHandle());

    for(int t = 0; t < r_list->noOfTextures; t++){

        glActiveTexture(GL_TEXTURE0 + t);
        glBindTexture(GL_TEXTURE_2D, r_list->textures[t]);
    }
    glUniform1i(uTextureHandle, 0);

    glBindBuffer(GL_ARRAY_BUFFER, r_list->vertexAttributes[0]);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE,0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(aPositionHandle);

    glBindBuffer(GL_ARRAY_BUFFER, r_list->textureAttributes[0]);
    glEnableVertexAttribArray(aTextureCoordinate);
    glVertexAttribPointer(aTextureCoordinate, 2, GL_FLOAT, GL_FALSE, 0, (animFrame * 2 * 4 * 4));

    //for(int r = 0; r < r_list->noOfObjects; r++) {
    glUniformMatrix4fv(mMVPMHandle, 1, GL_FALSE, wMatrix);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, r_list->drawIndices[0]);
   // }
}
void on_draw_mat_map( void* wMatrix, renderList* r_list, int animFrame){

   // float* _oMatrix = (float *)(r_list->matrices[0]);

    //glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(getNormalShaderHandle());

    for(int t = 0; t < r_list->noOfTextures; t++){

        glActiveTexture(GL_TEXTURE0 + t);
        glBindTexture(GL_TEXTURE_2D, r_list->textures[t]);
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUniform3f(getNormalLightColorHandle(), lightColor[0], lightColor[1], lightColor[2]);
    glUniform3f(getNormalLightPositionHandle(), lightPosition[0], lightPosition[1], lightPosition[2]);


    /*
    //TODO these two are placeholders
    glEnableVertexAttribArray(getNormalHasAnim());
    glBindBuffer(GL_ARRAY_BUFFER,r_list->textureAttributes[1]);
    glVertexAttribPointer(getNormalHasAnim(), 1, GL_BYTE, GL_FALSE, 0, BUFFER_OFFSET(0));
     */

    glUniform1i(getNormalAnimFrame(),animFrame);

    glBindBuffer(GL_ARRAY_BUFFER, r_list->vertexAttributes[0]);
    glEnableVertexAttribArray(getNormalPositionHandle());
    glVertexAttribPointer(getNormalPositionHandle(), 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //for(int r = 0; r < r_list->noOfObjects; r++)`

        for(int r = 0; r < r_list->noOfObjects; r++) {

            glEnableVertexAttribArray(getTileMapHandle());
            glVertexAttribPointer(getTileMapHandle(), 2, GL_FLOAT, GL_FALSE, 0, r_list->storageArray[r]);

            //LOGE("omatrix value: %i",indices[2]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glEnableVertexAttribArray(getNormalHasAnim());
            //glBindBuffer(GL_ARRAY_BUFFER,r_list->textureAttributes[1]);
            glVertexAttribPointer(getNormalHasAnim(), 1, GL_FLOAT, GL_FALSE, 0, r_list->hasAnim[r]);

            glUniformMatrix4fv(getMVPNormalMatrixHandle(), 1, GL_FALSE, r_list->matrices[r]);
            //glDrawArrays(GL_TRIANGLES, 0, 64);
            glDrawElements(GL_TRIANGLES, r_list->sizeOfIndices, GL_UNSIGNED_SHORT,
                           r_list->drawIndices[0]);
        }
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void on_draw( void* wMatrix, renderList* r_list, int animFrame){

    glUseProgram(getShaderHandle());
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, r_list->textures[0]);
    glUniform1i(uTextureHandle, 0);

    glBindBuffer(GL_ARRAY_BUFFER, r_list->vertexAttributes[0]);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE,0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(aPositionHandle);

    glBindBuffer(GL_ARRAY_BUFFER, r_list->textureAttributes[0]);
    glEnableVertexAttribArray(aTextureCoordinate);
    glVertexAttribPointer(aTextureCoordinate, 2, GL_FLOAT, GL_FALSE, 0, (animFrame * 2 * 4 * 4));


    glUniformMatrix4fv(mMVPMHandle, 1, GL_FALSE, r_list->matrices[0]);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, r_list->drawIndices[0]);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Testing
    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ((gVAO*)vao)->textureId);
    glUniform1i(uTextureHandle, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(aPositionHandle, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));
    glVertexAttribPointer(aTextureCoordinate, 2, GL_FLOAT, GL_FALSE,
                          4 * sizeof(GL_FLOAT), BUFFER_OFFSET(2 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(aPositionHandle);
    glEnableVertexAttribArray(aTextureCoordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
     */
}
