/**
 ******************************************************************************
 * @file           : RCC_program.c
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
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/



/**
 ******************************************************************************
 * @fn             : MRCC_u8SetClockState
 * @brief          : Set Clock State
 * @param[in]      : Copy_ClockType  --> get option from @ClockType_t  enum
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8SetClockState		(  ClockType_t       Copy_ClockType , ClockState_t Copy_ClockState )
{
          uint8_t Local_u8ErrorState = ERROR_STATE_OK;
          if ( Copy_ClockType <= PLL  &&  Copy_ClockState <= ENABLE )
          {
    		  uint32_t Local_u32TimeOut = 0 ;
              switch ( Copy_ClockType )
              {
              	  	  case HSI :  RCC->CR &=~( RCC_CLOCK_STATE_MASK<<(RCC_CR_HSION));
  	  	  	  	  	  	  	  	  RCC->CR |= (Copy_ClockState<<(RCC_CR_HSION));
  	  	  	  	  	  	  	  	  while( (  RCC_CLK_NOT_RDY == (RCC->CR >> RCC_CR_HSIRDY) & 0x1 ) && ( Local_u32TimeOut < RCC_TIME_OUT ) )
  	  	  	  	  	  	  	  	  {
  	  	  	  	  	  	  	  		  Local_u32TimeOut++;
  	  	  	  	  	  	  	  	  }
  	  	  	  	  	  	  	  	  if( Local_u32TimeOut >= RCC_TIME_OUT )
  	  	  	  	  	  	  	  	  {
  	  	  	  	  	  	  	  		  Local_u8ErrorState = ERROR_STATE_NOK;
  	  	  	  	  	  	  	  	  }
  	  	  	  	  	  	  	  	  break;

              	  	  case HSE :  RCC->CR &=~( RCC_CLOCK_STATE_MASK<<(RCC_CR_HSEON));
              	  	  	  	  	  RCC->CR |= (Copy_ClockState<<(RCC_CR_HSEON));
              	  	  	  	  	  while( (  RCC_CLK_NOT_RDY == (RCC->CR >> RCC_CR_HSERD) & 0x1 ) && ( Local_u32TimeOut < RCC_TIME_OUT ) )
              	  	  	  	  	  {
              	  	  	  	  		  	 Local_u32TimeOut++;
              	  	  	  	  	  }
              	  	  	  	  	  if( Local_u32TimeOut >= RCC_TIME_OUT )
              	  	  	  	  	  {
              	  	  	  	  		  	 Local_u8ErrorState = ERROR_STATE_NOK;
              	  	  	  	  	  }
              	  	  	  	  	  break;

              	  	  case PLL :  RCC->CR &=~( RCC_CLOCK_STATE_MASK<<(RCC_CR_PLLON));
              	  	  	  	  	  RCC->CR |= (Copy_ClockState<<(RCC_CR_PLLON));
              	  	  	  	  	  while( (  RCC_CLK_NOT_RDY == (RCC->CR >> RCC_CR_PLLRDY) & 0x1 ) && ( Local_u32TimeOut < RCC_TIME_OUT ) )
              	  	  	  	  	  {
              	  	  	  	  		  Local_u32TimeOut++;
              	  	  	  	  	  }
              	  	  	  	  	  if( Local_u32TimeOut >= RCC_TIME_OUT )
              	  	  	  	  	  {
              	  	  	  	  		  Local_u8ErrorState = ERROR_STATE_NOK;
              	  	  	  	  	  }
              	  	  	  	  	  break;
              	  	  default  :  Local_u8ErrorState = ERROR_STATE_NOK;
              	  	  	  	  	  break;
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
 * @fn             : MRCC_u8SetSystemClock
 * @brief          : Set System Clock
 * @param[in]      : Copy_ClockType  --> get option from @ClockType_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8SetSystemClock		(  ClockType_t       Copy_ClockType  )
{
          uint8_t Local_u8ErrorState = ERROR_STATE_OK;
          if ( Copy_ClockType <= PLL  )
          {
        	  	  RCC->CFGR &=~( RCC_SYS_CLOCK_MASK<<(RCC_CFGR_SW));
	  	  	  	  RCC->CFGR |= ( Copy_ClockType<<(RCC_CFGR_SW));
          }
          else
          {
          	Local_u8ErrorState = ERROR_STATE_NOK;
          }
          return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MRCC_u8HSEConfiguration
 * @brief          : Set HSE Configuration
 * @param[in]      : Copy_HSEConfig  --> get option from @HSEConfig_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8HSEConfiguration   (  HSEConfig_t  Copy_HSEConfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_HSEConfig <= DIV_2 )
	{
		RCC->CFGR &=~( RCC_HSE_CONFIG_MASK<<(RCC_CFGR_PLLXTPRE));
	    RCC->CFGR |= (Copy_HSEConfig<<(RCC_CFGR_PLLXTPRE));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MRCC_u8HSEClockBypassConfiguration
 * @brief          : Set HSE Clock Bypass Configuration
 * @param[in]      : Copy_Bypass --> get option from @HSEBypass_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8HSEClockBypassConfiguration   (  HSEBypass_t  Copy_Bypass  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_Bypass <= BYP )
	{
	  	  RCC->CR &=~( RCC_HSE_BYP_MASK<<(RCC_CR_HSEBYP));
	  	  RCC->CR |= ( Copy_Bypass<<(RCC_CR_HSEBYP));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : MRCC_u8PLLConfiguration
 * @brief          : Set PLL Configuration
 * @param[in]      : Copy_PLLmul    --> get option from @PLLmul_t    enum
 * @param[in]      : Copy_PLLinput  --> get option from @PLLinput_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8PLLConfiguration   (  PLLmul_t  Copy_PLLmul , PLLinput_t Copy_PLLinput )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PLLmul <= MUL_16 &&  Copy_PLLinput <= PLL_HSE )
	{
		RCC->CFGR &=~( RCC_PLL_INPUT_MASK<<(RCC_CFGR_PLLSRC));
		RCC->CFGR |= (Copy_PLLinput<<(RCC_CFGR_PLLSRC));

		RCC->CFGR &=~( RCC_PLL_MUL_MASK<<(RCC_CFGR_PLLMUL));
	    RCC->CFGR |= (Copy_PLLmul<<(RCC_CFGR_PLLMUL));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : MRCC_u8AHBPeripheralsClockState
 * @brief          : Set Clock State on AHB Peripherals
 * @param[in]      : Copy_PerID      --> get option from @AHBperipherals_t  enum
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t      enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8AHBPeripheralsClockState     (  AHBperipherals_t  Copy_PerID , ClockState_t Copy_ClockState )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PerID <= PER_SDIO &&  Copy_ClockState <= ENABLE )
	{
		RCC->AHBENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
		RCC->AHBENR |= (Copy_ClockState)<<(Copy_PerID);
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MRCC_u8APB1PeripheralsClockState
 * @brief          : Set Clock State on APB1 Peripherals
 * @param[in]      : Copy_PerID      --> get option from @APB1peripherals_t enum
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t      enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8APB1PeripheralsClockState    (  APB1peripherals_t Copy_PerID , ClockState_t Copy_ClockState )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PerID <= PER_DAC &&  Copy_ClockState <= ENABLE )
	{
		RCC->APB1ENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
		RCC->APB1ENR |= (Copy_ClockState)<<(Copy_PerID);
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}

/**
 ******************************************************************************
 * @fn             : MRCC_u8APB1PeripheralsClockState
 * @brief          : Set Clock State on APB2 Peripherals
 * @param[in]      : Copy_PerID      --> get option from @APB2peripherals_t enum
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t      enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8APB2PeripheralsClockState    (  APB2peripherals_t Copy_PerID , ClockState_t Copy_ClockState )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_PerID <= PER_TIM11 &&  Copy_ClockState <= ENABLE )
	{
		RCC->APB2ENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
		RCC->APB2ENR |= (Copy_ClockState)<<(Copy_PerID);
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MRCC_u8PeripheralsClockState
 * @brief          : Set Clock State on AHB , APB1 &APB2 Peripherals
 * @param[in]      : Copy_PerID      --> get option from @BUSS_t , @APB1pe   enum
 * @param[in]      : Copy_PerID      --> get option from @AHBperipherals_t , @APB1peripherals_t & @APB2peripherals_t  enum
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t       enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8PeripheralsClockState     (  BUSS_t Copy_Bus , uint8_t  Copy_PerID , ClockState_t Copy_ClockState )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_Bus<=APB2  && Copy_PerID <= PER_DAC &&  Copy_ClockState <= ENABLE )
	{
		switch ( Copy_Bus )
		{
			case AHB :  RCC->AHBENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
					    RCC->AHBENR |= (Copy_ClockState)<<(Copy_PerID);
					    break;
			case APB1 : RCC->APB1ENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
					    RCC->APB1ENR |= (Copy_ClockState)<<(Copy_PerID);
					    break;
			case APB2 : RCC->APB2ENR &=~( RCC_CLOCK_STATE_MASK<<(Copy_PerID));
					    RCC->APB2ENR |= (Copy_ClockState)<<(Copy_PerID);
					    break;
			default  :  Local_u8ErrorState = ERROR_STATE_NOK;
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
 * @fn             : MRCC_u8ClockSecurityState
 * @brief          : Set Clock Security State
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t    enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MRCC_u8ClockSecurityState ( ClockState_t Copy_ClockState )
{
    uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ClockState <= ENABLE )
	{
		 RCC->CR &=~( RCC_CLOCK_STATE_MASK<<(RCC_CR_CSSON));
		 RCC->CR |= (Copy_ClockState<<(RCC_CR_CSSON));

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MRCC_u8ADCPrescelar
 * @brief          : Set ADC Prescelar
 * @param[in]      : Copy_ADCPrescelar --> get option from @ADCPrescelar_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MRCC_u8ADCPrescelar ( ADCPrescelar_t Copy_ADCPrescelar )
{
    uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ADCPrescelar <= PCLK2_DIV_8 )
	{
		RCC->CFGR &=~(RCC_ADC_PRE_MASK<<(RCC_CFGR_ADCPRE));
	    RCC->CFGR |= (Copy_ADCPrescelar<<(RCC_CFGR_ADCPRE));

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}

