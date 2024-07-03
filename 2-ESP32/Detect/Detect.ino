#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "stdlib.h"
/************************************************************************************/
#define WIFI_SSID     "WE_G"
#define WIFI_PASSWORD "Diea@Abdeltwab_G" 
#define API_KEY       "AIzaSyD2PnFZ3kYQGHKO49Bzmjy6r-KQXioaYZY"
#define DATABASE_URL  "https://gp-1-a8657-default-rtdb.firebaseio.com/" 
FirebaseData  fbdo;
FirebaseAuth  auth;
FirebaseConfig config;
bool signupOK= false ;

/************************************************************************************/
String StringAmbulanceStationID = "W4-4-001" ;
#define BUZZERPIN                  15
#define BUTTON_PIN                 23 

/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

/**************************************************************************************************************************/
/************************************************** Firebase Help Functions ***********************************************/
/**************************************************************************************************************************/
void voidFirebaseSetBool ( String Copy_StringFirebasePass , bool Copy_BoolData)
{
  Serial.print(Copy_StringFirebasePass);
  Serial.print("--->> ");
  if (Firebase.RTDB.setBool(&fbdo, Copy_StringFirebasePass , Copy_BoolData ))
  {
    Serial.println((bool)Copy_BoolData);
  }
  else 
  {
    Serial.println("ERROR!");
  }
}
bool boolFirebaseGetBool ( String Copy_StringFirebasePass )
{
  bool boolReadValue = false  ;
  Serial.print(Copy_StringFirebasePass);
  Serial.print(" <<---");
  if (Firebase.RTDB.getBool(&fbdo,Copy_StringFirebasePass))
  {
    boolReadValue = fbdo.boolData();
    Serial.println((bool)boolReadValue);
  }
  else 
  {
    Serial.println("ERROR!");
  }
  return boolReadValue ; 
}
void voidFirebaseSetString ( String Copy_StringFirebasePass , String Copy_StringData)
{
  Serial.print(Copy_StringFirebasePass);
  Serial.print("--->> ");
  if (Firebase.RTDB.setString(&fbdo, Copy_StringFirebasePass , Copy_StringData ))
  {
    Serial.println((String)Copy_StringData);
  }
  else 
  {
    Serial.println("ERROR!");
  }
}
String stringFirebaseGetString ( String Copy_StringFirebasePass )
{
  String stringReadValue = "ERROR!" ;
  Serial.print(Copy_StringFirebasePass);
  Serial.print(" <<---");
  if (Firebase.RTDB.getString(&fbdo,Copy_StringFirebasePass))
  {
    stringReadValue = fbdo.stringData();
    Serial.println((String)stringReadValue);
  }
  else 
  {
    Serial.println("ERROR!");
  }
  return stringReadValue ; 
}
void voidFirebaseSetInt ( String Copy_StringFirebasePass , int Copy_intData)
{
  Serial.print(Copy_StringFirebasePass);
  Serial.print("--->> ");
  if (Firebase.RTDB.setInt(&fbdo, Copy_StringFirebasePass , Copy_intData ))
  {
    Serial.println((int)Copy_intData);
  }
  else 
  {
    Serial.println("ERROR!");
  }
}
int intFirebaseGetInt ( String Copy_StringFirebasePass )
{
  int intReadValue = 0 ;
  Serial.print(Copy_StringFirebasePass);
  Serial.print(" <<---");
  if (Firebase.RTDB.getInt(&fbdo,Copy_StringFirebasePass))
  {
    intReadValue = fbdo.intData();
    Serial.println((int)intReadValue);
  }
  else 
  {
    Serial.println("ERROR!");
  }
  return intReadValue ; 
}
void voidFirebaseSetDouble ( String Copy_StringFirebasePass , double Copy_doubleData)
{
  Serial.print(Copy_StringFirebasePass);
  Serial.print("--->> ");
  if (Firebase.RTDB.setDouble(&fbdo, Copy_StringFirebasePass , Copy_doubleData ))
  {
    Serial.println((double)Copy_doubleData,6);
  }
  else 
  {
    Serial.println("ERROR!");
  }
}
double doubleFirebaseGetDouble ( String Copy_StringFirebasePass )
{
  double doubleReadValue = 0 ;
  Serial.print(Copy_StringFirebasePass);
  Serial.print(" <<---");
  if (Firebase.RTDB.getDouble(&fbdo,Copy_StringFirebasePass))
  {
    doubleReadValue = fbdo.doubleData();
    Serial.println((double)doubleReadValue,6);
  }
  else 
  {
    Serial.println("ERROR!");
  }
  return doubleReadValue ; 
}
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
String StringDetectTrafficID = "0";
void DetectAccident ( void )
{
  StringDetectTrafficID  = stringFirebaseGetString(StringAmbulanceStationID +"/DetectTrafficID");
  if ( StringDetectTrafficID == "0" )
  {
    digitalWrite( BUZZERPIN , LOW );
  }
  else 
  {
    digitalWrite( BUZZERPIN , HIGH );
    double doubleAccidentLatitude = doubleFirebaseGetDouble(StringDetectTrafficID+"/latitude"); 
    double doubleAccidentLongitude = doubleFirebaseGetDouble(StringDetectTrafficID+"/longitude"); 
    // Display ON LCD Her 
  }
}  

/**************************************************************************************************************************/
/**************************************************************************************************************************/

void setup() {
  pinMode ( BUZZERPIN , OUTPUT );
  pinMode (BUTTON_PIN  , INPUT_PULLUP);
    // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
}
void loop()
{  
  delay(500);
  DetectAccident();
  int ButtonState = digitalRead(BUTTON_PIN);
  if ( ButtonState == 0 && StringDetectTrafficID != "0" )
  {
    voidFirebaseSetString(StringAmbulanceStationID +"/DetectTrafficID" , "0" );
    digitalWrite( BUZZERPIN , LOW );
  }  
}
