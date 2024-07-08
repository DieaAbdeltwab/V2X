package com.example.v2xapp;

public class LocationHelper {
    private double Longitude;
    private double Latitude;
    private int Money;
    private int compassDegree;
    private String DateAndTime;

    public LocationHelper(double longitude, double latitude) {
        Longitude = longitude;
        Latitude = latitude;
    }

    public LocationHelper(double longitude, double latitude, int money, int compassDegree, String dateAndTime) {
        Longitude = longitude;
        Latitude = latitude;
        Money = money;
        this.compassDegree = compassDegree;
        DateAndTime = dateAndTime;
    }

    public double getLongitude() {
        return Longitude;
    }

    public void setLongitude(double longitude) {
        Longitude = longitude;
    }

    public double getLatitude() {
        return Latitude;
    }

    public void setLatitude(double latitude) {
        Latitude = latitude;
    }

    public float getMoney() { return Money; }

    public void setSpeed(int money) { Money = money; }

    public int getCompassDegree() {
        return compassDegree;
    }

    public void setCompassDegree(int compassDegree) {
        this.compassDegree = compassDegree;
    }

    public String getDateAndTime() {
        return DateAndTime;
    }

    public void setDateAndTime(String dateAndTime) {
        DateAndTime = dateAndTime;
    }
}
