/**
 ******************************************************************************
 * @file           : EXTI_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
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
#include "stm32f103xx.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void (* EXTI_ApfCallBack[16])(void) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/

/**
 ******************************************************************************
 * @fn             : MEXTI_u8Config
 * @brief          : EXTI line Config
 * @param[in]      : Copy_Config --> init Value of Pin from @EXTI_config_t struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8Config    ( EXTI_config_t* Copy_Config )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_Config != NULL && Copy_Config->InitState <= EXTI_ENABLE && Copy_Config->PinNumber<=LINE15 )
	{
        switch (Copy_Config-> TrigSrc )
        {
        	case FALLINNG        : EXTI->FTSR |=  (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
							       EXTI->RTSR &=~ (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
							       break ;
        	case RISING          : EXTI->FTSR &=~ (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
							       EXTI->RTSR |=  (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
							       break ;
        	case FALLINNG_RISING : EXTI->FTSR |=  (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
								   EXTI->RTSR |=  (EXTI_TRIGSRC_MASK << (Copy_Config->PinNumber));
							       break ;
        	default              : Local_u8ErrorState = ERROR_STATE_NOK ;
        }
        EXTI->IMR &=~ (EXTI_STATE_MASK << (Copy_Config->PinNumber));
        EXTI->IMR |=  (Copy_Config->InitState << (Copy_Config->PinNumber));
        if ( Copy_Config->CallBackFunc != NULL )
        {
        	EXTI_ApfCallBack[Copy_Config->PinNumber]=Copy_Config->CallBackFunc;
        }
    	else
    	{
    		Local_u8ErrorState = ERROR_STATE_NULL_PTR ;
    	}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}

/**
 ******************************************************************************
 * @fn             : MEXTI_u8SetSignalLatch
 * @brief          : Set Signal Latch
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @param[in]      : Copy_SenseMode  --> get option from @EXTI_TrigSrc_t    enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SetSignalLatch   ( EXTI_LineNumber_t Copy_LineNumber , EXTI_TrigSrc_t Copy_SenseMode )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (  Copy_SenseMode <= FALLINNG_RISING && Copy_LineNumber <=LINE15 )
	{
        switch ( Copy_SenseMode )
        {
    		case FALLINNG        : EXTI->FTSR |=  (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
    							   EXTI->RTSR &=~ (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
    							   break ;
    		case RISING          : EXTI->FTSR &=~ (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
						           EXTI->RTSR |=  (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
						           break ;
    	    case FALLINNG_RISING : EXTI->FTSR |=  (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
							       EXTI->RTSR |=  (EXTI_TRIGSRC_MASK << (Copy_LineNumber));
						           break ;
    	default                  : Local_u8ErrorState = ERROR_STATE_NOK ;
        }
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MEXTI_u8InterruptState
 * @brief          : Interrupt State
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @param[in]      : Copy_LineState  --> get option from @EXTI_State_t    enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8InterruptState       ( EXTI_LineNumber_t Copy_LineNumbe , EXTI_State_t Copy_LineState )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_LineNumbe <=LINE15 )
	{
        EXTI->IMR &=~ (EXTI_STATE_MASK << (Copy_LineNumbe));
        EXTI->IMR |=  (Copy_LineState << (Copy_LineNumbe));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MEXTI_u8SoftwareTrigger
 * @brief          : Software Trigger
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SoftwareTrigger  ( EXTI_LineNumber_t Copy_LineNumbe )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_LineNumbe <=LINE15 )
	{
        EXTI->SWIER |=  (EXTI_SOFT_TRIG_MASK << (Copy_LineNumbe));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MEXTI_u8ClearPendingFlag
 * @brief          : Clear Pending Flag
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8ClearPendingFlag  ( EXTI_LineNumber_t Copy_LineNumbe )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_LineNumbe <=LINE15 )
	{
        EXTI->PR =  (EXTI_FLAG_MASK << (Copy_LineNumbe));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MEXTI_u8GetPendingFlag
 * @brief          : Get Pending Flag
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @param[OUT]     : Copy_pu8Pendingstate --> GET state of flag
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8GetPendingFlag  ( EXTI_LineNumber_t Copy_LineNumbe , uint8_t *Copy_pu8Pendingstate )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_LineNumbe <=LINE15 &&  Copy_pu8Pendingstate != NULL )
	{
		*Copy_pu8Pendingstate= ((EXTI->PR >> Copy_LineNumbe )&0b1 );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MEXTI_u8SetCallBack
 * @brief          : Set Call Back
 * @param[in]      : Copy_LineNumber --> get option from @EXTI_LineNumber_t enum
 * @param[in]      : Copy_pfun --> set Call back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SetCallBack      ( EXTI_LineNumber_t Copy_LineNumbe   , void (* Copy_pfun)(void) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_pfun != NULL )
	{
		EXTI_ApfCallBack[Copy_LineNumbe] = Copy_pfun;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/********************************************************* Handlers implementations **************************************************/
