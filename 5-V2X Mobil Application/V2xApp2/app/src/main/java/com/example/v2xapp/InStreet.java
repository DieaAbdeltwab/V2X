package com.example.v2xapp;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.IntentSender;
import android.content.pm.PackageManager;
import android.location.Location;
import android.os.Bundle;
import android.os.Looper;
import android.provider.Settings;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

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
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
public class InStreet extends AppCompatActivity {

    private static final String TAG = "InStreet";
    ImageButton btnBack;
    int LOCATION_REQUEST_CODE = 10001;

    String formattedLocationString;

    private TextView textViewLng;
    private TextView textViewLat;
    String formattedstringAndroidID;
    String oldFormattedLocation = " ";
    public static boolean warningFlag;
    DataHelper dataHelper;


    private boolean isRunning;
    private Thread backgroundThread;
    FusedLocationProviderClient fusedLocationProviderClient;

    LocationCallback locationCallback = new LocationCallback() {
        @SuppressLint("SetTextI18n")
        @Override
        public void onLocationResult(@NonNull LocationResult locationResult) {

            for(Location location: locationResult.getLocations())
            {
                LocationHelper helper1 = new LocationHelper(
                        location.getLongitude(),
                        location.getLatitude()
                );
                textViewLng.setText(" " + helper1.getLongitude());
                textViewLat.setText(" " + helper1.getLatitude());
                

                /* Get formatted Location String */
                formattedLocationString = getMyCheckedLocation(helper1.getLatitude(),helper1.getLongitude());

                /* Delete old Firebase path if it exists and is different from the new path */
                handleLocationChangeInFirebase();

                /* Publish Longitude & Latitude to Firebase path (PedestrianID) */
                FirebaseDatabase.getInstance().getReference(formattedLocationString).setValue(dataHelper);
                FirebaseDatabase.getInstance().getReference(formattedstringAndroidID).setValue(helper1).addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if(task.isSuccessful()) {
                            Toast.makeText(InStreet.this, "Location Saved", Toast.LENGTH_SHORT).show();
                        }
                        else {
                            Toast.makeText(InStreet.this, "FAILED To Save Location", Toast.LENGTH_SHORT).show();
                        }
                    }
                });

