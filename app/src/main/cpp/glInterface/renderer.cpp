//
// Created by brad on 9/20/21.
//
#include "renderer.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../deps/glm-master/glm/gtc/matrix_transform.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <android/native_window.h>
#include <android/native_window_jni.h>


void setupView();
void setupPerspective(int width, int height);

void on_surface_created() {

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    setupView();
    setupPerspective( 16, 9);
}


glm::mat4 mViewMatrix;
glm::mat4 mProjection;
void setupView() {

    const float eyeX = 0.0f;
    const float eyeY = 0.0f;
    const float eyeZ = -0.5f;

    const float lookX = 0.0f;
    const float lookY = 0.0f;
    const float lookZ = -1.0f;

    const float upX = 0.0f;
    const float upY = 1.0f;
    const float upZ = 0.0f;


    mViewMatrix = glm::lookAt(
            glm::vec3(eyeX, eyeY, eyeZ),
            glm::vec3(lookX, lookY, lookZ),
            glm::vec3(upX, upY, upZ)
            );

}
void setupPerspective(int width, int height){

    float w = (float)width;
    float h = (float)height;
    float aspectRatio = w/h;
    /*mProjection = glm::perspective(
            glm::radians(90.0f),
            -1.0f,
            0.1f,
            10.0f
            );
    */
    mProjection = glm::frustum( -1.0f, 1.0f,-1.0f, 1.0f, 0.1f, 10.0f);
}


void on_surface_changed(int width, int height){
    setupPerspective(width, height);
}

void on_draw_frame(){
}
