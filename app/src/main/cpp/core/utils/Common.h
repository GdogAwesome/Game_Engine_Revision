//
// Created by bradley on 1/2/22.
//

#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

//TODO this is temporary. I will define system specifics later
#define OTHER

#ifdef OTHER
#define TEXTURE_SIZE 2048
#else
#define TEXTURE_SIZE 1024
#endif

//TODO I will later convert this to 4 verts per quad. also ???
#define VERTS_PER_QUADRILATERAL 4
#define TEXTURE_VBO 0
#define VERTEX_VBO 1

//some of my own defines


//Some select, aliased opengl defines
#define AGL_ARRAY_BUFFER                   0x8892
#define AGL_ELEMENT_ARRAY_BUFFER           0x8893
#define AGL_ARRAY_BUFFER_BINDING           0x8894

#define AGL_BYTE                           0x1400
#define AGL_UNSIGNED_BYTE                  0x1401
#define AGL_SHORT                          0x1402
#define AGL_UNSIGNED_SHORT                 0x1403
#define AGL_INT                            0x1404
#define AGL_UNSIGNED_INT                   0x1405
#define AGL_FLOAT                          0x1406

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint;

    static const uint textureSize = TEXTURE_SIZE;
    static const uint VERTS_PER_QUAD = VERTS_PER_QUADRILATERAL;


void resizeArrayF(float** array,int currentSize, int sizeDelta);
void resizeArrayI(int** array, int currentSize, int sizeDelta);
void resizeArrayB(bool** array, int currentSize, int sizeDelta);


typedef struct {
    const uint width;
    const uint height;
    const uint size;
    const uint gl_color_format;
    const void *data;
} Texture;

typedef struct{
    bool isMap;
    int noOfObjects;
    int noOfTextures;
    int* renderOrder;
    float** storageArray;
    uint* textures;
    uint* typesOfTextures;
    int noOfVertexAttributes;
    int leadingTileMap;
    void* swapPointer;
    uint* typeOfVertexAttribute;
    uint* vertexAttributes;
    int noOfTextureAttributes;
    uint* textureAttributes;
    int sizeOfIndices;
    int indicesStride;
    unsigned short** drawIndices;
    float** hasAnim;
    int noOfMatrices;
    float** matrices;;
}renderList;

#ifdef __cplusplus
}
#endif



#endif //_COMMON_H
