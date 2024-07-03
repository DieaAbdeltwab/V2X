/**
 ******************************************************************************
 * @file           : CARKIT_program.c
 * @author         : Diea Abdeltwab
 * @layer          : Service
 * @brief          : 
 * @date           : 19/3/2024
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
#include "AFIO_interface.h"
#include "ADC_interface.h"
#include "GPTIMER_interface.h"

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/

/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "TIMERS_interface.h"

#include "CARKIT_interface.h"
#include "CARKIT_config.h"
#include "CARKIT_private.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static float Local_floatAdcVoltage  = 0.0     ;
static float Local_floatInVoltage   = 0.0     ;
static float Local_floatR1          = 30000.0 ;
static float Local_floatR2          = 7500.0  ;
static float Local_floatRefVoltage  = 3.3     ;
static int   Local_intAdcValue      = 0       ;
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
void SCARKIT_voidInit( void )
{
	/*----------------------------------------------------------------*/
	MGPIO_u8SetPinDirection( CARKIT_ADC_VOLT_PIN , INPUT_ANALOG );
	MADC_vInit();
	MADC_vEnable();
	MADC_vSelectChannel    (CARKIT_ADC_VOLT_CHANNEL);
	/*----------------------------------------------------------------*/
	MAFIO_u8TIM3PortRemap  (CARKIT_TIMER_PORT_REMAP);
	MGPIO_u8SetPinDirection(CARKIT_L298N_EN_A_PIN , OUTPUT_SPEED_2MHZ_AFPP );
	STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_R, CARKIT_L298N_FREQ , CARKIT_L298N_INIT_SPEED );
	MGPIO_u8SetPinDirection(CARKIT_L298N_IN_1_PIN , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection(CARKIT_L298N_IN_2_PIN , OUTPUT_SPEED_2MHZ_PP );
	/*----------------------------------------------------------------*/
	MGPIO_u8SetPinDirection(CARKIT_L298N_EN_B_PIN, OUTPUT_SPEED_2MHZ_AFPP );
	STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_L, CARKIT_L298N_FREQ , CARKIT_L298N_INIT_SPEED );
	MGPIO_u8SetPinDirection(CARKIT_L298N_IN_3_PIN, OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection(CARKIT_L298N_IN_4_PIN, OUTPUT_SPEED_2MHZ_PP );
	/*----------------------------------------------------------------*/
}
uint8_t SCARKIT_u8GetVoltageValue( void )
{
	Local_intAdcValue      = MADC_u16ConvertToDigital(CARKIT_ADC_VOLT_CHANNEL);
	Local_floatAdcVoltage  = (Local_intAdcValue * Local_floatRefVoltage) / 4096.0;
	Local_floatInVoltage   = Local_floatAdcVoltage*((Local_floatR1+Local_floatR2)/Local_floatR2);
	return (uint8_t)Local_floatInVoltage ;
}
void SCARKIT_voidCarSpeed ( CarSpeedWheel_t Copy_SpeedWheel , uint8_t Copy_u8SpeedPercentageValue )
{
	if ( Copy_u8SpeedPercentageValue > 90 )
	{
		Copy_u8SpeedPercentageValue = 90 ;
	}
	else if ( Copy_u8SpeedPercentageValue < 30 )
	{
		Copy_u8SpeedPercentageValue = 30 ;
	}
	/*************************************************************************************************/
	if ( Copy_SpeedWheel == SPEED_RIGHT_WHEEL )
	{
		STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_R, 150 , Copy_u8SpeedPercentageValue );
	}
	else if ( Copy_SpeedWheel == SPEED_LEFT_WHEEL )
	{
		STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_L, 150 , Copy_u8SpeedPercentageValue );
	}
	else if ( Copy_SpeedWheel == SPEED_BOTH_WHEEL )
	{
		STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_R, 150 , Copy_u8SpeedPercentageValue );
		STIMERS_u8GeneratePWM  (CARKIT_SPEED_TIMER_CHANNEL_L, 150 , Copy_u8SpeedPercentageValue );
	}
	/*************************************************************************************************/
}
void SCARKIT_voidCarDirection ( CarDirection_t Copy_Direction  )
{
	if ( Copy_Direction == CAR_FORWARD )
	{
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_1_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_2_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_3_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_4_PIN, LOW  );
	}
	else if ( Copy_Direction ==  CAR_LEFT)
	{
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_1_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_2_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_3_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_4_PIN, LOW  );
	}
	else if ( Copy_Direction == CAR_RIGHT )
	{
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_1_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_2_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_3_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_4_PIN, HIGH );
	}
	else if ( Copy_Direction == CAR_BACKWARD )
	{
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_1_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_2_PIN, HIGH );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_3_PIN, LOW  );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_4_PIN, HIGH );
	}
	else if ( Copy_Direction == CAR_STOP )
	{
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_1_PIN, LOW );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_2_PIN, LOW );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_3_PIN, LOW );
		MGPIO_u8SetPinValue(CARKIT_L298N_IN_4_PIN, LOW );
	}
}
/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

