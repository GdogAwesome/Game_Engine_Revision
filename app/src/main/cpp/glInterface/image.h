//
// Created by bradley on 11/6/21.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <GLES2/gl2.h>


#ifdef __cplusplus
extern "C"{
#endif
typedef struct {
    const int width;
    const int height;
    const int size;
    const GLenum gl_color_format;
    const void *data;
} RawImageData;

RawImageData get_raw_image_data_from_png(const void* png_data, const int png_data_size);

void release_raw_image_data(const RawImageData *data);

#ifdef __cplusplus
}
#endif
#endif //RENDERERD_DREAM_IMAGE_H
