package com.example.v2xapp;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import androidx.appcompat.app.AppCompatActivity;

public class ChoiceScreen extends AppCompatActivity{

    ImageButton btnInStreet;
    ImageButton btnInCar;
    ImageButton btnClose;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choice_screen);

        btnInStreet = findViewById(R.id.in_street_button);
        btnInCar    = findViewById(R.id.in_car_button);
        btnClose    = findViewById(R.id.close_button);

        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChoiceScreen.this, MainActivity.class);
                startActivity(intent);
            }
        });

        btnInStreet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChoiceScreen.this, InStreet.class);
                startActivity(intent);
            }
        });
        btnInCar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChoiceScreen.this, InCar.class);
                startActivity(intent);
            }
        });

    }

}
