package com.example.v2xapp;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Build;
import android.os.Bundle;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Timer;
import java.util.TimerTask;

public class WarningScreen extends AppCompatActivity {
    ImageButton btnGoBack;
    Timer timer;
    Vibrator vibrator;
    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_warning_screen);

        MediaPlayer mp = MediaPlayer.create(WarningScreen.this,R.raw.warning_voice);

        timer = new Timer();
        vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);

        if(Build.VERSION.SDK_INT >= 26) {
            vibrator.vibrate(VibrationEffect.createOneShot(10000, VibrationEffect.DEFAULT_AMPLITUDE));
            mp.start();
        }
        else {
            vibrator.vibrate(10000);
            mp.start();
        }
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                //InStreet.warningFlag = false;
                //InStreet.warningIntFlag = 0;
                Intent intent = new Intent(WarningScreen.this, InStreet.class);
                startActivity(intent);
                mp.pause();
                finish();
            }
        }, 10000);

    }

}
