package com.example.aeoplayer;

import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class AeoPlayer {

    static {
        System.loadLibrary("native-lib");
    }

    private String dataSource;

    private SurfaceView surfaceView;
    private SurfaceHolder holder;
    private SurfaceHolderCallback mSurfaceHolderCallback = new SurfaceHolderCallback();
    private OnPrepareListener onPrepareListener;

    public void setSurfaceView(SurfaceView surfaceView) {
        this.surfaceView = surfaceView;
    }

    public void setDataSource(String dataSource) {
        this.dataSource = dataSource;
    }


    public void prepare() {
        holder = surfaceView.getHolder();
        holder.addCallback(mSurfaceHolderCallback);
        native_prepare(dataSource);
    }

    public void start() {
        nativeStart();
    }

    public void stop() {

    }

    public void release() {
        holder.removeCallback(mSurfaceHolderCallback);
    }


    public void onError(int errorCode) {

    }

    public void onPrepare() {
        if (onPrepareListener != null) {
            onPrepareListener.onPrepare();
        }
    }

    public void setOnPrepareListener(OnPrepareListener listener) {
        onPrepareListener = listener;
    }

    public interface OnPrepareListener {
        void onPrepare();
    }

    public class SurfaceHolderCallback implements SurfaceHolder.Callback {

        @Override
        public void surfaceCreated(SurfaceHolder holder) {

        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {

        }
    }

    native void native_prepare(String dataSource);

    native void nativeStart();

}
