/**
 ******************************************************************************
 * @file           : STP_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 29/7/2023
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
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HSTP_voidInit
 * @brief          : Init Serial to parallel IC
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HSTP_voidInit( void )
{
	MSTK_u8ClockConfig(STK_AHB_DIV_8) ;
	#if STP_NUMBER_IC == STP_ONE_IC
		MGPIO_u8SetPinDirection ( STP_DATA_PIN_IC1      , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BIT_SHCP_PIN_IC1  , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BYTE_STCP_PIN_IC1 , OUTPUT_SPEED_2MHZ_PP );
	#elif STP_NUMBER_IC == STP_TWO_IC
		MGPIO_u8SetPinDirection ( STP_DATA_PIN_IC1      , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BIT_SHCP_PIN_IC1  , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BYTE_STCP_PIN_IC1 , OUTPUT_SPEED_2MHZ_PP );

		MGPIO_u8SetPinDirection ( STP_DATA_PIN_IC2      , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BIT_SHCP_PIN_IC2  , OUTPUT_SPEED_2MHZ_PP );
		MGPIO_u8SetPinDirection ( STP_BYTE_STCP_PIN_IC2 , OUTPUT_SPEED_2MHZ_PP );
	#endif
}
/**
 ******************************************************************************
 * @fn             : HSTP_u8SetIC1Byte
 * @brief          : Set 8 Bit IC1
 * @param[in]      : Copy_u8Data  --> Set Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HSTP_u8SetIC1Byte ( uint8_t Copy_u8Data )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( 1 )
	{
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , LOW );
		for( uint8_t Local_u8Counter = STP_PIN_NUMBER  ; Local_u8Counter > 0 ; Local_u8Counter-- )
		{
			MGPIO_u8SetPinValue( STP_DATA_PIN_IC1 , ( GET_BIT( Copy_u8Data , ( Local_u8Counter - 1  ) ) ) );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , HIGH );
			MSTK_u8BusyWait    ( STP_WAIT_SHIFT );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , LOW  );
		}
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , HIGH );
		MSTK_u8BusyWait     ( STP_TIME_ENABLE_PULS );
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , LOW  );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : HSTP_u8SetIC2Byte
 * @brief          : Set 8 Bit IC2
 * @param[in]      : Copy_u8Data  --> Set Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HSTP_u8SetIC2Byte ( uint8_t Copy_u8Data )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( 1 )
	{
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC2 , LOW );
		for( uint8_t Local_u8Counter = STP_PIN_NUMBER  ; Local_u8Counter > 0 ; Local_u8Counter-- )
		{
			MGPIO_u8SetPinValue( STP_DATA_PIN_IC2 , ( GET_BIT( Copy_u8Data , ( Local_u8Counter - 1  ) ) ) );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC2 , HIGH );
			MSTK_u8BusyWait    ( STP_WAIT_SHIFT );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC2 , LOW  );
		}
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC2 , HIGH );
		MSTK_u8BusyWait     ( STP_TIME_ENABLE_PULS );
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC2 , LOW  );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : HSTP_u8SetICValue
 * @brief          : Set 8 Bit and select IC number
 * @param[in]      : Copy_u8ICNumber  --> Set Number of IC
 * @param[in]      : Copy_u8Data  --> Set Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HSTP_u8SetICValue (uint8_t Copy_u8ICNumber , uint8_t Copy_u8Data )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( 1 )
	{
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , LOW );
		for( uint8_t Local_u8Counter = STP_PIN_NUMBER * ( Copy_u8ICNumber + 1 ) ; Local_u8Counter > 0 ; Local_u8Counter-- )
		{
			MGPIO_u8SetPinValue( STP_DATA_PIN_IC1 , ( GET_BIT( Copy_u8Data , ( Local_u8Counter - 1 - ( Copy_u8ICNumber * STP_PIN_NUMBER ) ) ) ) );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , HIGH );
			MSTK_u8BusyWait    ( STP_WAIT_SHIFT );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , LOW  );
		}
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , HIGH );
		MSTK_u8BusyWait     ( STP_TIME_ENABLE_PULS );
		MGPIO_u8SetPinValue ( STP_BYTE_STCP_PIN_IC1 , LOW  );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : HSTP_u8SetICSHalfWord
 * @brief          : Set 16 Bit
 * @param[in]      : Copy_u8DataIC1  --> Set 8Bit Data
 * @param[in]      : Copy_u8DataIC2  --> Set 8Bit Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HSTP_u8SetICSHalfWord ( uint8_t Copy_u8DataIC1 , uint8_t Copy_u8DataIC2 )
{
    uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( 1 )
	{
		uint16_t Local_u16Data  ;
		         Local_u16Data  = ( Copy_u8DataIC2 << 8 ) ;
		         Local_u16Data |= (uint8_t)( Copy_u8DataIC1  ) ;
		MGPIO_u8SetPinValue( STP_BYTE_STCP_PIN_IC1 , LOW );
		for( uint8_t Local_u8Counter = STP_PIN_NUMBER * 2  ; Local_u8Counter > 0 ; Local_u8Counter-- )
		{
			MGPIO_u8SetPinValue( STP_DATA_PIN_IC1 , ( GET_BIT( Local_u16Data , ( Local_u8Counter - 1 )  ) ) );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , HIGH  );
			MSTK_u8BusyWait( STP_WAIT_SHIFT );
			MGPIO_u8SetPinValue( STP_BIT_SHCP_PIN_IC1 , LOW   );
		}
		MGPIO_u8SetPinValue(  STP_BYTE_STCP_PIN_IC1 , HIGH );
		MSTK_u8BusyWait( STP_TIME_ENABLE_PULS );
		MGPIO_u8SetPinValue(  STP_BYTE_STCP_PIN_IC1 , LOW  );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : STP_u8LedMatrix
 * @brief          : Led matrix connected by serial to parallel
 * @param[in]      : Copy_pu8PatternArray  --> Set Address of Pattern
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void STP_u8LedMatrix  ( uint8_t * Copy_pu8PatternArray )
{
	uint8_t Local_u8BitShift = 0;
	for( uint8_t Local_u8Counter = 0 ; Local_u8Counter < STP_PIN_NUMBER  ; Local_u8Counter ++ )
	{
		HSTP_u8SetIC2Byte ( STP_DISABLE_COL );
		HSTP_u8SetIC1Byte ( Copy_pu8PatternArray[Local_u8Counter] );
		Local_u8BitShift=   ~(STP_BIT_SHIFT_MASK << Local_u8Counter);
		HSTP_u8SetIC2Byte ( Local_u8BitShift );
		MSTK_u8BusyWait   ( STP_DISPLAY_ROW_TIME );

	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
