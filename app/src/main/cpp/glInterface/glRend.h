//
// Created by brad on 9/20/21.
//

#ifndef GLREND_H
#define GLREND_H

#define BUFFER_OFFSET(i) ((void*)(i))
#include <GLES2/gl2.h>
#include "textureLoader.h"

//TODO Loader is only included here for the VAO struct. I may move it to a more logical location
#include "../core/utils/Loader.h"

//#include "../deps/glm-master/glm/gtc/matrix_transform.hpp"

#ifdef __cplusplus
extern "C" {
#endif

//TODO this will probably move to a separate gl-Loader utility
static float* prevQuads;

static int* prevVBOIds;
static bool firstLoad = true;
static int numOfUniqueQuads = 0;
static uint lastBoundTexture = 8000;
static const int vertsPerQuad = VERTS_PER_QUAD;

void init();
extern void on_surface_changed(int width, int height);
extern void on_draw(void* wMatrix, renderList* r_list, int animFrame);
void on_draw_map(void* wMatrix, renderList* r_list, int animFrame);
extern void on_draw_mat_map(void* wMatrix, renderList* r_list, int animFrame);
GLuint create_vbo(const GLsizeiptr size, const GLvoid *data, int VBOType, const GLenum usage);
GLuint loadVBO(GLsizeiptr size, const GLvoid *data, GLenum usage);
GLuint createTileIndex(int* mapValues, int mapSize);


#ifdef __cplusplus
}
#endif

#endif //RENDERED_DREAM_RENDERER_H
