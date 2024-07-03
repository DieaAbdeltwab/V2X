/**
 ******************************************************************************
 * @file           : LEDMRX_program.c
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
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "STK_INTERFACE.h"

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HLEDMRX_voidInit
 * @brief          : Init Led matrix Init
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HLEDMRX_voidInit              ( void )
{

	MSTK_u8ClockConfig(STK_AHB_DIV_8) ;

	MGPIO_u8SetPinDirection( LEDMRT_ROW0_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW1_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW2_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW3_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW4_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW5_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW6_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_ROW7_PIN , OUTPUT_SPEED_2MHZ_PP );
	
	MGPIO_u8SetPinDirection( LEDMRT_COL0_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL1_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL2_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL3_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL4_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL5_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL6_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection( LEDMRT_COL7_PIN , OUTPUT_SPEED_2MHZ_PP );
}
/**
 ******************************************************************************
 * @fn             : HLEDMRX_u8DisplayNonBlocking
 * @brief          : Display Shape
 * @param          : Copy_pu8Data  --> Set address of Shape array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HLEDMRX_u8DisplayNonBlocking  ( uint8_t *Copy_pu8Data )
{
	 uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	 if ( Copy_pu8Data != NULL )
	 {
	     {
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT0] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL0_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT1] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL1_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT2] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL2_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT3] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL3_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT4] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL4_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT5] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL5_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT6] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL6_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	
	    	 HLEDMRX_voidDisableAllCols ( );
	    	 HLEDMRX_voidSetRowValues   ( Copy_pu8Data[LEDMRX_BIT7] );
	    	 MGPIO_u8SetPinValue        ( LEDMRT_COL7_PIN , LOW );
	    	 MSTK_u8BusyWait            ( LEDMRX_DISPLAY_ROW_TIME );
	     }
	 }
	 else
	 {
		 Local_u8ErrorState = ERROR_STATE_NOK ;
	 }
	 HLEDMRX_voidDisableAllCols();
	 return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
static void HLEDMRX_voidDisableAllCols ( void )
{
	MGPIO_u8SetPinValue( LEDMRT_COL0_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL1_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL2_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL3_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL4_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL5_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL6_PIN , HIGH );
	MGPIO_u8SetPinValue( LEDMRT_COL7_PIN , HIGH );
}
static void HLEDMRX_voidSetRowValues   ( uint8_t Copy_u8Value )
{
	MGPIO_u8SetPinValue( LEDMRT_ROW0_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT0 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW1_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT1 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW2_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT2 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW3_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT3 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW4_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT4 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW5_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT5 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW6_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT6 ) );
	MGPIO_u8SetPinValue( LEDMRT_ROW7_PIN , GET_BIT ( Copy_u8Value , LEDMRX_BIT7 ) );
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