                /* Check Vehicle Warning flag -> if (true) GO TO Warning Screen <- */
                readVehicleWarning();

            }
        }
    };

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_in_street_screen);

        textViewLng = findViewById(R.id.text_longitude);
        textViewLat = findViewById(R.id.text_latitude);

        @SuppressLint("HardwareIds")
        String stringAndroidID = Settings.Secure.getString(InStreet.this.getContentResolver() , Settings.Secure.ANDROID_ID);
        formattedstringAndroidID = String.format("R9-3A-%s",stringAndroidID);

        dataHelper = new DataHelper(formattedstringAndroidID,false);

        /*------------------------------------------------------------------------------------------------*/
        /* Thread to run this screen normally when App go to the warning screen*/
        isRunning = true;

        backgroundThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (isRunning) {
                    // Perform your background task here
                    fusedLocationProviderClient = LocationServices.getFusedLocationProviderClient(InStreet.this);

                    try {
                        Thread.sleep(500); // Sleep for a while
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        backgroundThread.start();
        /*-----------------------------------------------------------------------------------------------*/

        /*------------------------------------------ Buttons --------------------------------------------*/
        btnBack = findViewById(R.id.back_button);
        btnBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(InStreet.this, ChoiceScreen.class);
                startActivity(intent);

                FirebaseDatabase.getInstance().getReference(formattedLocationString).removeValue();
                fusedLocationProviderClient.removeLocationUpdates(locationCallback);

                isRunning = false;
                backgroundThread.interrupt();
            }
        });
    }

    public void btnStartShareLocation(View view) {
        if (ContextCompat.checkSelfPermission(InStreet.this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            //getLastLocation();
            checkSettingsAndStartLocationUpdates();
        } else {
            askLocationPermission();
        }
    }

    public void btnStopShareLocation(View view)
    {
        stopLocationUpdates();
    }
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
        SettingsClient client = LocationServices.getSettingsClient(InStreet.this);

        Task<LocationSettingsResponse> locationSettingsResponseTask = client.checkLocationSettings(request);
        locationSettingsResponseTask.addOnSuccessListener(new OnSuccessListener<LocationSettingsResponse>() {
            @SuppressLint("MissingPermission")
            @Override
            public void onSuccess(LocationSettingsResponse locationSettingsResponse) {
                fusedLocationProviderClient.requestLocationUpdates(locationRequest, locationCallback, Looper.getMainLooper());
            }
        });
        locationSettingsResponseTask.addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(@NonNull Exception e) {
                if (e instanceof ResolvableApiException) {
                    ResolvableApiException apiException = (ResolvableApiException) e;
                    try {
                        apiException.startResolutionForResult(InStreet.this, LOCATION_REQUEST_CODE);
                    } catch (IntentSender.SendIntentException ex) {
                        ex.printStackTrace();
                    }
                }
            }
        });
    }

    private void stopLocationUpdates() {
        // Delete  Firebase path if stop Share Location
        FirebaseDatabase.getInstance().getReference(formattedLocationString).removeValue();
        fusedLocationProviderClient.removeLocationUpdates(locationCallback);
    }

    private void askLocationPermission() {
        if (ContextCompat.checkSelfPermission(InStreet.this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(InStreet.this, Manifest.permission.ACCESS_FINE_LOCATION)) {
                Log.d(TAG, "askLocationPermission: you should show an alert dialog...");
                ActivityCompat.requestPermissions(InStreet.this, new String[] {Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_REQUEST_CODE);
            } else {
                ActivityCompat.requestPermissions(InStreet.this, new String[] {Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_REQUEST_CODE);
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

    /*------------------------------------------ V2P functions --------------------------------------------*/
    public void handleLocationChangeInFirebase() {
        /* Check Formatted Location String equal to old Formatted Location String or not */
        if (!formattedLocationString.equals(oldFormattedLocation))
        {
            /* Delete old Firebase path if it exists and is different from the new path */
            if( (!oldFormattedLocation.equals(" ")) )
            {
                //warningIntFlag = 0;
                warningFlag = false;
                FirebaseDatabase.getInstance().getReference(formattedLocationString).removeValue();
                FirebaseDatabase.getInstance().getReference(oldFormattedLocation).removeValue();
            }
            oldFormattedLocation = formattedLocationString;
        }
    }

    public static String getMyCheckedLocation(double latitude, double longitude) {
        // Format the latitude and longitude to 5 decimal places
        @SuppressLint("DefaultLocale") String checkedAreaLatitude = String.format("%.5f", latitude);
        @SuppressLint("DefaultLocale") String checkedAreaLongitude = String.format("%.5f", longitude);

        // Convert to char arrays for manipulation
        char[] latArray = checkedAreaLatitude.toCharArray();
        char[] lonArray = checkedAreaLongitude.toCharArray();

        // Manipulate specific indices
//        latArray[2] = ',';
//        lonArray[2] = ',';
//        latArray[7] = ' ';
//        lonArray[7] = '-';
        latArray[2] = ',';
        lonArray[2] = ',';
        lonArray[7] = ' ';
        latArray[7] = '-';

        // Convert back to strings
        checkedAreaLatitude = new String(latArray);
        checkedAreaLongitude = new String(lonArray);

        // Concatenate the modified strings
//        String checkedAreaLocation = checkedAreaLongitude + checkedAreaLatitude;
        return (checkedAreaLatitude + checkedAreaLongitude);
    }

    public void readVehicleWarning() {
        /* Subscribe warning From Firebase path (formattedLocation/warning) */
        DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference(formattedLocationString);
        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                warningFlag = Boolean.TRUE.equals(snapshot.child("warning").getValue(Boolean.class));
                if(warningFlag)
                {
                    /* Go to warning screen */
                    Intent intent = new Intent(InStreet.this, WarningScreen.class);
                    startActivity(intent);
                }
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FirebaseDatabase.getInstance().getReference(formattedLocationString).removeValue();
        isRunning = false;
        backgroundThread.interrupt();
    }
    /*-----------------------------------------------------------------------------------------------------*/

}


