/**
 ******************************************************************************
 * @file           : SPI_interface.h
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
#ifndef  SPI_INTERFACE_H
#define  SPI_INTERFACE_H
/******************************************************************************/
/************************ @SPIindex_t *****************************************/
/******************************************************************************/
typedef enum{
			SPI_1   =0,
			SPI_2     ,
			SPI_3
}SPIindex_t;
/******************************************************************************/
/************************ @ClockPhase *****************************************/
/******************************************************************************/
typedef enum{
			LEADING_CAPTURE       =0,
		    LEADING_SETUP

}ClockPhase_t;
/******************************************************************************/
/************************ @ClockPolarity_t ************************************/
/******************************************************************************/
typedef enum{
			LEADING_RISING       =0,
			LEADING_FALLING

}ClockPolarity_t;
/******************************************************************************/
/************************ @SPI_MCUstate_t *************************************/
/******************************************************************************/
typedef enum{
			SLAVE       =0,
			MASTER

}SPI_MCUstate_t;
/******************************************************************************/
/************************ @BaudRate_t *****************************************/
/******************************************************************************/
typedef enum{
			F_CLK_DIV_2           =0,
			F_CLK_DIV_4             ,
			F_CLK_DIV_8             ,
			F_CLK_DIV_16            ,
			F_CLK_DIV_32            ,
			F_CLK_DIV_64            ,
			F_CLK_DIV_128           ,
			F_CLK_DIV_256           ,

}BaudRate_t;
/******************************************************************************/
/************************ @FrameFormat_t **************************************/
/******************************************************************************/
typedef enum{
			MSB       =0,
			LSB

}FrameFormat_t;
/******************************************************************************/
/************************ @InternalSlaveSelect_t ******************************/
/******************************************************************************/
typedef enum{
			SELECT_ZERO        =0,
			SELECT_ONE
}InternalSlaveSelect_t;
/******************************************************************************/
/************************ @SoftwareSlaveManagment_t ***************************/
/******************************************************************************/
typedef enum{
			MANAGMENT_DISABLE        =0,
			MANAGMENT_ENABLE
}SoftwareSlaveManagment_t;
/******************************************************************************/
/************************ @ReceiveOnly_t **************************************/
/******************************************************************************/
typedef enum{
			FULL_DUPLEX            =0,
			OUTPUT_DISABLED
}ReceiveOnly_t;
/******************************************************************************/
/************************ @DataFrame_t ****************************************/
/******************************************************************************/
typedef enum{
			FORMAT_8_BIT           =0,
			FORMAT_16_BIT
}DataFrame_t;
/******************************************************************************/
/************************ @RXDMA_t ********************************************/
/******************************************************************************/
typedef enum{
			RX_DMA_DISABLE           =0,
			RX_DMA_ENABLE
}RXDMA_t;
/******************************************************************************/
/************************ @TXDMA_t ********************************************/
/******************************************************************************/
typedef enum{
			TX_DMA_DISABLE           =0,
			TX_DMA_ENABLE
}TXDMA_t;
/******************************************************************************/
/************************ @SSoutput_t *****************************************/
/******************************************************************************/
typedef enum{
			SS_OUTPUT_DISABLE           =0,
			SS_OUTPUT_ENABLE
}SSoutput_t;
/******************************************************************************/
/************************ @RXinterrupt_t **************************************/
/******************************************************************************/
typedef enum{
			RX_INTERRUPT_MASKED           =0,
			RX_INTERRUPT_NOT_MASKED
}RXinterrupt_t;
/******************************************************************************/
/************************ @RXinterrupt_t **************************************/
/******************************************************************************/
typedef enum{
			TX_INTERRUPT_MASKED           =0,
			TX_INTERRUPT_NOT_MASKED
}TXinterrupt_t;
/******************************************************************************/
/************************ @RXinterrupt_t **************************************/
/******************************************************************************/
typedef struct{

	SPIindex_t                  SPIindex                ;
	ClockPhase_t                ClockPhase              ;
	ClockPolarity_t             ClockPolarity           ;         
	SPI_MCUstate_t              SPI_MCUstate            ;
	BaudRate_t                  BaudRate                ;
	FrameFormat_t               FrameFormat             ;
	InternalSlaveSelect_t       InternalSlaveSelect     ;
	SoftwareSlaveManagment_t    SoftwareSlaveManagment  ;
	ReceiveOnly_t               ReceiveOnly             ;
	DataFrame_t                 DataFrame               ;
	RXDMA_t                     RXDMA                   ;
	TXDMA_t                     TXDMA                   ;
	SSoutput_t                  SSoutput                ;
	RXinterrupt_t               RXinterrupt             ;
	TXinterrupt_t               TXinterrupt             ;

}SPIconfig_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MSPI_u8SetConfiguration
 * @brief          : initialization Value of SPI Configuration
 * @param[in]      : USARTconfig  --> get option from @SPIconfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SetConfiguration ( const SPIconfig_t* SPIconfig );
/**
 ******************************************************************************
 * @fn             : MSPI_u8RXinterruptStatus
 * @brief          : RXinterruptStatus
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[in]      : Copy_RXinterrupt --> Get option From @RXinterrupt_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8RXinterruptStatus ( SPIindex_t Copy_SPIindex , RXinterrupt_t Copy_RXinterrupt );
/**
 ******************************************************************************
 * @fn             : MSPI_u8SendReceiveSynch
 * @brief          : Send and Receive Synchronization Function
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[in]      : Copy_u8DataToTransmit  --> Set Transmit Data
 * @param[out]     : Copy_u8DataToReceive  --> Get Received Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SendReceiveSynch ( SPIindex_t Copy_SPIindex , uint8_t Copy_u8DataToTransmit , uint8_t *Copy_u8DataToReceive );
/**
 ******************************************************************************
 * @fn             : MSPI_u8ReceiveArraySynch
 * @brief          : Receive Array Synch
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[out]     : Copy_pu8DataArray  --> Get Received Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MSPI_u8ReceiveArraySynch  (  SPIindex_t Copy_SPIindex , uint8_t * Copy_pu8DataArray   );
/**
 ******************************************************************************
 * @fn             : MSPI_u8SendReceiveAsynch
 * @brief          : Send and Receive Synchronization Function
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[in]      : Copy_u8DataToTransmit  --> Set Transmit Data
 * @param[out]     : Copy_pFunNotification  --> Set Address of Call Back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SendReceiveAsynch ( SPIindex_t Copy_SPIindex , uint8_t Copy_u8DataToTransmit , void (*Copy_pFunNotification) (uint8_t) );
/**
 ******************************************************************************
 * @fn             : MSPI_u8TransmitArraySynch
 * @brief          : Transmit Array Synch
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[out]     : Copy_pu8DataArray  --> Set Received Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSPI_u8TransmitArraySynch  ( SPIindex_t Copy_SPIindex , uint8_t * Copy_pu8DataArray );


/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/



#endif
