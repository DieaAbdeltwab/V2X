/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of KPD ************************************************************************************/
/***************** Date : 9/9/2022  *****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For KPD ******************************************************************************/
/****************************************************************************************************************************/
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"

/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include"RCC_interface.h"
#include"GPIO_interface.h"
#include"STK_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include"KPD_interface.h"
#include"KPD_private.h"
#include"KPD_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
const uint8_t KPD_Au8Keys[KPD_NUMBER_ROW] [KPD_NUMBER_COL]= KPD_KEYS;
const uint8_t KPD_Au8RowsPins[KPD_NUMBER_ROW]={KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};
const uint8_t KPD_Au8ColsPins[KPD_NUMBER_COL]={KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HKPD_voidInit
 * @brief          : initialization Direction of Pin
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HKPD_voidInit(void)
{
	MGPIO_u8SetPinDirection( KPD_u8_PORT_ROW  , KPD_u8_R1_PIN , INPUT_PULL_UP_DOWEN  );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_ROW  , KPD_u8_R2_PIN , INPUT_PULL_UP_DOWEN  );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_ROW  , KPD_u8_R3_PIN , INPUT_PULL_UP_DOWEN  );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_ROW  , KPD_u8_R4_PIN , INPUT_PULL_UP_DOWEN  );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_COLS , KPD_u8_C1_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_COLS , KPD_u8_C2_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_COLS , KPD_u8_C3_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( KPD_u8_PORT_COLS , KPD_u8_C4_PIN , OUTPUT_SPEED_2MHZ_PP );

	MGPIO_u8SetPinValue( KPD_u8_PORT_ROW  , KPD_u8_R1_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_ROW  , KPD_u8_R2_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_ROW  , KPD_u8_R3_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_ROW  , KPD_u8_R4_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_COLS , KPD_u8_C1_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_COLS , KPD_u8_C2_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_COLS , KPD_u8_C3_PIN , HIGH );
	MGPIO_u8SetPinValue( KPD_u8_PORT_COLS , KPD_u8_C4_PIN , HIGH );
}
/**
 ******************************************************************************
 * @fn             : HKPD_u8GetKeyState
 * @brief          : Get value of Key
 * @param[OUT]     : Copy_pu8Key -> Get Value of key
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HKPD_u8GetKeyState ( uint8_t * Copy_pu8Key)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu8Key != NULL )
	{
		uint8_t Local_u8Pressed,Local_u8Key;
		Local_u8Key=KEY_NOT_PRESSED;
		for(uint8_t Local_u8ColumnsCounter=0;Local_u8ColumnsCounter<KPD_NUMBER_COL;Local_u8ColumnsCounter++)
		{
			MGPIO_u8SetPinValue(KPD_u8_PORT_COLS,KPD_Au8ColsPins[Local_u8ColumnsCounter],LOW);
			for(uint8_t Local_u8RowsCounter=0;Local_u8RowsCounter<KPD_NUMBER_ROW;Local_u8RowsCounter++)
			{
				MGPIO_u8GetPinValue(KPD_u8_PORT_ROW, KPD_Au8RowsPins[Local_u8RowsCounter], &Local_u8Pressed);
				if(Local_u8Pressed==LOW)
				{
					Local_u8Key=KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColumnsCounter];
					while(Local_u8Pressed==LOW)
					{
						MGPIO_u8GetPinValue(KPD_u8_PORT_ROW, KPD_Au8RowsPins[Local_u8RowsCounter], &Local_u8Pressed);
					}
					MSTK_u8BusyWait(KPD_TIME_NOT_PRESSED_AGIN);
				}
			}
			MGPIO_u8SetPinValue(KPD_u8_PORT_COLS,KPD_Au8ColsPins[Local_u8ColumnsCounter],HIGH);
		}
		*Copy_pu8Key = Local_u8Key;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState  ;
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
