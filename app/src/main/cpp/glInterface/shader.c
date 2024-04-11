//
// Created by bradley on 10/7/21.
//


#include <GLES2/gl2.h>
#include <android/log.h>
#include "../android/androidLoader.h"

#include <stdio.h>
#include <stdlib.h>

//#include "../deps/glm-master/glm/gtc/matrix_transform.hpp"

#include "shader.h"
#define LOG_TAG "shader"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

GLuint mMVPMatrixHandle;
GLuint mMVMatrixHandle;
GLuint mPositionHandle;
GLuint mTextureUniformHandle;
GLuint mTextureCoordinateHandle;

GLuint uNormalTextureUniformHandle;
GLuint mMVPNormalMatrixHandle;
GLuint mMVNormalMatrixHandle;
GLuint mNormalPositionHandle;
GLuint aNormalTextureCoordinateHandle;
GLuint uNormalTextureMapHandle;
GLuint uLightPosHandle;
GLuint mNormalPerVertexHandle;
GLuint aTileMap;
GLuint uNormalAnimFrame;
GLuint aNormalHasAnim;
GLuint uNormalLightColorHandle;
GLuint vertexShaderHandle;
GLuint fragmentShaderHandle;
GLuint normalVertexShaderHandle;
GLuint normalFragmentShaderHandle;
GLuint mPerVertexProgramHandle;





GLuint createAndLinkProgram(GLuint vHandle, GLuint fHandle,const char* attributes, size_t length);

GLuint compileShader(GLenum type, const char *source,const GLint size){
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar **)&source, &size);
    glCompileShader(shader);

    int  success = 0;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOGE("/n shader failed: &s", infoLog);
    }

    return shader;
}
void initShaders(){

    setupNormalShader();
    setupRegularShader();
    //TODO this will not remain static
    //glUseProgram(mPerVertexProgramHandle);

}
GLuint createAndLinkProgram(GLuint vHandle, GLuint fHandle, const char* attributes, size_t length){

    GLuint programHandle = glCreateProgram();
    if(programHandle != 0){

        glAttachShader(programHandle, vHandle);
        glAttachShader(programHandle, fHandle);

        if(attributes != NULL){
            int s = length;
            for(int i = 0; i < s; i++){
                glBindAttribLocation(programHandle, i, attributes);
            }
        }
        glLinkProgram(programHandle);

    }
    return programHandle;
}

void setupNormalShader(){

    const char* vS = "glsl/v_shader_map.txt";
    const char* fS = "glsl/f_shader_map.txt";

    char* vShaderText;
    char* fShaderText;

    size_t size_v;
    size_t size_f;
    android_fopen(vS ,&vShaderText , &size_v , 0);
    android_fopen(fS, &fShaderText , &size_f , 0);


    normalVertexShaderHandle = compileShader(GL_VERTEX_SHADER, vShaderText, (GLint)size_v);
    normalFragmentShaderHandle = compileShader(GL_FRAGMENT_SHADER, fShaderText, (GLint)size_f);

    free(vShaderText);
    free(fShaderText);


    char attributes[3][16] = {"a_Position","a_TileMap","a_HasAnim" };
    mNormalPerVertexHandle = createAndLinkProgram(normalVertexShaderHandle, normalFragmentShaderHandle, *attributes , sizeof(attributes[0])/ sizeof(attributes[0][0]));
    LOGE("shader successfully linked");

    //char* attributes = {"a_Position", "a_TexCoordinate", "a_HasAnim", "a_TileMap" };
    //mNormalPerVertexHandle = createAndLinkProgram(normalFragmentShaderHandle, normalVertexShaderHandle, attributes, sizeof(attributes)/sizeof(attributes[0]));

    //mMVNormalMatrixHandle = glGetUniformLocation(mNormalPerVertexHandle,"u_MVMatrix");
    mMVPNormalMatrixHandle = glGetUniformLocation(mNormalPerVertexHandle,"u_MVPMatrix");
    mNormalPositionHandle = glGetAttribLocation(mNormalPerVertexHandle,"a_Position");
    LOGE("before Error?");

    uLightPosHandle = glGetUniformLocation(mNormalPerVertexHandle, "u_LightPos");
    uNormalAnimFrame = glGetUniformLocation(mNormalPerVertexHandle, "u_AnimFrame");
    aNormalHasAnim = glGetAttribLocation(mNormalPerVertexHandle, "a_HasAnim");
    aTileMap = glGetAttribLocation(mNormalPerVertexHandle, "a_TileMap");

    uNormalLightColorHandle = glGetUniformLocation(mNormalPerVertexHandle, "u_lightColor");

    //aNormalTextureCoordinateHandle = glGetAttribLocation(mNormalPerVertexHandle, "a_TexCoordinate");


    uNormalTextureUniformHandle = glGetUniformLocation(mNormalPerVertexHandle, "u_Texture");
    uNormalTextureMapHandle = glGetUniformLocation(mNormalPerVertexHandle, "u_NormalMap");

    glUseProgram(mNormalPerVertexHandle);

    glUniform1i(uNormalTextureUniformHandle, 0);
    glUniform1i(uNormalTextureMapHandle, 1);

    LOGE("shader success final");

}

