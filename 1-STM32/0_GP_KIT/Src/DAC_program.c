/**
 ******************************************************************************
 * @file           : DAC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 25/7/2023
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
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "DAC_interface.h"
#include "DAC_private.h"
#include "DAC_config.h"

/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
volatile   uint32_t   DAC_u32DataCounter = 0     ;
const      uint8_t   *DAC_pu8DataArrayCallBack   ;
uint32_t   DAC_u32ArraySizeCallBack   ;
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HDAC_voidInit
 * @brief          : Init Digital to Analog Config
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void   HDAC_voidInit    ( void )
{
	   MGPIO_u8SetPortDirection      ( DAC_PORT , DAC_PORT_Position , OUTPUT_SPEED_2MHZ_PP );
	   MSTK_u8ClockConfig(STK_AHB_DIV_8)  ;
}
/**
 ******************************************************************************
 * @fn             : HDAC_voidPlay
 * @brief          : Play Audio or ...
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void   HDAC_voidPlay    ( void )
{
	   MSTK_u8SetInterval    ( DAC_RATE_TIME_US , PERIODIC, HDAC_voidSetData );
}
/**
 ******************************************************************************
 * @fn             : HDAC_u8GetData
 * @brief          : Set your Data in this Function
 * @param[in]      : Copy_pu8DataArray --> Set Address of Data Array
 * @param          : Copy_u16ArraySize --> Set Size of Data Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *  Set  Data Array in DAC_data.h (404)
 *
 ******************************************************************************
 */
uint8_t     HDAC_u8GetData   ( const  uint8_t * Copy_pu8DataArray  , uint16_t Copy_u16ArraySize )
{
	   uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	   if ( Copy_pu8DataArray != NULL )
	   {
		   DAC_pu8DataArrayCallBack    =  Copy_pu8DataArray   ;
		   DAC_u32ArraySizeCallBack    =  Copy_u16ArraySize   ;
	   }
	   else
	   {
		   Local_u8ErrorState = ERROR_STATE_NOK ;
	   }
	   return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
static void HDAC_voidSetData ( void )
{
	MGPIO_u8SetPortValue ( DAC_PORT , DAC_PORT_Position , DAC_pu8DataArrayCallBack[DAC_u32DataCounter] );
	DAC_u32DataCounter++ ;
	if ( DAC_u32DataCounter == DAC_u32ArraySizeCallBack )
	{
		DAC_u32DataCounter = 0 ;
	}
	
	
	
}



