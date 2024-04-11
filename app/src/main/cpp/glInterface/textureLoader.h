//
// Created by bradley on 11/5/21.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <GLES2/gl2.h>
#include "image.h"
#include "../core/utils/Common.h"

#ifdef __cplusplus
extern "C" {
#endif

GLuint loadTexture(const char *location);
GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid *pixels);

#ifdef __cplusplus
}
#endif

#endif //RENDERERD_DREAM_TEXTURELOADER_H