void setupRegularShader(){
    const char* vS = "glsl/v_shader.txt";
    const char* fS = "glsl/f_shader.txt";

    char* fShaderText;
    char* vShaderText;
    size_t size_v;
    size_t size_f;

    android_fopen(vS ,&vShaderText , &size_v , 0);
    android_fopen(fS, &fShaderText , &size_f , 0);

    vertexShaderHandle = compileShader(GL_VERTEX_SHADER, (const char*)vShaderText, (GLint)size_v);
    fragmentShaderHandle = compileShader(GL_FRAGMENT_SHADER, (const char*)fShaderText, (GLint)size_f);

    free(vShaderText);
    free(fShaderText);

    char attributes[2][16] = {"a_Position", "a_TexCoordinate"};
    mPerVertexProgramHandle = createAndLinkProgram(vertexShaderHandle, fragmentShaderHandle, *attributes , sizeof(attributes[0])/ sizeof(attributes[0][0]));

    mMVPMatrixHandle = glGetUniformLocation(mPerVertexProgramHandle,"u_MVPMatrix");
    mPositionHandle = glGetAttribLocation(mPerVertexProgramHandle,"a_Position");
    mTextureCoordinateHandle = glGetAttribLocation(mPerVertexProgramHandle, "a_TexCoordinate");
    mTextureUniformHandle = glGetUniformLocation(mPerVertexProgramHandle, "u_Texture");
}

GLuint getShaderHandle(){
    return mPerVertexProgramHandle;
}
GLuint getNormalShaderHandle(){
    return mNormalPerVertexHandle;
}
GLuint getMVMHandle(){
    return mMVMatrixHandle;
}
GLuint getMVPMHandle(){
    return mMVPMatrixHandle;
}
GLuint getPositionHandle(){
    return mPositionHandle;
}

GLuint getTexCoordHandle(){
    return mTextureCoordinateHandle;
}
GLuint getTexUniformHandle(){
    return mTextureUniformHandle;
}
GLuint getMVNormalMatrixHandle(){
    return mMVMatrixHandle;
}
GLuint getMVPNormalMatrixHandle(){
    return mMVPNormalMatrixHandle;
}
GLuint getNormalPositionHandle(){
    return mNormalPositionHandle;
}
GLuint getNormalLightPositionHandle(){
    return uLightPosHandle;
}
GLuint getNormalAnimFrame(){
    return uNormalAnimFrame;
}
GLuint getNormalHasAnim(){
    return aNormalHasAnim;
}
GLuint getTileMapHandle(){
    return aTileMap;
}
GLuint getNormalLightColorHandle(){
    return uNormalLightColorHandle;
}
GLuint getNormalTextureCoordinatHandle(){
    return aNormalTextureCoordinateHandle;
}
GLuint getNormalTextureUniformHandle(){
    return uNormalTextureUniformHandle;
}
GLuint getNormalTextureMapHandle(){
    return uNormalTextureMapHandle;
}
