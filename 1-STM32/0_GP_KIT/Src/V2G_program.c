/**
 ******************************************************************************
 * @file           : V2G_program.c
 * @author         : Diea Abdeltwab
 * @layer          : Service
 * @brief          : 
 * @date           : 7/3/2024
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_INTERFACE.h"
#include "USART_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "CARKIT_interface.h"
#include "GUI_interface.h"

#include "V2G_interface.h"
#include "V2G_config.h"
#include "V2G_private.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/


/*************************************************************************************************************************************/
/********************************************************* V2G ***********************************************************************/
/*************************************************************************************************************************************/

/*************************************************************************************************************/
/************************************* Plug Cable ************************************************************/
/*************************************************************************************************************/
uint8_t V2G_u8PlugCable ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_PLUG_CABLE ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd , 1);

	MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK )
	{
		MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		Local_u8SuccessFlag = 1 ;
	}
	return Local_u8SuccessFlag ;
}
/*************************************************************************************************************/
/************************************* Identification ********************************************************/
/*************************************************************************************************************/
uint8_t V2G_u8Identification ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	uint8_t  Local_pu8VIN[]   = VEHICLE_VIN ;
	Local_u8LengthToFollow = 1 + sizeof(Local_pu8VIN) ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_IDENTIFICATION ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd , 1);
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, Local_pu8VIN       , sizeof(Local_pu8VIN));

	MUSART_u8ReceiveArraySynch(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK )
	{
		MUSART_u8ReceiveArraySynch(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if ( Local_u8ReceivedData[0] == V2G_EV_VERIFY_IDENTIFICATION_SCCESS )
		{
			Local_u8SuccessFlag =  1;
		}
	}
	return Local_u8SuccessFlag ;
}
/*************************************************************************************************************/
/************************************* Charge Parameter ******************************************************/
/*************************************************************************************************************/
uint8_t V2G_u8ChargeParameter ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	uint8_t Local_u8Voltage  = SCARKIT_u8GetVoltageValue();
	//uint8_t Local_u8Voltage = 5;
	uint8_t Local_u8EnergyAmount = (Local_u8Voltage*100)/12  ;

	Local_u8LengthToFollow = 2 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_CHARGE_PARAMETAR ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd   , 1);
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8EnergyAmount, 1 );

	MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK  )
	{
		MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] == V2G_EV_ACCEPT_CHARGING  )
		{
			Local_u8SuccessFlag =  1;
		}
	}
	return Local_u8SuccessFlag ;
}
/*************************************************************************************************************/
/************************************* Charging Profiles *****************************************************/
/*************************************************************************************************************/
uint8_t V2G_u8ChargingCost ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_CHARGING_PROFILE ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd   , 1 );

	MUSART_u8ReceiveArraySynch(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK  )
	{
		MUSART_u8ReceiveArraySynch(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] == V2G_EV_ADD_COST_SCCESS  )
		{
			Local_u8SuccessFlag = 1 ;
		}
	}
	return Local_u8SuccessFlag ;
}
/*************************************************************************************************************/
/************************************* Start Charging ********************************************************/
/*************************************************************************************************************/
void V2G_voidStartCharging ( void )
{
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_START_CHARGING ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd, 1);

	MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK  )
	{
		MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] ==  V2G_EV_ACCEPT_START_CHARGING )
		{
	        // What ?
		}

	}
}
/*************************************************************************************************************/
/************************************* END Charging **********************************************************/
/*************************************************************************************************************/
void V2G_voidEndCharging ( void )
{
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =   V2G_EV_END_CHARGING ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd, 1);

	MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK  )
	{
		MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] ==  V2G_EV_ACCEPT_END_CHARGING )
		{
	        // What ?
		}
	}
}
/*************************************************************************************************************/
/************************************* Send Energy Amount ****************************************************/
/*************************************************************************************************************/
void V2G_voidSendEnergyAmount (void )
{
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	uint8_t Local_u8Voltage  = SCARKIT_u8GetVoltageValue();
	//uint8_t Local_u8Voltage = 10 ;
	uint8_t Local_u8EnergyAmount =  (Local_u8Voltage*100)/12  ;


	Local_u8LengthToFollow = 2 ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  V2G_EV_SEND_ENERGY_AMOUNT ;
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8SelectCmd   , 1);
	MUSART_u8TransmitArraySynch(V2G_USART_INDEX, &Local_u8EnergyAmount, 1 );

	MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == V2G_EV_ACK  )
	{
		MUSART_u8ReceiveArrayNonBlocking(V2G_USART_INDEX, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] == V2G_EV_ACCEPT_UPDATE_ENARGY  )
		{
	        // What ?
		}
	}
}

/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

