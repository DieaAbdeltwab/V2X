/**
 ******************************************************************************
 * @file           : I2C_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 2 For STM32F446RE Drivers
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
#include "STM32F103xx.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MI2C_u8SetConfiguration
 * @brief          : initialization Value of I2C Configuration
 * @param[in]      : I2Cconfig  --> get option from @I2Cconfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t MI2C_u8SetConfiguration ( const I2Cconfig_t* I2Cconfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if (  I2Cconfig !=NULL )
	{
		I2C_Index[I2Cconfig->I2Cindex]->CR1 |=  (I2C_F_S_MASK<<I2C_CCR_F_S);
		I2C_Index[I2Cconfig->I2Cindex]->CR1 &= ~(I2C_F_S_MASK<<I2C_CCR_F_S);
		uint32_t Local_u16Temp=0 , Local_u16Freq=0 , Local_u16Result=0 ;
		Local_u16Temp=I2C_Index[I2Cconfig->I2Cindex]->CR2;
		Local_u16Temp  &=~ ( I2C_FREQ_MASK  << I2C_CR2_FREQ );
		Local_u16Freq=(P_CLOCK1/1000000);
		Local_u16Temp  |=  ( Local_u16Freq        );
		I2C_Index[I2Cconfig->I2Cindex]->CR2=Local_u16Temp;
		/*****************************************************************************/
		Local_u16Temp=0 ;
		Local_u16Result =(P_CLOCK1/(2*(I2Cconfig->ClockSpeed)));
		Local_u16Temp |=Local_u16Result;
		Local_u16Temp  &=~ ( I2C_F_S_MASK          << I2C_CCR_F_S );
		Local_u16Temp  |=  ( I2Cconfig->MasterMode << I2C_CCR_F_S );
		I2C_Index[I2Cconfig->I2Cindex]->CCR = Local_u16Temp;
		/*****************************************************************************/
		I2C_Index[I2Cconfig->I2Cindex]->TRISE = Local_u16Freq+I2C_TRISE_MASK ;
		/*****************************************************************************/
		Local_u16Temp=0;
		Local_u16Temp  &=~ ( I2C_NOSTRETCH_MASK          << I2C_CR1_NOSTRETCH );
		Local_u16Temp  |=  ( I2Cconfig->Clock_Stretching << I2C_CR1_NOSTRETCH );
		Local_u16Temp  &=~ ( I2C_SMBUS_MASK     << I2C_CR1_SMBUS );
		Local_u16Temp  |=  ( I2Cconfig->I2Cmode << I2C_CR1_SMBUS );
		Local_u16Temp  &=~ ( I2C_ACK_MASK          << I2C_CR1_ACK );
		Local_u16Temp  |=  ( I2Cconfig->Acknowledge << I2C_CR1_ACK );
		Local_u16Temp  &=~ ( I2C_ENGC_MASK          << I2C_CR1_ENGC );
		Local_u16Temp  |=  ( I2Cconfig->GeneralCall << I2C_CR1_ENGC );
		I2C_Index[I2Cconfig->I2Cindex]->CR1 = Local_u16Temp ;
		/*******************************************************************************/
		SET_BIT(I2C_Index[I2Cconfig->I2Cindex]->CR1,I2C_CR1_PE);
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState ;

}

