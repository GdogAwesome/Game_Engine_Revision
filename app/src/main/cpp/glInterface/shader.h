//
// Created by bradley on 10/7/21.
//

#ifndef SHADER_H
#define SHADER_H

#ifdef __cplusplus
extern "C"
#endif

void setupRegularShader();
void setupNormalShader();
void initShaders();

GLuint getShaderHandle();
GLuint getNormalShaderHandle();
GLuint getMVMHandle();
GLuint getMVPMHandle();
GLuint getPositionHandle();
GLuint getTexCoordHandle();
GLuint getTexUniformHandle();
GLuint getMapTileHandle();
GLuint getMVNormalMatrixHandle();
GLuint getMVPNormalMatrixHandle();
GLuint getNormalPositionHandle();
GLuint getNormalLightPositionHandle();
GLuint getNormalAnimFrame();
GLuint getNormalHasAnim();
GLuint getTileMapHandle();
GLuint getNormalLightColorHandle();
GLuint getNormalTextureCoordinatHandle();
GLuint getNormalTextureUniformHandle();
GLuint getNormalTextureMapHandle();
GLuint getNormalTextureSampler();
GLuint getNormalTextureMapSampler();






#ifdef __cplusplus
extern "C"
#endif

#endif //RENDERERD_DREAM_SHADER_H