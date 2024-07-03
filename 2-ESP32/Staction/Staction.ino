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
/************************************************************************************/
int Global_intMoney = 0 ;
char   Global_pu8VIN[18] ;
String Global_StringVIN ="0";

String Global_StringMyID ="V2G-Station-001";

/*------------------------------------------------*/
#define SE_ACK					                     0xA5
#define SE_NACK					                     0x7F

#define SE_IDENTIFICATION     	             0x52
#define SE_CHARGING_COST                     0x54

#define SE_ADD_COST_SCCESS           		     0xB0
#define SE_ADD_COST_FAIL             		     0xB1

#define SE_VERIFY_IDENTIFICATION_SCCESS      0xB3
#define SE_VERIFY_IDENTIFICATION_FAIL        0xB4
/*------------------------------------------------*/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void voidSendNAck ( void )
{
	uint8_t Local_u8NAckBuffer = SE_NACK;
  Serial2.write( &Local_u8NAckBuffer  , 2 ) ; 
}
void voidSendAck (char Copy_u8ReplyLength )
{
	char Local_u8AckBuffer [2] = { SE_ACK , Copy_u8ReplyLength };
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
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
void SE_voidIdentification (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8VerifyIdentificationStatus = SE_VERIFY_IDENTIFICATION_FAIL ;
  for ( uint8_t Local_u8Counter =0 ; Local_u8Counter<18 ; Local_u8Counter++ )
	{
		Global_pu8VIN[Local_u8Counter] =(char) Copy_pu8CmdPacket[Local_u8Counter+2];
	}
  Global_StringVIN =  Global_pu8VIN ; 
  Global_intMoney = intFirebaseGetInt( Global_StringVIN +"/money");
	if ( Global_intMoney >= 10 )
	{
		Local_u8VerifyIdentificationStatus = SE_VERIFY_IDENTIFICATION_SCCESS ;
	}
	voidSendAck(1u);
  Serial2.write( &Local_u8VerifyIdentificationStatus  , 1 ) ; 
}
void SE_voidChargingCost (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8ChargCostStatus =  SE_ADD_COST_FAIL ;
	uint8_t Local_u8ChargingVolt    = *((uint8_t *) &Copy_pu8CmdPacket[2] );
  uint8_t Local_u8VoltCost = intFirebaseGetInt( Global_StringMyID +"/VoltCost"); //----<<<<----
  uint8_t Local_u8ChargingCost    = (Global_intMoney - (Local_u8ChargingVolt * Local_u8VoltCost) ) ;
  voidFirebaseSetInt( Global_StringMyID +"/"+ Global_StringVIN , (Local_u8ChargingVolt * Local_u8VoltCost) ); //----<<<<---- Can i Use Rtc her to Set Time (Time + Cost)
  voidFirebaseSetInt( Global_StringVIN  +"/money" , Local_u8ChargingCost );
	if ( Global_StringVIN !="0" )
	{
		Local_u8ChargCostStatus = SE_ADD_COST_SCCESS ;
    Global_intMoney  = 0  ;
    Global_StringVIN ="0" ;
	}
	voidSendAck(1u);
  Serial2.write( &Local_u8ChargCostStatus  , 1 ) ; 
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
  uint8_t buffer[255]="";
  if (Serial2.available())
  {
    Serial2.readBytes( buffer    , 1         ) ; 
    Serial2.readBytes(&buffer[1] , buffer[0] ) ; 
    switch (buffer[1])
		{
		case SE_IDENTIFICATION     	    :      SE_voidIdentification    (buffer)    ; break ;
		case SE_CHARGING_COST           :      SE_voidChargingCost      (buffer)    ; break ;
    }
  }
}