/**
 ******************************************************************************
 * @fn             : MI2C_u8SendSynch
 * @brief          : Send Synchronization Function
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_u16SlaveAddress  --> Set Slave Address
 * @param[in]      : Copy_pu8DataToTransmit--> Get Data To Transmit
 * @param[in]      : Copy_u32DataLenght    --> Set Data Lenght
 * @param[in]      : Copy_StopCondition    --> Get option From @StopCondition_t enum
 * @param[in]      : Copy_StartRepeat      --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MI2C_u8SendSynch    ( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress ,uint8_t *Copy_pu8DataToTransmit , uint32_t Copy_u32DataLenght
		                    , StopCondition_t Copy_StopCondition , StartRepeat_t Copy_StartRepeat)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	volatile uint8_t Local_u8tmp ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_pu8DataToTransmit != NULL && Copy_StopCondition<= STOP_ENABLE && Copy_StartRepeat<= REPEAT_ENABLE )
	{
		 /*********************************************************************************************/
		 for (uint32_t i =0 ; i<=100;i++)
		 {
			 Local_u8tmp=i;
		 }
		 MI2C_u8GenerateStart( Copy_I2Cindex ,FUNC_STATE_ENABLE ,  REPEAT_DISABBLE);
		 while( (MI2C_u8GetFlagStatus( I2C_1 , FLAG_EV5)==FLAG_RESET));
		 MI2C_u8SendAddress(Copy_I2Cindex ,Copy_u16SlaveAddress , TRANSMITTER);
		 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV6)==FLAG_RESET);
         /*********************************************************************************************/
		 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , MASTER_BYTE_TRANSMITTER)==FLAG_RESET);
		 for (uint8_t Local_u8Counter =0 ; Local_u8Counter < Copy_u32DataLenght ; Local_u8Counter++)
		 {
			 I2C_Index[Copy_I2Cindex]->DR = Copy_pu8DataToTransmit[Local_u8Counter];
			 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV8)==FLAG_RESET);
		 }
		 /*********************************************************************************************/
		 if (Copy_StopCondition == STOP_ENABLE )
		 {
			 MI2C_u8GenerateStop(Copy_I2Cindex , STOP_ENABLE );
		 }
		 /*********************************************************************************************/

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MI2C_u8ReceiveSynch
 * @brief          : Receive Synchronization Function
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_u16SlaveAddress  --> Set Slave Address
 * @param[out]     : Copy_pu8DataToReveive --> Get Data To Reveive
 * @param[in]      : Copy_u32DataLenght    --> Set Data Lenght
 * @param[in]      : Copy_StopCondition    --> Get option From @StopCondition_t enum
 * @param[in]      : Copy_StartRepeat      --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MI2C_u8ReceiveSynch ( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress ,uint8_t *Copy_pu8DataToReveive , uint32_t Copy_u32DataLenght
		                    , StopCondition_t Copy_StopCondition , StartRepeat_t Copy_StartRepeat)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	volatile uint8_t Local_u8tmp ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_pu8DataToReveive != NULL && Copy_StopCondition<= STOP_ENABLE && Copy_StartRepeat<= REPEAT_ENABLE )
	{
		 /*********************************************************************************************/
		 MI2C_u8GenerateStart( Copy_I2Cindex ,FUNC_STATE_ENABLE ,  REPEAT_DISABBLE);
		 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV5)==FLAG_RESET);
		 MI2C_u8SendAddress(Copy_I2Cindex ,Copy_u16SlaveAddress , RECEIVER);
		 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV6)==FLAG_RESET);
		 /*********************************************************************************************/
		 MI2C_u8AcknowledgeConfig(Copy_I2Cindex , ACK_ENABLE);
		 /*********************************************************************************************/
		 if (Copy_u32DataLenght >= 1 )
		 {
			 for (uint8_t Local_u8Counter = Copy_u32DataLenght ; Local_u8Counter >= 1 ; Local_u8Counter--)
			 {
				 while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV7)==FLAG_RESET);
				 *Copy_pu8DataToReveive = I2C_Index[Copy_I2Cindex]->DR ;
				  Copy_pu8DataToReveive++;
			 }
			 MI2C_u8AcknowledgeConfig(Copy_I2Cindex , ACK_DISABBLE);

		 }
		 /*********************************************************************************************/
		 if (Copy_StopCondition == STOP_ENABLE )
		 {

			 MI2C_u8GenerateStop(Copy_I2Cindex , STOP_ENABLE );
			 for (uint32_t i =0 ; i<=100;i++)
			 {
				 Local_u8tmp=i;
			 }

		 }
		 /*********************************************************************************************/
		 MI2C_u8AcknowledgeConfig(Copy_I2Cindex , ACK_ENABLE);
		 /*********************************************************************************************/
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
******************************************************************************
* @fn             : MI2C_u8DMArequests
* @brief          : DMA requests
* @param[in]      : Copy_I2Cindex  --> get option from @I2Cindex_t  enum
* @param[in]      : Copy_DMArequests --> get option from @DMArequests_t  enum
* @retval         : ErrorState
******************************************************************************
* @attention
*
*
******************************************************************************
*/

