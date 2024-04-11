//
// Created by bradley on 11/5/21.
//

#include "textureLoader.h"
#include <stdio.h>
#include <malloc.h>

//TODO more non-dynamic includes
#include "../android/androidLoader.h"
#include <android/log.h>

#define LOG_TAG "texture loader jni"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

const unsigned int maxTextures = 18;
static unsigned int* textures[maxTextures] = {0};

GLuint loadTexture(const char* location){
    unsigned char* data;
    size_t size = 0;

    LOGE("test in texture Loader: %s", location);

    open_image(location,&data,&size);
    const RawImageData raw_data = get_raw_image_data_from_png( data, (const int)size);
    GLuint texture = load_texture(raw_data.width, raw_data.height, raw_data.gl_color_format, raw_data.data);
    LOGE("texture size: %i",(const int)raw_data.size);

    Texture* tPt;

    int _width = raw_data.width;
    int _height = raw_data.height;
    int _size = raw_data.size;
    unsigned int _color_format = raw_data.gl_color_format;
    const void* _data = raw_data.data;
    //tPt = new Texture{_width, _height, _size, _color_format, _data};

    release_raw_image_data(&raw_data);
    free(data);
    return texture;
}

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels){
    GLuint texture_id;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture_id;

}