/**
 ******************************************************************************
 * @file           : USART_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 19/20/2023
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
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void (* USART_ApfCallBack[USART_NUMBERS])(uint8_t) = {NULL,NULL,NULL,NULL,NULL};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MUSART_u8SetConfiguration
 * @brief          : initialization Value of USART Configuration
 * @param[in]      : USARTconfig  --> get option from @USARTconfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MUSART_u8SetConfiguration ( const USARTconfig_t* USARTconfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if (  USARTconfig !=NULL )
	{
		/*************************************************************************************************************************************/
		/********************************************** Clear Flags ********************************************************************/
		MUSART_voidClearFlags(USARTconfig->USARTindex) ;
		/********************************************** Configuration ******************************************************************/
		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_RE_MASK << (USART_CR1_RE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->Receiver << (USART_CR1_RE));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_TE_MASK << (USART_CR1_TE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->Transmitter << (USART_CR1_TE));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_RXNEIE_MASK << (USART_CR1_RXNEIE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->RXNEinterrupt << (USART_CR1_RXNEIE));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_TCIE_MASK << (USART_CR1_TCIE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->TransmetCompleteInterrupt << (USART_CR1_TCIE));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_TXEIE_MASK << (USART_CR1_TXEIE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->TXEinterrupt << (USART_CR1_TXEIE));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_PS_MASK << (USART_CR1_PS));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->ParitySelection << (USART_CR1_PS));

		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_PCE_MASK << (USART_CR1_PCE));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->ParityControl << (USART_CR1_PCE));


		USART_Index[USARTconfig->USARTindex] -> CR1 &=~ (USART_M_MASK << (USART_CR1_M));
		USART_Index[USARTconfig->USARTindex] -> CR1 |=  (USARTconfig->WordLength << (USART_CR1_M));

		USART_Index[USARTconfig->USARTindex] -> CR2 &=~ (USART_STOP_MASK << (USART_CR2_STOP));
		USART_Index[USARTconfig->USARTindex] -> CR2 |=  (USARTconfig->StopBit_t << (USART_CR2_STOP));

		USART_Index[USARTconfig->USARTindex] -> CR3 &=~ (USART_EIE_MASK << (USART_CR3_EIE));
		USART_Index[USARTconfig->USARTindex] -> CR3 |=  (USARTconfig->ErrorTnterrupt << (USART_CR3_EIE));

		USART_Index[USARTconfig->USARTindex] -> CR3 &=~ (USART_DMAR_MASK << (USART_CR3_DMAR));
		USART_Index[USARTconfig->USARTindex] -> CR3 |=  (USARTconfig->DMAresevier << (USART_CR3_DMAR));

		USART_Index[USARTconfig->USARTindex] -> CR3 &=~ (USART_DMAT_MASK << (USART_CR3_DMAT));
		USART_Index[USARTconfig->USARTindex] -> CR3 |=  (USARTconfig->DMAtransmitter << (USART_CR3_DMAT));
		/********************************************** Baud Rate ************************************************************************/
		uint64_t Local_u64Mantissa = ( F_COLCK ) / ( USART_OVER_SAMPLING * USART1_BAUD_RATE ) ;
		uint64_t Local_u64Fraction = ( ( ( F_COLCK * 100 ) / ( USART_OVER_SAMPLING * USART1_BAUD_RATE )  ) % 100 ) * USART_OVER_SAMPLING ;

		if( Local_u64Fraction > USART_MAX_FRAC )
		{
			Local_u64Mantissa += USART_MANTISSA ;
			Local_u64Fraction  = USART_FRACTION ;
		}
		USART_Index[USARTconfig->USARTindex] -> BRR = ( Local_u64Mantissa << USART_BAUD_RATE_ACCESS  ) | ( Local_u64Fraction / 100 ) ;
		/********************************************** Enable ***************************************************************************/
		/*************************************************************************************************************************************/
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8UsartStatus
 * @brief          : USART Status
 * @param[in]      : Copy_USARTindex    --> get option from @USARTindex_t    enum
 * @param[in]      : Copy_UsartStatus   --> get option from @UsartStatus_t   enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MUSART_u8UsartStatus ( USARTindex_t Copy_USARTindex , UsartStatus_t Copy_UsartStatus )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (  1  )
	{
		USART_Index[Copy_USARTindex] -> CR1 &=~ (USART_USART_MASK   << (USART_CR1_UE));
		USART_Index[Copy_USARTindex] -> CR1 |=  (Copy_UsartStatus   << (USART_CR1_UE));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8RXinterruptStatus
 * @brief          : Receive interrupt Status
 * @param[in]      : Copy_USARTindex    --> get option from @USARTindex_t    enum
 * @param[in]      : Copy_RXNEinterrupt --> get option from @RXNEinterrupt_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MUSART_u8RXinterruptStatus ( USARTindex_t Copy_USARTindex , RXNEinterrupt_t Copy_RXNEinterrupt )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (  1  )
	{
		USART_Index[Copy_USARTindex] -> CR1 &=~ (USART_RXNEIE_MASK  << (USART_CR1_RXNEIE));
		USART_Index[Copy_USARTindex] -> CR1 |=  (Copy_RXNEinterrupt << (USART_CR1_RXNEIE));
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/****************************************************************************************************/
/*********************************** Receive ********************************************************/
/****************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MUSART_u8ReceiveCharSynch
 * @brief          : Receive Char Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pu8DataChar  --> Set Address of Data Char
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveCharSynch     ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataChar  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu8DataChar != NULL )
	{
		//CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE );
	    while ( USART_SR_RXNE_DOWN_MASK == GET_BIT ( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE ) )  ;
	    *Copy_pu8DataChar = ( USART_Index[Copy_USARTindex] -> DR )  ;
		CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE );

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8ReceiveCharNonBlocking
 * @brief          : Receive Char Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pu8DataChar  --> Set Address of Data Char
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveCharNonBlocking     ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataChar  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	uint32_t Local_u32TimeOutCounter = 0 ;
	if ( Copy_pu8DataChar != NULL )
	{
		CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE );
	    while ( (USART_SR_RXNE_DOWN_MASK == GET_BIT ( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE )) && (Local_u32TimeOutCounter < 500000) )
	    {
			Local_u32TimeOutCounter++;
	    }
		if(Local_u32TimeOutCounter<500000)
		{
		    *Copy_pu8DataChar = ( USART_Index[Copy_USARTindex] -> DR )  ;
			//CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_RXNE );
		}
		else
		{
			Local_u8ErrorState = ERROR_STATE_TIME_OUT ;
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
 * @fn             : MUSART_u8ReceiveArraySynch
 * @brief          : Receive Char Array Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pu8DataChar  --> Set Address of Data Char Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveStringSynch  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	uint8_t Local_u8Flag = 0 ;
	if ( Copy_pu8DataArray != NULL )
	{
	      for ( uint8_t Local_u8Counter = 0 ; Local_u8Flag == 0 ; Local_u8Counter++ )
		  {
	    	   MUSART_u8ReceiveCharSynch( Copy_USARTindex , & (Copy_pu8DataArray[Local_u8Counter]) );
	    	   if ( Copy_pu8DataArray[Local_u8Counter] == '\0' )
	    	   {
	    		   Local_u8Flag = 1 ;
	    	   }
		   }
	       Local_u8Flag = 0 ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8ReceiveArraySynch
 * @brief          : Receive Char Array Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pu8DataChar  --> Set Address of Data Char Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveArraySynch  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  , uint8_t Copy_u8Size  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu8DataArray != NULL )
	{
	   for (uint8_t Local_u8Counter = 0 ; Local_u8Counter < Copy_u8Size ; Local_u8Counter++ )
	   {
    	   MUSART_u8ReceiveCharSynch( Copy_USARTindex , & (Copy_pu8DataArray[Local_u8Counter]) );
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
 * @fn             : MUSART_u8ReceiveArrayNonBlocking
 * @brief          : Receive Char Array Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pu8DataChar  --> Set Address of Data Char Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveArrayNonBlocking  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  , uint8_t Copy_u8Size  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	uint8_t Local_u8StepErrorState = ERROR_STATE_OK ;

	if ( Copy_pu8DataArray != NULL )
	{
	   for (uint8_t Local_u8Counter = 0 ; Local_u8Counter < Copy_u8Size ; Local_u8Counter++ )
	   {
		   Local_u8StepErrorState = MUSART_u8ReceiveCharNonBlocking( Copy_USARTindex , & (Copy_pu8DataArray[Local_u8Counter]) );
		   if ( Local_u8StepErrorState == ERROR_STATE_TIME_OUT )
		   {
			   Local_u8ErrorState = ERROR_STATE_TIME_OUT ;
			   break;
		   }
	   }
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/****************************************************************************************************/
/*********************************** Transmit *******************************************************/
/****************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MUSART_u8TransmitCharSynch
 * @brief          : Transmit Char Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_u8DataChar  --> Set Data Char
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8TransmitCharSynch     ( USARTindex_t Copy_USARTindex , uint8_t  Copy_u8DataChar  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{
		CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_TC );
		USART_Index[Copy_USARTindex] -> DR = Copy_u8DataChar ;
		while ( USART_SR_TC_MASK == GET_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_TC ) )  ;
		CLR_BIT( USART_Index[Copy_USARTindex] -> SR , USART_SR_TC );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8TransmitStringSynch
 * @brief          : Transmit Char Array Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_u8DataChar  --> Set Data Char Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MUSART_u8TransmitStringSynch  ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu8DataArray != NULL )
	{
       for (uint8_t Local_u8Counter = 0 ; Copy_pu8DataArray[Local_u8Counter] != '\0' ; Local_u8Counter++ )
	   {
    	   MUSART_u8TransmitCharSynch( Copy_USARTindex , Copy_pu8DataArray[Local_u8Counter]  );
	   }
	   MUSART_u8TransmitCharSynch( Copy_USARTindex , '\0'  );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MUSART_u8TransmitArraySynch
 * @brief          : Transmit Char Array Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_u8DataChar  --> Set Data Char Array
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MUSART_u8TransmitArraySynch  ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray , uint8_t Copy_u8Size )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu8DataArray != NULL )
	{
       for (uint8_t Local_u8Counter = 0 ; Local_u8Counter < Copy_u8Size ; Local_u8Counter++ )
	   {
    	   MUSART_u8TransmitCharSynch( Copy_USARTindex , Copy_pu8DataArray[Local_u8Counter]  );
	   }
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MUSART_u32GetDRAddress
 * @brief          : Get DR Address
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @retval         : Address  DR
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint32_t*   MUSART_u32GetDRAddress( USARTindex_t Copy_USARTindex )
{
	return &USART_Index[Copy_USARTindex] -> DR ;
}

/**
 ******************************************************************************
 * @fn             : MUSART1_voidClearFlags
 * @brief          : Clear all Flags
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void   MUSART_voidClearFlags( USARTindex_t Copy_USARTindex )
{
	USART_Index[Copy_USARTindex] -> SR = USART_SR_MASK ;
}

/**
 ******************************************************************************
 * @fn             : MUSART_u8ReceiveCharNonSynch
 * @brief          : Receive Char Non Synchronization
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pFun  --> Set Address of Call back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8ReceiveCharNonSynch     ( USARTindex_t Copy_USARTindex , void (*Copy_pFun) (uint8_t) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (Copy_pFun!= NULL  )
	{
		USART_ApfCallBack[Copy_USARTindex] = Copy_pFun;
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
void USART1_IRQHandler(void)
{
	if (  USART_ApfCallBack[USART_1] != NULL )
	{
		USART_ApfCallBack[USART_1](USART_Index[USART_1] -> DR);
		MUSART_voidClearFlags(USART_1);

	}

}
void USART2_IRQHandler(void)
{
	if (  USART_ApfCallBack[USART_2] != NULL )
	{
		USART_ApfCallBack[USART_2](USART_Index[USART_2] -> DR);
		MUSART_voidClearFlags(USART_2);

	}

}
void USART3_IRQHandler(void)
{
	if (  USART_ApfCallBack[USART_3] != NULL )
	{
		USART_ApfCallBack[USART_3](USART_Index[USART_3] -> DR);
		MUSART_voidClearFlags(USART_3);
	}

}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