uint8_t MI2C_u8DMArequests (  I2Cindex_t Copy_I2Cindex , DMArequests_t Copy_DMArequests )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_DMArequests <= I2C_DMA_ENABLE )
	{
		if(Copy_DMArequests==I2C_DMA_ENABLE)
		{
			/*
			Bit 11 DMAEN: DMA requests enable
			0: DMA requests disabled
			1: DMA request enabled when TxE=1 or RxNE =1
			*/
			//while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV7)==FLAG_RESET); /* RxNE=1 */
			while( MI2C_u8GetFlagStatus( Copy_I2Cindex , FLAG_EV8)==FLAG_RESET); /* TxE =1 */
		}
		I2C_Index[Copy_I2Cindex]->CR2 &= ~(I2C_DMA_MASK    <<I2C_CR2_DMAEN);
		I2C_Index[Copy_I2Cindex]->CR2 |=  (Copy_DMArequests<<I2C_CR2_DMAEN);
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
 * @fn             : MI2C_u8GetFlagStatus
 * @brief          : Get Flag Status
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_Flag  --> Get option From @Flag_t enum
 * @retval         : FlagStatus_t --> enum
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static FlagStatus_t MI2C_u8GetFlagStatus( I2Cindex_t Copy_I2Cindex , Flag_t Copy_Flag)
{
	volatile uint32_t Local_u32DummyRead;
	FlagStatus_t Local_BitStatus = FLAG_RESET ;
	uint32_t Local_u32Flag1 , Local_u32Flag2 , Local_u32LastEvent ;
	switch (Copy_Flag)
	{
		case FLAG_BUSY :
		{
			if (FLAG_SET ==GET_BIT(I2C_Index[Copy_I2Cindex]->SR2 ,I2C_SR2_BUSY))
			{
				 Local_BitStatus = FLAG_SET ;
			}
			break;
		}
		case FLAG_EV5 :
		{
			if (FLAG_SET ==GET_BIT(I2C_Index[Copy_I2Cindex]->SR1 ,I2C_SR1_SB))
			{
				 Local_BitStatus = FLAG_SET ;
			}
			break;
		}
		case FLAG_EV6 :
		{
			if (FLAG_SET ==GET_BIT(I2C_Index[Copy_I2Cindex]->SR1 ,I2C_SR1_ADDR))
			{
				 Local_BitStatus = FLAG_SET ;
			}
			Local_u32DummyRead = I2C_Index[Copy_I2Cindex]->SR2 ;
			break;
		}
		case MASTER_BYTE_TRANSMITTER :
		{
			Local_u32Flag1 = I2C_Index[Copy_I2Cindex]->SR1 ;
			Local_u32Flag2 = I2C_Index[Copy_I2Cindex]->SR2 ;
			Local_u32Flag2 = Local_u32Flag2 << I2C_BYTE_TRANSMITTER_MASK ;
			Local_u32LastEvent = (Local_u32Flag1 | Local_u32Flag2) & ((uint32_t)I2C_MASTER_BYTE_TRANSMITTER_MASK);
			if ( (Local_u32LastEvent & I2C_EVENT_MASTER_BYTE_TRANSMITTER) == I2C_EVENT_MASTER_BYTE_TRANSMITTER)
			{
				 Local_BitStatus = FLAG_SET ;
			}
		}
		case FLAG_EV8_1 :
		case FLAG_EV8 :
		{
			if (FLAG_SET ==GET_BIT(I2C_Index[Copy_I2Cindex]->SR1 ,I2C_SR1_TxE))
			{
				 Local_BitStatus = FLAG_SET ;
			}
			break;
		}
		case FLAG_EV7 :
		{
			if (FLAG_SET ==GET_BIT(I2C_Index[Copy_I2Cindex]->SR1 ,I2C_SR1_RxNE))
			{
				 Local_BitStatus = FLAG_SET ;
			}
			break;
		}
	}

	return  Local_BitStatus ;

}
/**
 ******************************************************************************
 * @fn             : MI2C_u8GenerateStop
 * @brief          : Generate Stop
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_StopCondition     --> Get option From @StopCondition_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8GenerateStop( I2Cindex_t Copy_I2Cindex , StopCondition_t Copy_StopCondition )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_StopCondition <= STOP_ENABLE )
	{
		I2C_Index[Copy_I2Cindex]->CR1  &=~ ( I2C_STOP_MASK      << I2C_CR1_STOP );
		I2C_Index[Copy_I2Cindex]->CR1  |=  ( Copy_StopCondition << I2C_CR1_STOP );

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MI2C_u8GenerateStart
 * @brief          : Generate Start
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_FunctionalState --> Get option From @FunctionalState_t enum
 * @param[in]      : Copy_StartRepeat     --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8GenerateStart( I2Cindex_t Copy_I2Cindex , FunctionalState_t Copy_FunctionalState , StartRepeat_t Copy_StartRepeat)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_FunctionalState <= FUNC_STATE_ENABLE &&  Copy_StartRepeat <= REPEAT_ENABLE )
	{
		if ( Copy_StartRepeat != REPEAT_ENABLE )
		{
			while(FLAG_SET== MI2C_u8GetFlagStatus( I2C_1 , FLAG_BUSY));
		}
		I2C_Index[Copy_I2Cindex]->CR1  &=~ ( I2C_START_MASK       << I2C_CR1_START );
		I2C_Index[Copy_I2Cindex]->CR1  |=  ( Copy_FunctionalState << I2C_CR1_START );

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}


/**
 ******************************************************************************
 * @fn             : MI2C_u8SendAddress
 * @brief          : Send Address
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_Direction  --> Get option From @Direction_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8SendAddress( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress , Direction_t Copy_Direction )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	 uint16_t Local_u16SlaveAddress = Copy_u16SlaveAddress;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_Direction <= RECEIVER  )
	{
		Local_u16SlaveAddress= (Local_u16SlaveAddress <<I2C_SLAVE_ADDRESS_MASK);
		if ( Copy_Direction ==  RECEIVER )
		{

			Local_u16SlaveAddress |= (I2C_SLAVE_ADDRESS_MASK  <<I2C_SLAVE_ADDRESS_RX_TX_BIT);
		}
		else
		{
			Local_u16SlaveAddress &=~ (I2C_SLAVE_ADDRESS_MASK <<I2C_SLAVE_ADDRESS_RX_TX_BIT);
		}
		I2C_Index[Copy_I2Cindex]->DR = Local_u16SlaveAddress;

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MI2C_u8AcknowledgeConfig
 * @brief          : Acknowledge Config
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Acknowledge_t  --> Set Slave Address
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8AcknowledgeConfig( I2Cindex_t Copy_I2Cindex , Acknowledge_t Copy_Acknowledge )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_I2Cindex <= I2C_2 &&  Copy_Acknowledge <= ACK_ENABLE )
	{
		I2C_Index[Copy_I2Cindex]->CR1  &=~ ( I2C_ACK_MASK     << I2C_CR1_ACK );
		I2C_Index[Copy_I2Cindex]->CR1  |=  ( Copy_Acknowledge << I2C_CR1_ACK );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
