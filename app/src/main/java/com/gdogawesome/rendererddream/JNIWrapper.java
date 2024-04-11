package com.gdogawesome.rendererddream;


import android.content.Context;
import android.view.SurfaceView;
import android.app.Activity;
import android.content.res.AssetManager;
import android.content.res.AssetFileDescriptor;



public class JNIWrapper {

    static{
        System.loadLibrary("rendererddream");
    }
    AssetManager assetManager;

    Context context;
    public JNIWrapper(Context context){
        this.context = context;
    }
    public void onCreate(){
        assetManager = context.getResources().getAssets();

        on_surface_created(assetManager);
    }
    public native void on_surface_created(AssetManager assetManager);
    public native void on_surface_changed(int width, int height);
    public native void on_draw_frame();

}
