/**
 ******************************************************************************
 * @file           : GPIO_program.c
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
#include "stm32f103xx.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MGPIO_u8PinInit
 * @brief          : initialization Value of Pin
 * @param[in]      : PinConfig  --> init Value of Pin from @PinConfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8PinInit ( const PinConfig_t* PinConfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( PinConfig->Port <= PORTG && PinConfig->PinNum <= PIN15 && PinConfig->Mode <= OUTPUT_SPEED_50MHZ && PinConfig->Outputmode <= AF_OPEN_DRAIN && PinConfig->Inputmode <= PULL_UP_DOWEN )
	{
		uint8_t Local_u8Reg = (PinConfig->PinNum)/CNF_PIN_ACCSESS ;
		uint8_t Local_u8Bit = (((PinConfig->PinNum) * MODE_PIN_ACCSESS) + 2) ;
		(GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) &=~ (CR_MASK << (PinConfig->PinNum) * MODE_PIN_ACCSESS );
	    (GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) |=  (PinConfig->Mode << (PinConfig->PinNum) * MODE_PIN_ACCSESS );
		if ( PinConfig->Mode == INPUT )
		{
			  (GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) &=~ (CR_MASK << (Local_u8Bit)) ;
			  (GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) |=  (PinConfig->Inputmode << (Local_u8Bit)) ;
		}
		else
		{
			  (GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) &=~ (CR_MASK << (Local_u8Bit)) ;
			  (GPIO_Ports[PinConfig->Port]->CR[Local_u8Reg]) |=  (PinConfig->Outputmode << (Local_u8Bit)) ;
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}

/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPinDirection
 * @brief          : Set Pin Direction
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[in]      : Copy_Mode   --> get option from @PinPortMode_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPinDirection ( Port_t Copy_PortID , Pin_t Copy_PinID , PinPortMode_t Copy_Mode    )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID<=PORTG && Copy_PinID<=PIN15  )
	{
		uint8_t Local_u8Reg = (Copy_PinID)/CNF_PIN_ACCSESS ;
		GPIO_Ports[Copy_PortID]->CR[Local_u8Reg]  &=~ ( ( MODER_MASK) << ( ( Copy_PinID % CNF_PIN_ACCSESS ) * MODE_PIN_ACCSESS ) );
		GPIO_Ports[Copy_PortID]->CR[Local_u8Reg]  |=  ( ( Copy_Mode ) << ( ( Copy_PinID % CNF_PIN_ACCSESS ) * MODE_PIN_ACCSESS ) );
	}
	else
	{
		    Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPortDirection
 * @brief          : Set Port Direction
 * @param[in]      : Copy_PortID   --> get option from @Port_t         enum
 * @param[in]      : Copy_Position --> get option from @PortPosition_t enum
 * @param[in]      : Copy_Mode     --> get option from @PinPortMode_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPortDirection ( Port_t Copy_PortID , PortPosition_t Copy_Position , PinPortMode_t Copy_Mode       )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID <= PORTG && Copy_Position <= PORT_HIGH &&  Copy_Position <= PORT_HIGH )
	{
			GPIO_Ports[Copy_PortID]->CR[Copy_Position] = ( MODE_PORT_MASK * Copy_Mode ) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPinValue
 * @brief          : Set Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[in]      : Copy_Value  --> get option from @PinValue_t     enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPinValue     ( Port_t Copy_PortID , Pin_t Copy_PinID , PinValue_t Copy_Value   )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID <= PORTG && Copy_PinID <= PIN15 )
	{
		GPIO_Ports[Copy_PortID]->ODR &=~ (PIN_MASK << (Copy_PinID)) ;
		GPIO_Ports[Copy_PortID]->ODR |=  (Copy_Value<< (Copy_PinID)) ;
		/*
		if ( Copy_Value == LOW)
		{
			GPIO_Ports[Copy_PortID]->BRR  = (0b1 << (Copy_PinID)  );
		}
		else if ( Copy_Value == HIGH)
		{
			GPIO_Ports[Copy_PortID]->BSRR =  (0b1 << (Copy_PinID)  );
		}
		else
		{
			Local_u8ErrorState = ERROR_STATE_NOK;
		}*/
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}


/**
 ******************************************************************************
 * @fn             : MGPIO_u8GetPinValue
 * @brief          : Get Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[out]     : Copy_Value  --> Set value in Copy_pu8Result     uint8_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t  MGPIO_u8GetPinValue    ( Port_t Copy_PortID , Pin_t Copy_PinID , uint8_t *Copy_pu8Result )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID <= PORTG && Copy_PinID <= PIN15 && Copy_pu8Result!=NULL )
	{
		*Copy_pu8Result = ( (GPIO_Ports[Copy_PortID]->IDR >> Copy_PinID) & PIN_MASK );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MGPIO_u8TogPinValue
 * @brief          : TOG Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8TogPinValue     ( Port_t Copy_PortID , Pin_t Copy_PinID  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID <= PORTG && Copy_PinID <= PIN15 )
	{
		GPIO_Ports[Copy_PortID]->ODR ^= PIN_MASK<<Copy_PinID ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}

/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPortValue
 * @brief          : Set Port Value
 * @param[in]      : Copy_PortID --> get option from @Port_t            enum
 * @param[in]      : Copy_Position  --> get option from @PortPosition_t enum
 * @param[in]      : Copy_u16Value  --> Set Value in Copy_u16Value      uint16_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPortValue     ( Port_t Copy_PortID , PortPosition_t Copy_Position , uint16_t Copy_u16Value    )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PortID <= PORTG )
	{

	     if   ( Copy_Position == PORT_LOW  )
	     {
	    	 GPIO_Ports[Copy_PortID]->ODR = (GPIO_Ports[Copy_PortID]->ODR & PORT_POSITION_LOW_MASK ) | ( (uint8_t)Copy_u16Value ) ;
	     }
	     else if ( Copy_Position == PORT_HIGH )
	     {
	    	 GPIO_Ports[Copy_PortID]->ODR = (GPIO_Ports[Copy_PortID]->ODR & PORT_POSITION_HIGH_MASK ) | (           Copy_u16Value ) ;
	     }
	 	else
	 	{
	 		Local_u8ErrorState = ERROR_STATE_NOK;
	 	}

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
