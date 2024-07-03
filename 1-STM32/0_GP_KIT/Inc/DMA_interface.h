
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/********************************************************/
/******* @Channel_t  ************************************/
/********************************************************/
typedef enum{
			DMA_CHANNEL1 =0 ,
			DMA_CHANNEL2    ,            
			DMA_CHANNEL3    ,           
			DMA_CHANNEL4    ,           
			DMA_CHANNEL5    ,           
			DMA_CHANNEL6    ,           
			DMA_CHANNEL7                
}Channel_t;
/********************************************************/
/******* @Direction  ************************************/
/********************************************************/
typedef enum{
			DMA_MEM_TO_MEM   =0 ,               
			DMA_PREI_TO_MEM     ,            
			DMA_MEM_TO_PERI                      		                
}Direction_t;
/********************************************************/
/******* @Mode_t  ***************************************/
/********************************************************/
typedef enum{
			 DMA_DISABLE_CIRCULAR =0 ,
			 DMA_ENABLE_CIRCULAR
}DMAMode_t;
/********************************************************/
/******* @Increment_t  **********************************/
/********************************************************/
typedef enum{
			 DMA_INCREMENT_DISABLE =0 ,
			 DMA_INCREMENT_ENABLE
}Increment_t;

/********************************************************/
/******* @DataSize_t  ***********************************/
/********************************************************/
typedef enum{
			DMA_SIZE_BYTE      =0 ,               
			DMA_SIZE_HALF_WORD    , 
			DMA_SIZE_WORD
}DataSize_t;      
/********************************************************/
/******* @Priority_t  ***********************************/
/********************************************************/
typedef enum{
			DMA_LOW        =0 ,               
			DMA_MEDIUM        , 
			DMA_HIGH          ,    
			DMA_VERY_HIGH  
}Priority_t;
/********************************************************/
/******* @Flags_t  **************************************/
/********************************************************/
typedef enum{
			DMA_GIF   =0 ,               
			DMA_TCIF     , 
			DMA_HTIF     ,    
			DMA_TEIF  
}Flags_t;
/********************************************************/
/******* @InterruptEnable_t  ****************************/
/********************************************************/
typedef enum{
			DMA_TCIE  =1 ,
			DMA_HTIE     , 
			DMA_TEIE        			
}InterruptEnable_t;
/********************************************************/
/******* @DMAstate_t  ***********************************/
/********************************************************/
typedef enum{
			DMA_DISABLE  =0 ,
			DMA_ENABLE
}DMAstate_t;
/********************************************************/
/******* @DMAconfig_t ***********************************/
/********************************************************/

typedef struct{
			Channel_t           ChannelIndex       ;     
			Direction_t         Direction          ;
			DMAMode_t           Mode               ;
			Increment_t         PerINC             ;
			Increment_t         MemINC             ;
			DataSize_t			MemSize            ;
			DataSize_t			PerSize            ;
			Priority_t			ChannelPriority    ;
}DMAconfig_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
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
uint8_t MDMA_u8SetConfiguration ( const DMAconfig_t* DMAconfig );
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
uint8_t  MDMA_u8Enable( Channel_t Copy_ChannelIndex );
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
uint8_t  MDMA_u8Disable( Channel_t Copy_ChannelIndex );
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
uint8_t  MDMA_u8InterruptEnable( Channel_t Copy_ChannelIndex , InterruptEnable_t Copy_INTSource );
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
uint8_t  MDMA_u8ChannelStart ( Channel_t Copy_ChannelIndex , uint32_t * Copy_pu32PeripheralAddress , uint32_t * Copy_pu32MemoryAddress , uint16_t Copy_u16BlockLength );
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
uint8_t  MDMA_u8SetCallBack      ( Channel_t Copy_ChannelIndex , void (* Copy_pfun)(void) );

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


















#endif
