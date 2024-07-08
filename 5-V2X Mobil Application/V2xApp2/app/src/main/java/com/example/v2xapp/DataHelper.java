package com.example.v2xapp;

public class DataHelper {

    private String ID;
    private boolean Warning;

    public DataHelper(String ID, boolean warning) {
        this.ID = ID;
        Warning = warning;
    }

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public boolean isWarning() {
        return Warning;
    }

    public void setWarning(boolean warning) {
        Warning = warning;
    }
}
