#include <ESP8266WiFi.h>
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
unsigned long sendDataPrevMillis = 0 ;
/************************************************************************************/
String StringMyID = "W3-3-001";
/*------------------------------------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/
#define V2I_ID_TRAFFIC_RED                  0xB4
#define V2I_ID_TRAFFIC_YELLOW               0xB5
#define V2I_ID_TRAFFIC_GREAN                0xB6
/*------------------------------------------------*/
#define V2I_ID_SPECIAL_VEHICLE_WARNING      0xC4
/*------------------------------------------------*/
#define PIN_TRAFFIC_RED                     12
#define PIN_TRAFFIC_YELLOW                  13
#define PIN_TRAFFIC_GREAN                   15
/**************************************************************************************************************************/
/************************************************** Firebase Help Functions ***********************************************/
/**************************************************************************************************************************/
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
String stringFirebaseGetstring ( String Copy_StringFirebasePass )
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
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

void setup() {

  pinMode(PIN_TRAFFIC_RED    , OUTPUT );
  pinMode(PIN_TRAFFIC_YELLOW , OUTPUT );
  pinMode(PIN_TRAFFIC_GREAN  , OUTPUT );

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
  for ( int intCounter = 0 ; intCounter<= 10 ; intCounter++ )
  {
    voidFirebaseSetInt( StringMyID + "/Status" , V2I_ID_TRAFFIC_RED );
    digitalWrite(PIN_TRAFFIC_RED    , HIGH );
    digitalWrite(PIN_TRAFFIC_YELLOW , LOW  );
    digitalWrite(PIN_TRAFFIC_GREAN  , LOW  );
    delay(1000);
    bool boolSpecialVehicle = boolFirebaseGetBool ( StringMyID + "/specialVehicle" );
    if ( boolSpecialVehicle ==  true )
    {
      voidFirebaseSetBool( StringMyID + "/specialVehicle" , false );
      break; 
    }
  }
  voidFirebaseSetInt( StringMyID + "/Status" , V2I_ID_TRAFFIC_YELLOW );
  digitalWrite(PIN_TRAFFIC_RED    , LOW  ); 
  digitalWrite(PIN_TRAFFIC_YELLOW , HIGH );
  digitalWrite(PIN_TRAFFIC_GREAN  , LOW  );
  delay(3000);
  for ( int intCounter = 0 ; intCounter<= 10 ; intCounter++ )
  {
    voidFirebaseSetInt( StringMyID + "/Status" , V2I_ID_TRAFFIC_GREAN );
    digitalWrite(PIN_TRAFFIC_RED    , LOW  );
    digitalWrite(PIN_TRAFFIC_YELLOW , LOW  );
    digitalWrite(PIN_TRAFFIC_GREAN  , HIGH );
    delay(1000);
    bool boolDetectAccident = boolFirebaseGetBool ( StringMyID + "/DetectAccident" );
    if ( boolDetectAccident ==  true )
    {
      voidFirebaseSetBool ( StringMyID + "/DetectAccident" , false );
      break; 
    }
  }




}
