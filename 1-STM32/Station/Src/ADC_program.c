/**
 ******************************************************************************
 * @file           : ADC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 19/9/2023
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
#include "stm32f103xx.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void (* ADC_ApfCallBack[ADC_NUMBERS])(void) = {NULL,NULL,NULL};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/

uint8_t  MADC_u8ADCStatus     ( ADCindex_t Copy_ADCindex ,  ADCStatus_t Copy_ADCStatus )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_ADCindex <= ADC_3 && Copy_ADCStatus <= ADC_ENABLE )
	{
		ADC_Index[Copy_ADCindex] -> CR2 &=~ (0b1  << (0)) ;
		ADC_Index[Copy_ADCindex] -> CR2 |=  (Copy_ADCStatus<< (0)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
uint8_t  MADC_u8InterruptEnable      ( ADCindex_t Copy_ADCindex ,  ADCinterrupt_t Copy_ADCinterrupt )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_ADCindex <= ADC_3 && Copy_ADCinterrupt <= JEOCIE )
	{
		ADC_Index[Copy_ADCindex] -> CR1 &=~ (0b1  << (Copy_ADCinterrupt+5)) ;
		ADC_Index[Copy_ADCindex] -> CR1 |=  (1<< (Copy_ADCinterrupt+5)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}

uint8_t  MADC_u8SetRegularSequence       ( ADCindex_t Copy_ADCindex ,  uint8_t Copy_SequenceLength  , uint8_t Copy_ConversionSequenceNumber , uint8_t Copy_ChannelNumber  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_ADCindex <= ADC_3 )
	{
		ADC_Index[Copy_ADCindex] -> CR1 |=  (1<< (8)) ;


		uint8_t Local_u8Reg = 2- (Copy_ConversionSequenceNumber) / 6    ;
		uint8_t Local_u8Bit = (((Copy_ConversionSequenceNumber) % 6)*5)   ;

		ADC_Index[Copy_ADCindex] -> SQR[Local_u8Reg] &=~ (0b11111  << (Local_u8Bit)) ;
		ADC_Index[Copy_ADCindex] -> SQR[Local_u8Reg] |=  (Copy_ChannelNumber<< (Local_u8Bit)) ;


		ADC_Index[Copy_ADCindex] -> SQR[0] &=~ (0b1  << (20)) ;
		ADC_Index[Copy_ADCindex] -> SQR[0] |=  (Copy_SequenceLength<< (20)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
uint8_t  MADC_u8RegularStartConversion  ( ADCindex_t Copy_ADCindex  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_ADCindex <= ADC_3 )
	{
		//ADC_Index[Copy_ADCindex] -> CR2 &=~ (0b1  << (22)) ;
		ADC_Index[Copy_ADCindex] -> CR2 |=  (1    << (22)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
uint8_t  MADC_u8RaedData  ( ADCindex_t Copy_ADCindex , uint16_t* Copy_u16Data )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_ADCindex <= ADC_3 )
	{
		ADC_Index[Copy_ADCindex] -> CR2 |=  (1    << (22)) ;

		//while(0==GET_BIT(ADC_Index[Copy_ADCindex] -> SR,1));
		*Copy_u16Data=ADC_Index[Copy_ADCindex] -> DR ;
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

/*************************************************************************************************************************************/
/********************************************************* Handlers implementations **************************************************/
/*************************************************************************************************************************************/
void ADC1_2_IRQHandler (void)
{
	if (  ADC_ApfCallBack[ADC_1] != NULL )
	{
		//MADC_u8ClearInterruptFlags(ADC_3);
		ADC_ApfCallBack[ADC_1]();
	}
}
void ADC3_IRQHandler (void)
{
	if (  ADC_ApfCallBack[ADC_3] != NULL )
	{
		//MADC_u8ClearInterruptFlags(ADC_3);
		ADC_ApfCallBack[ADC_3]();
	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
