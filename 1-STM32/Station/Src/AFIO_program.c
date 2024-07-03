/**
 ******************************************************************************
 * @file           : AFIO_program.c
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
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/

/**
 ******************************************************************************
 * @fn             : MAFIO_u8PortRemap
 * @brief          : Remap EXTI line
 * @param[in]      : Copy_Config --> init Value of Pin from @EXTI_config_t struct
 * @param[in]      : Copy_PortMap --> init Value of Pin from @AFIO_PortMap_t struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t   MAFIO_u8PortRemap ( AFIO_LineNumber_t Copy_LineNumber , AFIO_PortMap_t Copy_PortMap )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_LineNumber <= AFIO_LINE15 &&  Copy_PortMap <= AFIO_Port_G )
	{
		uint8_t Local_u8Reg  = Copy_LineNumber / AFIO_PORT_REMAP_ACCESS ;
		uint8_t Local_u8Line = Copy_LineNumber % AFIO_PORT_REMAP_ACCESS ;
		AFIO -> EXTICR[ Local_u8Reg ] &=~ ( ( AFIO_PORT_REMAP_MASK ) << ( Local_u8Line * AFIO_PORT_REMAP_ACCESS ) ) ;
		AFIO -> EXTICR[ Local_u8Reg ] |=  ( ( Copy_PortMap ) << ( Local_u8Line * AFIO_PORT_REMAP_ACCESS ) ) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}


