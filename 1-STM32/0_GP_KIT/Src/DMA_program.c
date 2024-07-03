/**
 ******************************************************************************
 * @file           : DMA_program.c
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
#include"DMA_INTERFACE.h"
#include"DMA_private.h"
#include"DMA_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void ( *DMA_ApfChannelCallBack[7] )( void )= {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MDMA_u8SetConfiguration
 * @brief          : initialization Value of DMA Configuration
 * @param[in]      : DMAconfig  --> get option from @PinConfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MDMA_u8SetConfiguration ( const DMAconfig_t* DMAconfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if (  DMAconfig->ChannelIndex <= DMA_CHANNEL7   && DMAconfig->Mode <= DMA_ENABLE_CIRCULAR && DMAconfig->PerINC <= DMA_INCREMENT_ENABLE
	   && DMAconfig->MemINC <= DMA_INCREMENT_ENABLE && DMAconfig->MemSize <= DMA_SIZE_WORD    && DMAconfig->PerSize <= DMA_SIZE_WORD    && DMAconfig->ChannelPriority <= DMA_VERY_HIGH)
	{
		/********************************** Disable DMA ***********************************************************/
		CLR_BIT( DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR , DMA_CCR_DMA_ENABLE );
		while( 1 == GET_BIT(  DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR , DMA_CCR_DMA_ENABLE ) );
		MDMA_u8ClearFlag( DMAconfig->ChannelIndex  , DMA_GIF  );
		MDMA_u8ClearFlag( DMAconfig->ChannelIndex  , DMA_TCIF );
		MDMA_u8ClearFlag( DMAconfig->ChannelIndex  , DMA_HTIF );
		MDMA_u8ClearFlag( DMAconfig->ChannelIndex  , DMA_TEIF );
		/********************************** CHANNEL PRIORITY *****************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_PRIORITY_MASK << (DMA_CCR_PRIORITY));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->ChannelPriority << (DMA_CCR_PRIORITY));
		/********************************** MEMORY SIZE **********************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_SIZE_MASK << (DMA_CCR_MEMORY_SIZE));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->PerSize << (DMA_CCR_MEMORY_SIZE));
		/********************************** PERIPHERAL SIZE ******************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_SIZE_MASK << (DMA_CCR_PERIPHERAL_SIZE));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->MemSize << (DMA_CCR_PERIPHERAL_SIZE));
		/********************************** MEMORY Increment ******************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_INCREMENT_MASK << (DMA_CCR_MEMORY_INCREMENT));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->MemINC << (DMA_CCR_MEMORY_INCREMENT));
		/********************************** PERIPHERAL Increment **************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_INCREMENT_MASK << (DMA_CCR_PERIPHERAL_INCREMENT));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->PerINC << (DMA_CCR_PERIPHERAL_INCREMENT));
		/********************************** DMA MODE ***************************************************************/
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR &=~ (DMA_MODE_MASK << (DMA_CCR_MODE));
		DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR |=  (DMAconfig->Mode << (DMA_CCR_MODE));
		/********************************** Direction **************************************************************/
		switch ( DMAconfig->Direction )
		{
	 	    case DMA_MEM_TO_MEM               :   SET_BIT( DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR , DMA_CCR_MEM_TO_MEM )   ;  break ;
		    case DMA_PREI_TO_MEM              :   CLR_BIT( DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR , DMA_CCR_PREI_TO_MEM  ) ;  break ;
		    case DMA_MEM_TO_PERI              :   SET_BIT( DMA->CHANNEL[ DMAconfig->ChannelIndex ].CCR , DMA_CCR_PREI_TO_MEM  ) ;  break ;
		    default	                          :   Local_u8ErrorState = ERROR_STATE_NOK                                          ;  break ;
		}
		/***********************************************************************************************************/
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MDMA_u8Enable
 * @brief          : Enable DMA
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MDMA_u8Enable( Channel_t Copy_ChannelIndex )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <= DMA_CHANNEL7 )
	{
		MDMA_u8ClearFlag( Copy_ChannelIndex , DMA_GIF  );
		MDMA_u8ClearFlag( Copy_ChannelIndex , DMA_TCIF );
		MDMA_u8ClearFlag( Copy_ChannelIndex , DMA_HTIF );
		MDMA_u8ClearFlag( Copy_ChannelIndex , DMA_TEIF );
	    SET_BIT( DMA->CHANNEL[ Copy_ChannelIndex ].CCR , DMA_CCR_DMA_ENABLE );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MDMA_u8Disable
 * @brief          : Disable DMA
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MDMA_u8Disable( Channel_t Copy_ChannelIndex )
{

	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <=DMA_CHANNEL7 )
	{
		 CLR_BIT( DMA->CHANNEL[ Copy_ChannelIndex ].CCR , DMA_CCR_DMA_ENABLE );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MDMA_u8InterruptEnable
 * @brief          : Interrupt Enable
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @param[in]      : Copy_INTSource     --> get option from @InterruptEnable_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MDMA_u8InterruptEnable( Channel_t Copy_ChannelIndex , InterruptEnable_t Copy_INTSource )
{

	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <=DMA_CHANNEL7 &&  Copy_INTSource <= DMA_TEIE )
	{
	     SET_BIT( DMA->CHANNEL[ Copy_ChannelIndex ].CCR , Copy_INTSource );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MDMA_u8ChannelStart
 * @brief          : Channel Start
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @param[in]      : Copy_pu32PeripheralAddress --> Set Peripheral Address
 * @param[in]      : Copy_pu32PeripheralAddress --> Set Memory Address
 * @param[in]      : Copy_pu32PeripheralAddress --> Set Block Length
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MDMA_u8ChannelStart ( Channel_t Copy_ChannelIndex , uint32_t * Copy_pu32PeripheralAddress , uint32_t * Copy_pu32MemoryAddress , uint16_t Copy_u16BlockLength )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <=DMA_CHANNEL7 &&  Copy_pu32PeripheralAddress != NULL &&  Copy_pu32MemoryAddress != NULL  )
	{
		CLR_BIT( DMA->CHANNEL[ Copy_ChannelIndex ].CCR , DMA_CCR_DMA_ENABLE );
		DMA->CHANNEL[ Copy_ChannelIndex ].CPAR  = (uint32_t)Copy_pu32PeripheralAddress ;
		DMA->CHANNEL[ Copy_ChannelIndex ].CMAR  = (uint32_t)Copy_pu32MemoryAddress ;
		DMA->CHANNEL[ Copy_ChannelIndex ].CNDTR =  Copy_u16BlockLength ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MDMA_u8SetCallBack
 * @brief          : Set Call Back
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @param[in]      : Copy_pfun --> Set Call Back Function Address
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MDMA_u8SetCallBack      ( Channel_t Copy_ChannelIndex , void (* Copy_pfun)(void) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <= DMA_CHANNEL7 && Copy_pfun != NULL )
	{
		 DMA_ApfChannelCallBack[Copy_ChannelIndex] = Copy_pfun;
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
/**
 ******************************************************************************
 * @fn             : MDMA_u8ClearFlag
 * @brief          : Clear Flag
 * @param[in]      : Copy_ChannelIndex  --> get option from @Channel_t  enum
 * @param[in]      : Copy_Flag  --> get option from @Flags_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t  MDMA_u8ClearFlag( Channel_t Copy_ChannelIndex , Flags_t Copy_Flag )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_ChannelIndex <= DMA_CHANNEL7 &&  Copy_Flag <= DMA_TEIF )
	{
		Copy_ChannelIndex *= DMA_FLAG_BIT_ACCESS ;
	    DMA->IFCR  |= DMA_FLAG_MASK << (Copy_ChannelIndex + Copy_Flag) ;
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
void DMA1_Channel1_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL1 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL1 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL1 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL1 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL1] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL1]();

	}

}
void DMA1_Channel2_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL2 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL2 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL2 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL2 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL2] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL2]();
	}

}
void DMA1_Channel3_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL3 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL3 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL3 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL3 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL3] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL3]();
	}

}
void DMA1_Channel4_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL4 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL4 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL4 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL4 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL4] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL4]();
	}

}
void DMA1_Channel5_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL5 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL5 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL5 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL5 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL5] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL5]();
	}

}
void DMA1_Channel6_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL6 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL6 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL6 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL6 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL6] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL6]();
	}

}
void DMA1_Channel7_IRQHandler(void)
{
	MDMA_u8ClearFlag( DMA_CHANNEL7 , DMA_GIF  );
	MDMA_u8ClearFlag( DMA_CHANNEL7 , DMA_TCIF );
	MDMA_u8ClearFlag( DMA_CHANNEL7 , DMA_HTIF );
	MDMA_u8ClearFlag( DMA_CHANNEL7 , DMA_TEIF );
	if ( DMA_ApfChannelCallBack[DMA_CHANNEL7] != NULL )
	{
		 DMA_ApfChannelCallBack[DMA_CHANNEL7]();
	}

}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
