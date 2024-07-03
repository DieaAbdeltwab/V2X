/**
 ******************************************************************************
 * @file           : IR_program.c
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
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "AFIO_INTERFACE.h"
#include "EXTI_INTERFACE.h"
#include "NVIC_INTERFACE.h"
#include "STK_INTERFACE.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "IR_interface.h"
#include "IR_private.h"
#include "IR_config.h"

/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void  ( *IR_ApfCallBack[21])(void) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
volatile  uint8_t   IR_u8StartFlag        =  0  ;
volatile  uint32_t  IR_Au32FrameData[100] = {0} ;
volatile  uint8_t   IR_u8EdgeCounter      =  0  ;
volatile  uint8_t   IR_u8Data             =  0  ;

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HIR_voidInit
 * @brief          : Init IR Config
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void    HIR_voidInit            ( void )
{
	MAFIO_u8PortRemap            ( IR_EXTI_LINE ,  IR_EXTI_PORT);
	MSTK_u8ClockConfig           ( STK_AHB_DIV_8 ) ;
	MNVIC_u8EnableInterrupt      ( IR_EXTI_LINE +  6  ) ;
	MGPIO_u8SetPinDirection      ( IR_EXTI_PORT ,  IR_EXTI_LINE , INPUT_FLOATING ) ;
	MEXTI_u8InterruptState       ( IR_EXTI_LINE ,  ENABLE );
	MEXTI_u8SetSignalLatch       ( IR_EXTI_LINE ,  FALLINNG ) ;
	MEXTI_u8SetCallBack          ( IR_EXTI_LINE , &HIR_voidGetFrame ) ;



}
/**
 ******************************************************************************
 * @fn             : HIR_u8ButtonSetCallBack
 * @brief          : Call Back for Buttons
 * @param[in]      : Copy_u32Ticks --> Get options from @IRbutton
 * @param          : Copy_pFun     --> Set address of Call back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   HIR_u8ButtonSetCallBack     ( IRbutton Copy_Button,void ( * Copy_pFun )( void ) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK  ;
	if ( Copy_pFun != NULL)
	{
		IR_ApfCallBack[Copy_Button] = Copy_pFun ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK  ;
	}
	return Local_u8ErrorState ;
}

/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
static void HIR_voidGetFrame ( void )
{
	 if ( IR_u8StartFlag == 0 )
	 {
		MSTK_u8SetInterval (  IR_MAX_TakeAction_TIME ,SINGLE, HIR_voidTakeAction ) ;
		IR_u8StartFlag  = 1 ;
	 }
	 else
	 {
		MSTK_u8GetElapsedTime    ( &IR_Au32FrameData [ IR_u8EdgeCounter ]      );
		MSTK_u8SetInterval       (  IR_MAX_TakeAction_TIME ,SINGLE, HIR_voidTakeAction );
		IR_u8EdgeCounter++;
	 }


}

static void HIR_voidTakeAction ( void )
{
	//if (IR_Au32FrameData[0] >=IR_MIN_RANGE_TIME_FOR_START_BIT && IR_Au32FrameData[0]<=IR_MAX_RANGE_TIME_FOR_START_BIT && ( ERROR_STATE_OK == HIR_u8RightAddress() ) )
	{
        for(uint8_t Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++)
	    {
    	    if ( IR_Au32FrameData[IR_DATA_COMMEND_START_EDGE+Local_u8Counter] >= IR_MIN_RANGE_TIME_FOR_ONE && IR_Au32FrameData[IR_DATA_COMMEND_START_EDGE+Local_u8Counter] <= IR_MAX_RANGE_TIME_FOR_ONE )
    	    {
    		    SET_BIT(IR_u8Data,Local_u8Counter);
    	    }
    	    else
    	    {
    		    CLR_BIT(IR_u8Data,Local_u8Counter);
    	    }
	    }

        HIR_voidPlay( IR_u8Data );
	}
	IR_u8StartFlag       = 0 ;
	IR_Au32FrameData[0]  = 0 ;
	IR_u8EdgeCounter     = 0 ;
	IR_u8Data            = 0 ;
}

static uint8_t HIR_u8RightAddress ( void )
{
	uint8_t Local_u8Address = 0 ,Local_u8ErrorState = ERROR_STATE_OK;
    for(uint8_t Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++)
    {
	    if ( IR_Au32FrameData[IR_ADDRESS_COMMEND_START_EDGE+Local_u8Counter] >= IR_MIN_RANGE_TIME_FOR_ONE && IR_Au32FrameData[IR_ADDRESS_COMMEND_START_EDGE+Local_u8Counter] <= IR_MAX_RANGE_TIME_FOR_ONE )
	    {
		    SET_BIT(Local_u8Address,Local_u8Counter);
	    }
	    else
	    {
		    CLR_BIT(Local_u8Address,Local_u8Counter);
	    }
    }
    if ( Local_u8Address == IR_REMOTE_ADDRESS )
    {
    	Local_u8ErrorState = ERROR_STATE_OK  ;
    }
    else
    {
    	Local_u8ErrorState = ERROR_STATE_NOK  ;
    }
    return Local_u8ErrorState ;
}

static void HIR_voidPlay ( uint8_t Copy_u8Data )
{
	switch ( Copy_u8Data )
	{
	    case IR_POWER_DATA_BUTTON       : if ( IR_ApfCallBack[IR_POWER]    != NULL) { IR_ApfCallBack[IR_POWER]    ( ) ; }    break;
	    case IR_MODE_DATA_BUTTON        : if ( IR_ApfCallBack[IR_MODE]     != NULL) { IR_ApfCallBack[IR_MODE]     ( ) ; }    break;
	    case IR_MUTE_DATA_BUTTON        : if ( IR_ApfCallBack[IR_MUTE]     != NULL) { IR_ApfCallBack[IR_MUTE]     ( ) ; }    break;
	    case IR_PLAY_DATA_BUTTON        : if ( IR_ApfCallBack[IR_PLAY]     != NULL) { IR_ApfCallBack[IR_PLAY]     ( ) ; }    break;
	    case IR_NEXT_DATA_BUTTON        : if ( IR_ApfCallBack[IR_NEXT]     != NULL) { IR_ApfCallBack[IR_NEXT]     ( ) ; }    break;
	    case IR_PREV_DATA_BUTTON        : if ( IR_ApfCallBack[IR_PREV]     != NULL) { IR_ApfCallBack[IR_PREV]     ( ) ; }    break;
	    case IR_EQ_DATA_BUTTON          : if ( IR_ApfCallBack[IR_EQ]       != NULL) { IR_ApfCallBack[IR_EQ]       ( ) ; }    break;
	    case IR_VOL_DOWN_DATA_BUTTON    : if ( IR_ApfCallBack[IR_VOLDOWEN] != NULL) { IR_ApfCallBack[IR_VOLDOWEN] ( ) ; }    break;
	    case IR_VOL_UP_DATA_BUTTON      : if ( IR_ApfCallBack[IR_VOLUP]    != NULL) { IR_ApfCallBack[IR_VOLUP]    ( ) ; }    break;
	    case IR_ZER0_DATA_BUTTON        : if ( IR_ApfCallBack[IR_RPT]      != NULL) { IR_ApfCallBack[IR_RPT]      ( ) ; }    break;
	    case IR_RPT_DATA_BUTTON         : if ( IR_ApfCallBack[IR_USD]      != NULL) { IR_ApfCallBack[IR_USD]      ( ) ; }    break;
	    case IR_USD_DATA_BUTTON         : if ( IR_ApfCallBack[IR_ZER0]     != NULL) { IR_ApfCallBack[IR_ZER0]     ( ) ; }    break;
	    case IR_ONE_DATA_BUTTON         : if ( IR_ApfCallBack[IR_ONE]      != NULL) { IR_ApfCallBack[IR_ONE]      ( ) ; }    break;
	    case IR_TWO_DATA_BUTTON         : if ( IR_ApfCallBack[IR_TWO]      != NULL) { IR_ApfCallBack[IR_TWO]      ( ) ; }    break;
	    case IR_THREE_DATA_BUTTON       : if ( IR_ApfCallBack[IR_THREE]    != NULL) { IR_ApfCallBack[IR_THREE]    ( ) ; }    break;
	    case IR_FOUR_DATA_BUTTON        : if ( IR_ApfCallBack[IR_FOUR]     != NULL) { IR_ApfCallBack[IR_FOUR]     ( ) ; }    break;
	    case IR_FIVE_DATA_BUTTON        : if ( IR_ApfCallBack[IR_FIVE]     != NULL) { IR_ApfCallBack[IR_FIVE]     ( ) ; }    break;
	    case IR_SIX_DATA_BUTTON         : if ( IR_ApfCallBack[IR_SIX]      != NULL) { IR_ApfCallBack[IR_SIX]      ( ) ; }    break;
	    case IR_SEVEN_DATA_BUTTON       : if ( IR_ApfCallBack[IR_SEVEN]    != NULL) { IR_ApfCallBack[IR_SEVEN]    ( ) ; }    break;
	    case IR_EIGHT_DATA_BUTTON       : if ( IR_ApfCallBack[IR_EIGHT]    != NULL) { IR_ApfCallBack[IR_EIGHT]    ( ) ; }    break;
	    case IR_NINE_DATA_BUTTON        : if ( IR_ApfCallBack[IR_NINE]     != NULL) { IR_ApfCallBack[IR_NINE]     ( ) ; }    break;
	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
