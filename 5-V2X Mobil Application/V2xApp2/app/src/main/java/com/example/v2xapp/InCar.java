package com.example.v2xapp;


import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.IntentSender;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.Location;
import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.ResolvableApiException;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.Granularity;
import com.google.android.gms.location.LocationCallback;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationResult;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.LocationSettingsRequest;
import com.google.android.gms.location.LocationSettingsResponse;
import com.google.android.gms.location.Priority;
import com.google.android.gms.location.SettingsClient;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.FirebaseDatabase;

import java.text.DateFormat;
import java.util.Calendar;
import java.util.Date;

public class InCar extends AppCompatActivity implements SensorEventListener {
    private static final String TAG = "MainActivity";
    int LOCATION_REQUEST_CODE = 10001;

    ImageButton btnBack;
    private TextView textView;
    private TextView textViewLng;
    private TextView textViewLat;
    private TextView textViewDg;
    private TextView textViewMoney;
    private TextView textViewDate;
    private EditText editText;


    public static final String SHARED_PREFS = "sharedPrefs";
    public static final String TEXT = "text";
    private String text;
    public String Car_VIN;
    int compassDegree;
    int Money = 100;
    String DateTimeFormat;
    SensorManager sensorManager;


    FusedLocationProviderClient fusedLocationProviderClient;
    //LocationRequest locationRequest = LocationRequest.create();
    LocationCallback locationCallback = new LocationCallback() {
        @SuppressLint("SetTextI18n")
        @Override
        public void onLocationResult(@NonNull LocationResult locationResult) {

            for (Location location : locationResult.getLocations()) {

                LocationHelper helper = new LocationHelper(
                        location.getLongitude(),
                        location.getLatitude(),
                        Money,
                        compassDegree,
                        DateTimeFormat
                );

                textViewLng.setText(" " + helper.getLongitude());
                textViewLat.setText(" " + helper.getLatitude());
                textViewMoney.setText(" " + Money);

                /* Publish Longitude & Latitude to Firebase path (CarVIN) */
                FirebaseDatabase.getInstance().getReference(Car_VIN)
                        .setValue(helper).addOnCompleteListener(new OnCompleteListener<Void>() {
                            @Override
                            public void onComplete(@NonNull Task<Void> task) {
                                if (task.isSuccessful()) {
                                    Toast.makeText(InCar.this, "Location Saved", Toast.LENGTH_SHORT).show();
                                } else {
                                    Toast.makeText(InCar.this, "FAILED To Save Location", Toast.LENGTH_SHORT).show();
                                }
                            }
                        });

            }
        }
    };

    @SuppressLint({"SetTextI18n", "MissingInflatedId"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_in_car_screenn);

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);

        /*----------------------------------- Define view variable -------------------------------------*/
        textView = (TextView) findViewById(R.id.textview);
        textViewLng = (TextView) findViewById(R.id.LnggTextView);
        textViewLat = (TextView) findViewById(R.id.LattTextView);
        textViewDg = (TextView) findViewById(R.id.degreeTextView);
        textViewMoney = (TextView) findViewById(R.id.moneyTextView);
        textViewDate = (TextView) findViewById(R.id.dateTextView);
        editText = (EditText) findViewById(R.id.edittext);
        btnBack = findViewById(R.id.back_button);
        /*-----------------------------------------------------------------------------------------------*/

