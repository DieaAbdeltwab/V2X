#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <math.h> 
#include "stdlib.h"
/************************************************************************************/
#define WIFI_SSID     "WE_F"
#define WIFI_PASSWORD "Diea@Abdeltwab_F" 
#define API_KEY       "AIzaSyD2PnFZ3kYQGHKO49Bzmjy6r-KQXioaYZY"
#define DATABASE_URL  "https://gp-1-a8657-default-rtdb.firebaseio.com/" 
FirebaseData  fbdo;
FirebaseAuth  auth;
FirebaseConfig config;
bool signupOK= false ;
unsigned long sendDataPrevMillis = 0 ;
#define RXD2 16
#define TXD2 17
/************************************************************************************/
String VEHICLE_VIN  ="XP7SA1DG9SFC14705" ;
/*---------------------------------------------*/
double doubleGpsLongitude =  0 ; 
double doubleGpslatitude  =  0 ; 
int    intCompassDegree   =  0 ; 
/*---------------------------------------------*/
int     intdestinationCounter=0 ;
int  intReachDestinationFlag = 0 ;
/*---------------------------------------------*/
#define ACK_FOUND			                      0xA0
#define NACK_FOUND					                0xA1
/*---------------------------------------------*/
#define SELF_DRIVING_RIGHT                  0xD0
#define SELF_DRIVING_LEFT                   0xD1
#define SELF_DRIVING_GO_STRAIGHT            0xD2
#define SELF_DRIVING_REACH_DESTINATION      0xD3
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void voidSendNAckFound ( void )
{
	uint8_t Local_u8NAckBuffer = NACK_FOUND;
  Serial2.write( &Local_u8NAckBuffer  , 2 ) ; 
}
void voidSendAckFound (char Copy_u8ReplyLength )
{
	char Local_u8AckBuffer [2] = { ACK_FOUND , Copy_u8ReplyLength };
  Serial2.write( Local_u8AckBuffer  , 2 ) ; 
}
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
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
double doubleArrayLocation[18][2]={
                                {29.299952,30.710649},
                                {29.299956,30.710630},
                                {29.299974,30.710637},
                                {29.299992,30.710634},
                                {29.299998,30.710639},
                                {29.300004,30.710639},
                                {29.300015,30.710635},
                                {29.300029,30.710634},
                                {29.300049,30.710640},
                                {29.300066,30.710646},
                                {29.300072,30.710646},
                                {29.300135,30.710645},
                                {29.300149,30.710645},
                                {29.300193,30.710646},
                                {29.300240,30.710650},
                                {29.300238,30.710650},
                                {29.300252,30.710651},
                                {29.300250,30.710657}};
/************************************************************************************/
/************************************************************************************/
 /************************************************************************************/
void voidUpdateMyLocation (void)
{
  doubleGpslatitude   = doubleFirebaseGetDouble ( VEHICLE_VIN +  "/latitude");
  doubleGpsLongitude  = doubleFirebaseGetDouble ( VEHICLE_VIN +  "/longitude");
  intCompassDegree    = intFirebaseGetInt       ( VEHICLE_VIN +  "/Compass Degree");
}
char charUpdateMyDestination( void )
{
  char charReachDestinationFlag = 0 ;
  double  doubleDistans = 0 ;
  for ( int intCounter = 0 ; intCounter<=5 ;intCounter++)
  {
    doubleDistans=acos(sin(radians(doubleGpslatitude))*sin(radians(doubleArrayLocation[intdestinationCounter][0]))
    +cos(radians(doubleGpslatitude))*cos(radians(doubleArrayLocation[intdestinationCounter][0]))
    *cos(radians(doubleArrayLocation[intdestinationCounter][1])-radians(doubleGpsLongitude)))*3440000.1 ;//Edit this  
    if (isnan(doubleDistans)==1)
    {
      doubleDistans=0;
    }
    if ( doubleDistans <= 3  )
    {
      intdestinationCounter++;
    }
  }
  Serial.print("------------------------------");
  Serial.print((int)intdestinationCounter);
  Serial.println("------------------------------");
  Serial.print("Distans : ");
  Serial.println((double)doubleDistans);
  if ( intdestinationCounter == (sizeof(doubleArrayLocation)/sizeof(doubleArrayLocation[0])))
  {
    intdestinationCounter=0;
    intReachDestinationFlag = 1 ; // Remove This 
    charReachDestinationFlag = 1 ;
  }
  return charReachDestinationFlag ; 
}
int intGetDirection( void )
{
  double doubleDestinationLatitude   = doubleArrayLocation[intdestinationCounter][0] ;
  double doubleDestinationLongitude  = doubleArrayLocation[intdestinationCounter][1] ;
  double doubleBearing = atan2(sin(radians(doubleDestinationLongitude) - radians(doubleGpsLongitude)) * cos(radians(doubleDestinationLatitude)),
    cos(radians(doubleGpslatitude)) * sin(radians(doubleDestinationLatitude)) - sin(radians(doubleGpslatitude)) * cos(radians(doubleDestinationLatitude)) 
    *cos(radians(doubleDestinationLongitude) - radians(doubleGpsLongitude)));
  int intBearing = degrees(doubleBearing);
  intBearing = (intBearing + 360) % 360 ;
  int intAccuracyDegree = intBearing - intCompassDegree ; 
  /*************************************************/
  if (abs(intAccuracyDegree)<=15 || abs(intAccuracyDegree)>=345 )
  {
    intAccuracyDegree = 0 ;
  }
  if ( doubleDestinationLatitude == doubleGpslatitude &&  doubleDestinationLongitude == doubleGpsLongitude )
  {
    intAccuracyDegree = 0 ;
  }
  /*************************************************/
  Serial.print((double)doubleGpslatitude,6);
  Serial.print("  :  ");
  Serial.print((double)doubleGpsLongitude,6);
  Serial.print(" ====>> ");
  Serial.print((double)doubleDestinationLatitude,6);
  Serial.print("  :  ");
  Serial.println((double)doubleDestinationLongitude,6);
  Serial.print(intBearing);
  Serial.print(" - ");
  Serial.print(intCompassDegree);
  Serial.print(" = ");
  Serial.print((int)intAccuracyDegree);
  Serial.print(" ====>> ");
  /*************************************************/
  return intAccuracyDegree ;  
}

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

void voidMove (void)
{
  char Local_charActionID = 0 ;
  char charReachDestinationFlag = 0 ;
  /*===========================================================================================*/
  if ( intReachDestinationFlag==0 )
  {
    voidUpdateMyLocation();
    charReachDestinationFlag = charUpdateMyDestination();
    if ( charReachDestinationFlag == 0 )
    {
      int intDirection = intGetDirection() ;
      if ( intDirection > 0 || intDirection < -300 )
      {
        Local_charActionID == SELF_DRIVING_RIGHT ;
        Serial.println("Right");
      }
      else if ( intDirection < 0)
      {
        Local_charActionID == SELF_DRIVING_LEFT ;
        Serial.println("Left");
      }
     else if ( intDirection == 0)
      {
        Local_charActionID == SELF_DRIVING_GO_STRAIGHT ;
        Serial.println("Go Straight");
      }
    }
    else if ( charReachDestinationFlag == 1 )
    {
      Local_charActionID == SELF_DRIVING_REACH_DESTINATION ;
      Serial.println("===================>>Reach To Destination<<===================");
    }
  }
  /*===========================================================================================*/
}
void setup() 
{
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

void loop() {

  delay(1000);
  voidMove();
  
}
