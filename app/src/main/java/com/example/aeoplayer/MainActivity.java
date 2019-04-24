package com.example.aeoplayer;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    public static final String TEST_STREAM_URL = "rtmp://live.chosun.gscdn.com/live/tvchosun1.stream";
    SurfaceView mSurfaceView;
    private AeoPlayer aeoPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mSurfaceView = findViewById(R.id.surfaceView);
        aeoPlayer = new AeoPlayer();
        aeoPlayer.setSurfaceView(mSurfaceView);
        aeoPlayer.setDataSource(TEST_STREAM_URL);

        aeoPlayer.setOnPrepareListener(new AeoPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "Ready!", Toast.LENGTH_LONG).show();
                    }
                });
                aeoPlayer.start();
            }
        });
    }

    public void start(View view) {
        aeoPlayer.prepare();
    }

    public void stop(View view) {
        aeoPlayer.stop();
    }
}
