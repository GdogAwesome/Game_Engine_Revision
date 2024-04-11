package com.gdogawesome.rendererddream;

import android.app.ActivityManager;
import android.content.Context;

import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import androidx.appcompat.app.AppCompatActivity;



public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        glSurfaceView = new GLSurfaceView(this);

        glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);

        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new RendererWrapper(this));
        rendererSet = true;

        setContentView(glSurfaceView);

    }
    @Override
    protected void onPause(){
        super.onPause();

        if(rendererSet){
            glSurfaceView.onPause();
        }
    }
    @Override
    protected void onResume(){
        super.onResume();
        removeSystemBars();
        if(rendererSet){
            glSurfaceView.onResume();
        }
    }

    private void removeSystemBars(){

        int uiOptions;
        if(android.os.Build.VERSION.SDK_INT >= 16) {
            uiOptions = View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                    | View.SYSTEM_UI_FLAG_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

            glSurfaceView.setSystemUiVisibility(uiOptions);
        }else{
            //TODO this doesn't quite work right but it doesn't mess up the screen touch coordinates

            //uiOptions = View.SYSTEM_UI_FLAG_FULLSCREEN;

        }


    }


}