#include "Common.h"
//TODO this will be removed in final build
#include <android/log.h>
#define LOG_TAG "Common"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void resizeArrayF(float** array, int currentSize, int sizeDelta){
    *array = (float*)realloc(*array, currentSize + (sizeDelta * sizeof(float)));
}
void resizeArrayI(int** array, int currentSize, int sizeDelta){
    *array = (int*)realloc(*array, currentSize + (sizeDelta * sizeof(int)));
}

void resizeArrayB(bool** array, int currentSize, int sizeDelta){
    *array = (bool*)realloc(*array, currentSize + (sizeDelta * sizeof(bool)));
}

