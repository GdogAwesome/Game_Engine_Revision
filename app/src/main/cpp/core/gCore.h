//
// Created by bradley on 11/21/21.
//

#ifndef GCORE_H
#define GCORE_H
#define maxObjectTypes 18
#include "Entity.h"
#include <sys/time.h>

//TODO this will be removed in final build
#include <android/log.h>
#define LOG_TAG "Core"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace gdg {
    class gCore {

    private:

    protected:

    public:
        gCore();
        ~gCore();
        void tick();
        void on_change_surface(int width, int height);
        void init_core();
    };

}
#endif //RENDERERD_DREAM_GCORE_H