/*************************************************************************************************************************************/
void EXTI0_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE0] != NULL )
	{
		 SET_BIT( EXTI->PR , LINE0 );
		 EXTI_ApfCallBack[LINE0]();
	}
}

void EXTI1_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE1] != NULL )
	{
		SET_BIT( EXTI->PR , LINE1 );
		EXTI_ApfCallBack[LINE1]();
	}
}

void EXTI2_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE2] != NULL )
	{
		SET_BIT( EXTI->PR , LINE2 );
	    EXTI_ApfCallBack[LINE2]();
	}
}
void EXTI3_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE3] != NULL )
	{
		SET_BIT( EXTI->PR , LINE3 );
		EXTI_ApfCallBack[LINE3]();
	}
}
void EXTI4_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE4] != NULL )
	{
		SET_BIT( EXTI->PR , LINE4 );
		EXTI_ApfCallBack[LINE4]();
	}
}
void EXTI9_5_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE5] != NULL && EXTI_LINE5_FLAGE == EXTI_LINE_RISING )
	{
		SET_BIT( EXTI->PR , LINE5 );
		EXTI_ApfCallBack[LINE5]();
	}
	if ( EXTI_ApfCallBack[LINE6] != NULL && EXTI_LINE6_FLAGE == EXTI_LINE_RISING )
	{
		SET_BIT( EXTI->PR , LINE6 );
	    EXTI_ApfCallBack[LINE6]();
	}
	if ( EXTI_ApfCallBack[LINE7] != NULL && EXTI_LINE7_FLAGE == EXTI_LINE_RISING )
	{
		SET_BIT( EXTI->PR , LINE7 );
		EXTI_ApfCallBack[LINE7]();
	}
	if ( EXTI_ApfCallBack[LINE8] != NULL && EXTI_LINE8_FLAGE == EXTI_LINE_RISING )
	{
		SET_BIT( EXTI->PR , LINE8 );
		EXTI_ApfCallBack[LINE8]();
	}
	if ( EXTI_ApfCallBack[LINE9] != NULL && EXTI_LINE9_FLAGE == EXTI_LINE_RISING )
	{
		SET_BIT( EXTI->PR , LINE9 );
		EXTI_ApfCallBack[LINE9]();
	}
}
void EXTI15_10_IRQHandler         ( void )
{
	if ( EXTI_ApfCallBack[LINE10] != NULL && EXTI_LINE10_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE10 );
		 EXTI_ApfCallBack[LINE10]();
	}
	if ( EXTI_ApfCallBack[LINE11] != NULL && EXTI_LINE11_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE11 );
		 EXTI_ApfCallBack[LINE11]();
	}
	if ( EXTI_ApfCallBack[LINE12] != NULL && EXTI_LINE12_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE12 );
		 EXTI_ApfCallBack[LINE12]();
	}
	if ( EXTI_ApfCallBack[LINE13] != NULL && EXTI_LINE13_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE13 );
		 EXTI_ApfCallBack[LINE13]();
	}
	if ( EXTI_ApfCallBack[LINE14] != NULL && EXTI_LINE14_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE14 );
		 EXTI_ApfCallBack[LINE14]();
	}
	if ( EXTI_ApfCallBack[LINE15] != NULL && EXTI_LINE15_FLAGE == EXTI_LINE_RISING )
	{
		 SET_BIT( EXTI->PR , LINE15 );
		 EXTI_ApfCallBack[LINE15]();
	}
}