        /*------------------------------------------ Buttons --------------------------------------------*/
        btnBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(InCar.this, ChoiceScreen.class);
                startActivity(intent);
                stopLocationUpdates();
            }
        });

        loadData();
        updateViews();
        getDateAndTime();

        fusedLocationProviderClient = LocationServices.getFusedLocationProviderClient(this);
    }


    public void btnStart(View view) {
        Car_VIN = editText.getText().toString();
        textView.setText(Car_VIN);
        saveData();
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            if (!Car_VIN.isEmpty())
                checkSettingsAndStartLocationUpdates();
            else
                Toast.makeText(InCar.this, "Please Enter Your Car VIN!", Toast.LENGTH_LONG).show();
        } else {
            askLocationPermission();
        }
    }

    public void btnStop(View view) { stopLocationUpdates(); }
    /*-----------------------------------------------------------------------------------------------------*/

    /*--------------------------------------- GPS functions -----------------------------------------------*/
    private void checkSettingsAndStartLocationUpdates() {
        LocationRequest locationRequest = new LocationRequest.Builder(500)
                .setGranularity(Granularity.GRANULARITY_FINE)
                .setPriority(Priority.PRIORITY_HIGH_ACCURACY)
                .setMinUpdateDistanceMeters(1)
                .build();

        LocationSettingsRequest request = new LocationSettingsRequest.Builder()
                .addLocationRequest(locationRequest).build();
        SettingsClient client = LocationServices.getSettingsClient(this);

        Task<LocationSettingsResponse> locationSettingsResponseTask = client.checkLocationSettings(request);
        locationSettingsResponseTask.addOnSuccessListener(new OnSuccessListener<LocationSettingsResponse>() {
            @SuppressLint("MissingPermission")
            @Override
            public void onSuccess(LocationSettingsResponse locationSettingsResponse) {
                //Settings of device are satisfied and we can start location updates
                fusedLocationProviderClient.requestLocationUpdates(locationRequest, locationCallback, Looper.getMainLooper());
            }
        });
        locationSettingsResponseTask.addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(@NonNull Exception e) {
                if (e instanceof ResolvableApiException) {
                    ResolvableApiException apiException = (ResolvableApiException) e;
                    try {
                        apiException.startResolutionForResult(InCar.this, 1001);
                    } catch (IntentSender.SendIntentException ex) {
                        ex.printStackTrace();
                    }
                }
            }
        });
    }

    private void stopLocationUpdates() {
        fusedLocationProviderClient.removeLocationUpdates(locationCallback);
    }

    private void askLocationPermission() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.ACCESS_FINE_LOCATION)) {
                Log.d(TAG, "askLocationPermission: you should show an alert dialog...");
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_REQUEST_CODE);
            } else {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_REQUEST_CODE);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == LOCATION_REQUEST_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Permission granted
                checkSettingsAndStartLocationUpdates();
            }
        }
    }
    /*-----------------------------------------------------------------------------------------------------*/

    /*---------------------------------------- VIN Show Part ----------------------------------------------*/
    public void saveData() {
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        editor.putString(TEXT, textView.getText().toString());

        editor.apply();
        //Toast.makeText(this, "Data saved", Toast.LENGTH_SHORT).show();
    }

    public void loadData() {
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        text = sharedPreferences.getString(TEXT, "");
    }

    public void updateViews() {
        textView.setText(text);
    }
    /*-----------------------------------------------------------------------------------------------------*/

    /*---------------------------------------- compass padding --------------------------------------------*/
    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION), SensorManager.SENSOR_DELAY_UI);
    }

    @Override
    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(this);
    }

    @SuppressLint("SetTextI18n")
    @Override
    public void onSensorChanged(SensorEvent event) {
        /* For Compass Degree Sensor */
        compassDegree = Math.round(event.values[0]);
        textViewDg.setText(compassDegree + "°");
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
    /*-----------------------------------------------------------------------------------------------------*/

    /*------------------------------------------ Date & Time ----------------------------------------------*/
    public void getDateAndTime() {
        Thread thread = new Thread() {
            /** @noinspection BusyWait*/
            @Override
            public void run() {
                try {
                    while (!isInterrupted()) {
                        Thread.sleep(1000);
                        runOnUiThread(new Runnable() {
                            @SuppressLint("SetTextI18n")
                            @Override
                            public void run() {
                                Date calendar = Calendar.getInstance().getTime();
                                String dateFormat = DateFormat.getDateInstance().format(calendar);
                                String timeFormat = DateFormat.getTimeInstance().format(calendar);
                                DateTimeFormat = String.format("%s - %s", dateFormat, timeFormat);
                                textViewDate.setText(DateTimeFormat);
                            }
                        });
                    }
                } catch (Exception e) {
                    textViewDate.setText(R.string.app_name);
                }
            }
        };
        thread.start();
    }
    /*-----------------------------------------------------------------------------------------------------*/


}