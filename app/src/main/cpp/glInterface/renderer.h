//
// Created by brad on 9/20/21.
//

#ifndef RENDERER_H
#define RENDERER_H
#ifdef __cplusplus
extern "C"{
#endif
    extern void on_surface_created();
    extern void on_surface_changed(int width, int height);
    extern void on_draw_frame();
#ifdef __cplusplus
}
#endif
#endif //RENDERED_DREAM_RENDERER_H
