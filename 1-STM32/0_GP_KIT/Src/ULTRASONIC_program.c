/**
 ******************************************************************************
 * @file           : ULTRASONIC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 11/9/2023
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
#include "NVIC_interface.h"
#include "GPTIMER_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"
#include "ULTRASONIC_private.h"
/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "TIMERS_interface.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
uint16_t ULTRASONIC_u16ICValue1;
uint16_t ULTRASONIC_u16ICValue2;
uint16_t ULTRASONIC_u16Time;
uint8_t  ULTRASONIC_u8Flag;
uint8_t  ULTRASONIC_u8DistanceReadyFlag=0;


GPTIMERindex_t ULTRASONIC_TMR			;
Channelindex_t ULTRASONIC_CHANNEL_TMR   ;

Pin_t   ULTRASONIC_TRIGGER_PIN   ;
Pin_t   ULTRASONIC_ECHO_PIN      ;

Port_t  ULTRASONIC_TRIGGER_PORT  ;
Port_t  ULTRASONIC_ECHO_PORT     ;

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : ULTRASONIC_voidConfig
 * @brief          : Initialization of ULTRASONIC With ICU
 * @param[in]      : Copy_TMR             --> Get option from  @GPTIMERindex_t
 * @param[in]      : Copy_ChannelTMR      --> Get option from  @Channelindex_t
 * @param[in]      : Copy_ULTRASONICindex --> Get option from  ULTRASONICindex_t
 * @retval         : void
 ******************************************************************************
 * @attention
 * Configuration STK , NVIC , GPIO And GPTIMER
 *
 ******************************************************************************
 */
void ULTRASONIC_voidConfig   ( GPTIMERindex_t Copy_TMR , Channelindex_t Copy_ChannelTMR , ULTRASONICindex_t Copy_ULTRASONICindex )
{
	ULTRASONIC_TMR  = Copy_TMR        ;

   //MNVIC_u8EnableInterrupt           ( Copy_TMR + 28 );

	switch ( Copy_ULTRASONICindex )
	{
	case ULTRASONIC_1 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_1_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_1_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_1_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_1_ECHO_PORT    ; break;

	case ULTRASONIC_2 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_2_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_2_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_2_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_2_ECHO_PORT    ; break;

	case ULTRASONIC_3 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_3_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_3_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_3_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_3_ECHO_PORT    ; break;

	case ULTRASONIC_4 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_4_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_4_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_4_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_4_ECHO_PORT    ; break;

	}
	 MGPIO_u8SetPinDirection           ( ULTRASONIC_ECHO_PORT    , ULTRASONIC_ECHO_PIN    , INPUT_FLOATING          );
	 MGPIO_u8SetPinDirection           ( ULTRASONIC_TRIGGER_PORT , ULTRASONIC_TRIGGER_PIN , OUTPUT_SPEED_10MHZ_PP   );

	 MGPTIMER_u8SetTriggerEdge         ( Copy_TMR , Copy_ChannelTMR                   , CCP_RISING );
	 MGPTIMER_u8SetPrescaler           ( Copy_TMR , ULTRASONIC_TMR_PRESCALER         );
	 MGPTIMER_u8SetChannelInput        ( Copy_TMR , Copy_ChannelTMR                   , CCS_TI1    );
	 MGPTIMER_u8SetAutoReload          ( Copy_TMR , ULTRASONIC_AUTO_RELOAD_INT_VALUE );
	 MGPTIMER_u8SetCallBack            ( Copy_TMR , ULTRASONIC_voidEdgeProcessing    );
	 MGPTIMER_u8CounterStatus          ( Copy_TMR , COUNTER_ENABLE                   );
}
/**
 ******************************************************************************
 * @fn             : ULTRASONIC_voidGetDistance
 * @brief          : Get Distance
 * @param[in]      : Copy_ULTRASONICindex --> Get option from  ULTRASONICindex_t
 * @param[out]     : Copy_pu16Distance    --> Get Distance Value
 * @retval         : void
 ******************************************************************************
 * @attention
 * Trigger  ULTRASONIC then Calculate Distance
 *
 ******************************************************************************
 */
void ULTRASONIC_voidGetDistance( ULTRASONICindex_t Copy_ULTRASONICindex , uint16_t *Copy_pu16DistanceValue )
{
	ULTRASONIC_u8DistanceReadyFlag = 0;
	ULTRASONIC_CHANNEL_TMR  = Copy_ULTRASONICindex  ;

	MGPTIMER_u8CompareInterruptStatus ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , CCIE_ENABLE );

	ULTRASONIC_voidTrigger( Copy_ULTRASONICindex );
	while(ULTRASONIC_u8DistanceReadyFlag==0);
	*Copy_pu16DistanceValue = ULTRASONIC_u16Time * ULTRASONIC_DISTANCE_EQ  ;

}
/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
static void ULTRASONIC_voidTrigger         ( ULTRASONICindex_t Copy_ULTRASONICindex )
{
	switch ( Copy_ULTRASONICindex )
	{
	case ULTRASONIC_1 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_1_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_1_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_1_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_1_ECHO_PORT    ; break;

	case ULTRASONIC_2 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_2_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_2_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_2_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_2_ECHO_PORT    ; break;

	case ULTRASONIC_3 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_3_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_3_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_3_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_3_ECHO_PORT    ; break;

	case ULTRASONIC_4 :  ULTRASONIC_TRIGGER_PIN  = ULTRASONIC_4_TRIGGER_PIN  ;
						 ULTRASONIC_ECHO_PIN     = ULTRASONIC_4_ECHO_PIN     ;
						 ULTRASONIC_TRIGGER_PORT = ULTRASONIC_4_TRIGGER_PORT ;
						 ULTRASONIC_ECHO_PORT    = ULTRASONIC_4_ECHO_PORT    ; break;

	}
	MGPTIMER_u8ClearCounter(ULTRASONIC_TMR);
	MGPIO_u8SetPinValue( ULTRASONIC_TRIGGER_PORT ,  ULTRASONIC_TRIGGER_PIN , HIGH);
	STIMERS_voidDelayUS( ULTRASONIC_TRIGGER_TIME );
	MGPIO_u8SetPinValue( ULTRASONIC_TRIGGER_PORT ,  ULTRASONIC_TRIGGER_PIN , LOW );
}

static void ULTRASONIC_voidEdgeProcessing  ( void )
{
	if (ULTRASONIC_u8Flag == 0)
	{
		MGPTIMER_u8GetCompareValue ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , &ULTRASONIC_u16ICValue1 );
		ULTRASONIC_u8Flag = 1;
		MGPTIMER_u8SetTriggerEdge  ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , CCP_FALLING );
	}
	else if(ULTRASONIC_u8Flag == 1)
	{
		MGPTIMER_u8GetCompareValue ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , &ULTRASONIC_u16ICValue2 );
		MGPTIMER_u8ClearCounter    ( ULTRASONIC_TMR );
		ULTRASONIC_u8Flag = 0;
		ULTRASONIC_u16Time = ULTRASONIC_u16ICValue2 - ULTRASONIC_u16ICValue1;
		MGPTIMER_u8SetTriggerEdge  ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , CCP_RISING );
	    MGPTIMER_u8CompareInterruptStatus ( ULTRASONIC_TMR , ULTRASONIC_CHANNEL_TMR , CCIE_DISABLE );
		MGPTIMER_u8ClearCounter(ULTRASONIC_TMR);
		ULTRASONIC_u8DistanceReadyFlag = 1 ;
	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

