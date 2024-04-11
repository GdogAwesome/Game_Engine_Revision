package com.gdogawesome.rendererddream;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.io.File;
import java.nio.file.Path;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


public class RendererWrapper implements GLSurfaceView.Renderer {

    private final Context context;
    private JNIWrapper jniW;

    public RendererWrapper(Context context) {
        this.context = context;

        //TODO test android information

        try {
            ApplicationInfo ainfo = this.context.getPackageManager().getApplicationInfo(
                    "com.gdogawesome.rendererddream",
                    PackageManager.GET_SHARED_LIBRARY_FILES
            );
            Log.e("native library dir: ", ainfo.nativeLibraryDir);
        }catch(Exception e){

        }


        jniW = new JNIWrapper(this.context);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config){
        gl.glClearColor( 0.0f, 0.0f, 1.0f, 0.0f);


        jniW.onCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height){
        jniW.on_surface_changed(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl){
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
        jniW.on_draw_frame();
    }
}