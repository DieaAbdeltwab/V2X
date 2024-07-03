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
unsigned long sendDataPrevMillis = 0 ;
#define RXD2 16
#define TXD2 17
char Local_u8CmdPacket[255]={0};
/************************************************************************************/
String VEHICLE_VIN  ="XP7SA1DG9SFC14705" ;
/*------------------------------------------------*/
double doubleGpsLongitude =  0 ; 
double doubleGpslatitude  =  0 ; 
int    intCompassDegree   =  0 ; 
/*------------------------------------------------*/
#define NACK_FOUND					                0xA1
#define CHECK_OBJECT                        0xA2
#define SPECIAL_VEHICLE                     0xA3
/*------------------------------------------------*/
#define V2I_ID_STOP                         0xB0
#define V2I_ID_SPEED_35                     0xB1
#define V2I_ID_SPEED_25                     0xB2
/*------------------------------------------------*/
/*------------------- Not Used -------------------*/
/*------------------------------------------------*/
#define V2I_ID_TRAFFIC_RED                  0xB4
#define V2I_ID_TRAFFIC_YELLOW               0xB5
#define V2I_ID_TRAFFIC_GREAN                0xB6
/*------------------------------------------------*/
#define V2I_ID_SPECIAL_VEHICLE_SUCCESS      0xC0
#define V2I_ID_SPECIAL_VEHICLE_ERROR        0xC1
/*------------------------------------------------*/
#define V2I_ID_SPECIAL_VEHICLE_WARNING      0xC4
/*------------------------------------------------*/
#define V2P_ID_VEHICLE_PEDESTRIAN           0xD0
/**************************************************/
#define V2P_ID_VEHICLE_WARNING              0xD1
/*------------------------------------------------*/
String stringSpecialVehicleTrafficLightRedID = "0";
/*------------------------------------------------*/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void voidSendNAckFound ( void )
{
	uint8_t Local_u8NAckBuffer = NACK_FOUND;
  Serial2.write( &Local_u8NAckBuffer  , 1 ) ; 
}

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
void voidSetPedestrianVehicleWarning ( String Copy_StringFirebasePass )
{
  bool intPedestrianVehicleWarningStatus   = boolFirebaseGetBool ( Copy_StringFirebasePass +  "/warning" );
  if ( intPedestrianVehicleWarningStatus == false && Copy_StringFirebasePass != "0")
  {
    voidFirebaseSetBool ( Copy_StringFirebasePass +  "/warning" , true );
  }
} 
char charGetTrafficLightStatus ( String Copy_StringFirebasePass )
{
  char charTrafficLightStatus   = (char)intFirebaseGetInt ( Copy_StringFirebasePass +  "/Status");
  return charTrafficLightStatus ; 
}
int intCheckSignPosition( String Copy_StringFirebasePass )
{
  double doubleSignLatitude   = doubleFirebaseGetDouble ( Copy_StringFirebasePass +  "/latitude");
  double doubleSignLongitude  = doubleFirebaseGetDouble ( Copy_StringFirebasePass +  "/longitude");
  double doubleBearing = atan2(
    sin(doubleSignLongitude - doubleGpsLongitude) * cos(doubleSignLatitude),
    cos(doubleGpslatitude) * sin(doubleSignLatitude) - sin(doubleGpslatitude) * cos(doubleSignLatitude) * cos(doubleSignLongitude - doubleGpsLongitude)
  );
  int intBearing = degrees(doubleBearing);
  intBearing = (intBearing + 360) % 360 ;
  int intAccuracyDegree = intBearing - intCompassDegree ; 
  Serial.print(intBearing);
  Serial.print(" - ");
  Serial.print(intCompassDegree);
  Serial.print(" = ");
  Serial.println((int)intAccuracyDegree);
  return intAccuracyDegree ;  
}
void voidSetVINinSignDataBase ( String Copy_StringFirebasePass , String Copy_StringTime )
{
  voidFirebaseSetString ( Copy_StringFirebasePass +  "/" + Copy_StringTime , VEHICLE_VIN );
}
void voidUpdateMyLocation (void)
{
  doubleGpslatitude   = doubleFirebaseGetDouble ( VEHICLE_VIN +  "/latitude");
  doubleGpsLongitude  = doubleFirebaseGetDouble ( VEHICLE_VIN +  "/longitude");
  intCompassDegree    = intFirebaseGetInt       ( VEHICLE_VIN +  "/compassDegree");
}
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
String stringGetMyCheckedLocation (void)
{
  String StringCheckedArealatitude  = String(doubleGpsLongitude,5) ;
  String StringCheckedAreaLongitude = String(doubleGpslatitude ,5) ;
  StringCheckedArealatitude [2]  = ',';
  StringCheckedAreaLongitude[2]  = ',';
  StringCheckedArealatitude [7]  = ' ';
  StringCheckedAreaLongitude[7]  = '-';
  String StringCheckedAreaLocation =  StringCheckedAreaLongitude + StringCheckedArealatitude ;
  return StringCheckedAreaLocation ; 
}
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void voidSetTrafficLightSpecialVehicle ( String Copy_StringFirebasePass )
{    
  bool boolTrafficLightSpecialVehicleStatus   = boolFirebaseGetBool ( Copy_StringFirebasePass +  "/specialVehicle" );
  if ( boolTrafficLightSpecialVehicleStatus == false && Copy_StringFirebasePass != "0")
  {
    voidFirebaseSetBool ( Copy_StringFirebasePass +  "/specialVehicle" , true );
  }
  stringSpecialVehicleTrafficLightRedID = "0";
}
void voidCheckObject( void )
{
  voidUpdateMyLocation ();
  String stringMyCheckedLocation = stringGetMyCheckedLocation( ) ;
  String stringSignID            = stringFirebaseGetString   ( stringMyCheckedLocation +"/id");
  if ( stringSignID == "ERROR!" )
  {
    voidSendNAckFound();
    Serial.println("Not Found");
  }
  else 
  {
    char Local_charActionID = 0 ;
    Serial.println("Found");
    int Local_intAccuracyDegree =  intCheckSignPosition( stringSignID );
    if (abs(Local_intAccuracyDegree)<=60 || abs(Local_intAccuracyDegree)>=300 )
    {
      String stringDateAndTime = stringFirebaseGetString   ( VEHICLE_VIN +"/dateAndTime");
      voidSetVINinSignDataBase ( stringSignID , stringDateAndTime );
      if ( stringSignID.substring(0,4) == "R1-1")
      {
        Serial.println("STOP");      
        Local_charActionID = V2I_ID_STOP ;
      }
      else if ( stringSignID.substring(0,5) == "W13-1" )
      {
        Serial.println("Limit Speed : 35");
        Local_charActionID = V2I_ID_SPEED_35 ;
      }
      else if ( stringSignID.substring(0,5) == "W13-2" )
      {
        Serial.println("Limit Speed : 25");
        Local_charActionID = V2I_ID_SPEED_25 ;
      }
      else if ( stringSignID.substring(0,4) == "W3-3" )
      {
        Local_charActionID = charGetTrafficLightStatus ( stringSignID );
        if ( Local_charActionID == V2I_ID_TRAFFIC_RED )
        {
          stringSpecialVehicleTrafficLightRedID = stringSignID ;
        }
        Serial.print("Traffic Light : ");
        Serial.println((int)Local_charActionID);
      }
      else if ( stringSignID.substring(0,5) == "R9-3A" )
      {
        voidSetPedestrianVehicleWarning ( stringMyCheckedLocation ); 
        Local_charActionID = V2P_ID_VEHICLE_PEDESTRIAN ;
        Serial.println("Pedestrian ");
      }
      else 
      {
        Local_charActionID = NACK_FOUND ;
        Serial.println("Error! , in ID " );
      }
    }
    else 
    {
      Local_charActionID = NACK_FOUND ;
      Serial.println("Error! , in Sign Position");
    }
    Serial2.write( &Local_charActionID  , 1 ) ; 
  }
}
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);    //Hardware Serial of ESP32
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
  memset(Local_u8CmdPacket,0,255);
  if (Serial2.available())
  {
    Serial2.readBytes( Local_u8CmdPacket    , 1                    ) ; 
    Serial2.readBytes(&Local_u8CmdPacket[1] , Local_u8CmdPacket[0] ) ; 
    switch (Local_u8CmdPacket[1])
		{
		case CHECK_OBJECT     	  : 
      voidCheckObject     ()  ;  
      break                   ;
    case SPECIAL_VEHICLE     	: 
      voidSetTrafficLightSpecialVehicle  (stringSpecialVehicleTrafficLightRedID)  ;  
      break                   ;
    }
  }
  
}
