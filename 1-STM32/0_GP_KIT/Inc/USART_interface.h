/**
 ******************************************************************************
 * @file           : USART_interface.h
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
#ifndef  UART_INTERFACE_H
#define  UART_INTERFACE_H
/******************************************************************************/
/************************ @USARTindex_t ***************************************/
/******************************************************************************/
typedef enum{
			USART_1   =0,
			USART_2     ,
			USART_3     ,
			 UART_4     ,
			 UART_5
}USARTindex_t;
/******************************************************************************/
/************************ @UsartRX_t ******************************************/
/******************************************************************************/
typedef enum{
			RECEIVER_DISABLE   =0,
			RECEIVER_ENABLE
}Receiver_t;
/******************************************************************************/
/************************ @UsartTX_t ******************************************/
/******************************************************************************/
typedef enum{
			TRANSMITTER_DISABLE   =0,
			TRANSMITTER_ENABLE
}Transmitter_t;
/******************************************************************************/
/************************ @RXNEinterrupt_t ************************************/
/******************************************************************************/
typedef enum{
			RXNE_INTERRUPT_DISABLE   =0,
			RXNE_INTERRUPT_ENABLE
}RXNEinterrupt_t;
/******************************************************************************/
/************************ @TransmetCompleteInterrupt_t ************************/
/******************************************************************************/
typedef enum{
			TRANSMITTER_COMPLETE_INTERRUPT_DISABLE   =0,
			TRANSMITTER_COMPLETE_INTERRUPT_ENABLE
}TransmetCompleteInterrupt_t;
/******************************************************************************/
/************************ @TXNEinterrupt_t ************************************/
/******************************************************************************/
typedef enum{
			TXE_INTERRUPT_DISABLE   =0,
			TXE_INTERRUPT_ENABLE
}TXEinterrupt_t;

/******************************************************************************/
/************************ @ParitySelection_t **********************************/
/******************************************************************************/
typedef enum{
			PARITY_SELECTION_EVEN   =0,
			PARITY_SELECTION_ODD
}ParitySelection_t;
/******************************************************************************/
/************************ @ParityControl_t ************************************/
/******************************************************************************/
typedef enum{
			PARITY_CONTROL_DISABLE   =0,
			PARITY_CONTROL_ENABLE
}ParityControl_t;

/******************************************************************************/
/************************ @WordLength_t ***************************************/
/******************************************************************************/
typedef enum{
			DATA_8_BITS   =0,
			DATA_9_BITS
}WordLength_t;
/******************************************************************************/
/************************ @StopBit_t ******************************************/
/******************************************************************************/
/*
 * The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5
 */
typedef enum{
			HALF_BIT       =0,
			ONE_BIT          ,
			ONE_AND_HALF_BIT ,
			TWO_BIT
}StopBit_t;
/******************************************************************************/
/************************ @ErrorTnterrupt_t ***********************************/
/******************************************************************************/

typedef enum{
			INHIBITED       =0,
			GENERATED
}ErrorTnterrupt_t;
/******************************************************************************/
/************************ @DMAresevier_t **************************************/
/******************************************************************************/

typedef enum{
			DMAR_DISABLE       =0,
			DMAR_ENABLE
}DMAresevier_t;
/******************************************************************************/
/************************ @DMAtransmitter_t ***********************************/
/******************************************************************************/

typedef enum{
			DMAT_DISABLE       =0,
			DMAT_ENABLE
}DMAtransmitter_t;

/******************************************************************************/
/************************ @UsartStatus_t **************************************/
/******************************************************************************/

typedef enum{
			USART_DISABLE       =0,
			USART_ENABLE
}UsartStatus_t;

/********************************************************/
/******* @USARTconfig_t *********************************/
/********************************************************/

typedef struct{
			USARTindex_t                       USARTindex                 ;
			Receiver_t                         Receiver                   ;
			Transmitter_t                      Transmitter                ;
			RXNEinterrupt_t                    RXNEinterrupt              ;
			TransmetCompleteInterrupt_t        TransmetCompleteInterrupt  ;
			TXEinterrupt_t                     TXEinterrupt               ;
			ParitySelection_t                  ParitySelection            ;
			ParityControl_t                    ParityControl              ;
			WordLength_t                       WordLength                 ;
			StopBit_t                          StopBit_t                  ;
			ErrorTnterrupt_t                   ErrorTnterrupt             ;
			DMAresevier_t                      DMAresevier                ;
			DMAtransmitter_t                   DMAtransmitter             ;
}USARTconfig_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
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
uint8_t MUSART_u8SetConfiguration ( const USARTconfig_t* USARTconfig );
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
uint8_t MUSART_u8UsartStatus ( USARTindex_t Copy_USARTindex , UsartStatus_t Copy_UsartStatus );
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
uint8_t MUSART_u8RXinterruptStatus ( USARTindex_t Copy_USARTindex , RXNEinterrupt_t Copy_RXNEinterrupt );
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
uint8_t  MUSART_u8ReceiveCharSynch     ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataChar  );
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
uint8_t  MUSART_u8ReceiveCharNonBlocking     ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataChar  );
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
uint8_t  MUSART_u8ReceiveCharNonSynch     ( USARTindex_t Copy_USARTindex , void (*Copy_pFun) (uint8_t) );
/**
 ******************************************************************************
 * @fn             : MUSART_u8ReceiveStringSynch
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
uint8_t  MUSART_u8ReceiveStringSynch  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  );
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
uint8_t  MUSART_u8ReceiveArraySynch  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  , uint8_t Copy_u8Size  );
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
uint8_t  MUSART_u8ReceiveArrayNonBlocking  (  USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray  , uint8_t Copy_u8Size  );
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
uint8_t  MUSART_u8TransmitCharSynch     ( USARTindex_t Copy_USARTindex , uint8_t  Copy_u8DataChar  );
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
uint8_t   MUSART_u8TransmitStringSynch  ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray );
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
uint8_t   MUSART_u8TransmitArraySynch  ( USARTindex_t Copy_USARTindex , uint8_t * Copy_pu8DataArray , uint8_t Copy_u8Size );
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
void   MUSART_voidClearFlags( USARTindex_t Copy_USARTindex );
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
uint32_t*   MUSART_u32GetDRAddress( USARTindex_t Copy_USARTindex );
/**
 ******************************************************************************
 * @fn             : MUSART_u8SetCallBack
 * @brief          : Set Call Back Functions
 * @param[in]      : Copy_USARTindex  --> get option from @USARTindex_t enum
 * @param[in]      : Copy_pFun  --> Set address of Call Back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MUSART_u8SetCallBack( USARTindex_t Copy_USARTindex , void (*Copy_pFun) (void) );
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
uint8_t  MUSART_u8ReceiveCharNonSynch     ( USARTindex_t Copy_USARTindex , void (*Copy_pFun) (uint8_t) );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/





#endif
