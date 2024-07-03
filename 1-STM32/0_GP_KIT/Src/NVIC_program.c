/**
 ******************************************************************************
 * @file           : NVIC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL (Core Peripherals )
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
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MNVIC_u8EnableInterrupt
 * @brief          : Enable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t   MNVIC_u8EnableInterrupt    ( IntNumber_t Copy_IntNumber )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		uint8_t Local_u8Reg = Copy_IntNumber/NVIC_BIT_REG_ACCESS;
		uint8_t Local_u8Bit = Copy_IntNumber%NVIC_BIT_REG_ACCESS;
		NVIC -> ISER[Local_u8Reg] = ( NVIC_BIT_MASK << Local_u8Bit );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MNVIC_u8DisableInterrupt
 * @brief          : Disable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8DisableInterrupt   ( IntNumber_t Copy_IntNumber )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		uint8_t Local_u8Reg = Copy_IntNumber/NVIC_BIT_REG_ACCESS;
		uint8_t Local_u8Bit = Copy_IntNumber%NVIC_BIT_REG_ACCESS;
		NVIC -> ICER[Local_u8Reg] = ( NVIC_BIT_MASK << Local_u8Bit );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPendingFlag
 * @brief          : Set Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPendingFlag     ( IntNumber_t Copy_IntNumber )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		uint8_t Local_u8Reg = Copy_IntNumber/NVIC_BIT_REG_ACCESS;
		uint8_t Local_u8Bit = Copy_IntNumber%NVIC_BIT_REG_ACCESS;
		NVIC -> ISPR[Local_u8Reg] = ( NVIC_BIT_MASK << Local_u8Bit );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ClearPendingFlag
 * @brief          : Clear Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ClearPendingFlag   ( IntNumber_t Copy_IntNumber )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		uint8_t Local_u8Reg = Copy_IntNumber/NVIC_BIT_REG_ACCESS;
		uint8_t Local_u8Bit = Copy_IntNumber%NVIC_BIT_REG_ACCESS;
		NVIC -> ICPR[Local_u8Reg] = ( NVIC_BIT_MASK << Local_u8Bit );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ReadActiveFlag
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[OUT]     : Copy_pu8StatusActiveFlag --> get Active Flag     uint8_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ReadActiveFlag     ( IntNumber_t Copy_IntNumber ,  uint8_t* Copy_pu8StatusActiveFlag )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		uint8_t Local_u8Reg = Copy_IntNumber/NVIC_BIT_REG_ACCESS;
		uint8_t Local_u8Bit = Copy_IntNumber%NVIC_BIT_REG_ACCESS;
		*Copy_pu8StatusActiveFlag = GET_BIT( NVIC->IABR[Local_u8Reg] , Local_u8Bit );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPriority
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[in]      : Copy_u8GroubSubPriority --> Set Groub Sub Priority uint8_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPriority ( IntNumber_t Copy_IntNumber ,  uint8_t Copy_u8GroubSubPriority )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_IntNumber <= NVIC_DMA2_Channel4_5 )
	{
		NVIC->IPR [Copy_IntNumber] = ( Copy_u8GroubSubPriority << NVIC_BIT_SHIFT_PRIORITY ) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}

    return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


