/**
 ******************************************************************************
 * @file           : RCC_interface.h
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
#ifndef  RCC_INTERFACE_H
#define  RCC_INTERFACE_H

/******************************************************************************/
/************************ @BUSS_t *********************************************/
/******************************************************************************/
typedef enum{
			 AHB=0,
             APB1 ,
             APB2
}BUSS_t;
/******************************************************************************/
/************************* @AHBperipherals_t **********************************/
/******************************************************************************/
typedef enum{
			PER_DMA1    =0,
			PER_DMA2      ,
			PER_SRAM      ,
			PER_FLITF   =4,
			PER_CRC     =6,
			PER_FSMC    =8,
			PER_SDIO   =10,

}AHBperipherals_t;
/******************************************************************************/
/************************* @APB1peripherals_t *********************************/
/******************************************************************************/
typedef enum{
			PER_TIM2   =0,
			PER_TIM3     ,
			PER_TIM4     ,
			PER_TIM5     ,
			PER_TIM6     ,
			PER_TIM7     ,
			PER_TIM12    ,
			PER_TIM13    ,
			PER_TIM14    ,
			PER_WWDG  =11,
			PER_SPI2  =14,
			PER_SPI3     ,
			PER_USART2=17,
			PER_USART3   ,
			PER_UART4    ,
			PER_UART5    ,
			PER_I2C1     ,
			PER_I2C2     ,
			PER_CAN   =25,
			PER_BKP   =27,
			PER_PWR      ,
			PER_DAC
}APB1peripherals_t;
/******************************************************************************/
/************************* @APB2peripherals_t *********************************/
/******************************************************************************/
typedef enum{
			PER_AFIO    =0,
			PER_IOPA    =2,
			PER_IOPB      ,
			PER_IOPC      ,
			PER_IOPD      ,
			PER_IOPE      ,
			PER_IOPF      ,
			PER_IOPG      ,
			PER_ADC1      ,
			PER_ADC2      ,
			PER_TIM1      ,
			PER_SPI1      ,
			PER_TIM8      ,
			PER_USART1    ,
			PER_ADC3      ,
			PER_TIM9   =19,
			PER_TIM10     ,
			PER_TIM11
}APB2peripherals_t;

/************************************************************************************/
/******************************* @ClockType_t ***************************************/
/************************************************************************************/
typedef enum{
	        HSI=0,
  	        HSE  ,
	        PLL
}ClockType_t;

/************************************************************************************/
/******************************** @HSEConfig_t **************************************/
/************************************************************************************/
typedef enum{
			DIV_1 =0 ,
			DIV_2
}HSEConfig_t;
/************************************************************************************/
/******************************** @HSEBypass_t **************************************/
/************************************************************************************/
typedef enum{
			NOT_BYP =0,
	        BYP
}HSEBypass_t;

/************************************************************************************/
/******************************** @PLLinput_t ***************************************/
/************************************************************************************/
typedef enum{
		    PLL_HSI_DIV_2=0,
		    PLL_HSE
}PLLinput_t;

/************************************************************************************/
/******************************** @PLLmul_t *****************************************/
/************************************************************************************/
typedef enum{
			MUL_2=0 ,
			MUL_3   ,
			MUL_4   ,
			MUL_5   ,
			MUL_6	,
			MUL_7	,
			MUL_8	,
			MUL_9	,
			MUL_10	,
			MUL_11	,
			MUL_12	,
			MUL_13	,
			MUL_14	,
			MUL_15	,
			MUL_16
}PLLmul_t;
/*******************************************************************************************/
/***************************** @ClockSecuritySys_t *****************************************/
/*******************************************************************************************/
typedef enum{
			SECURITY_DISABLE=0,
			SECURITY_ENABLE
}ClockSecuritySys_t;
/*******************************************************************************************/
/***************************** @ADCPrescelar_t *********************************************/
/*******************************************************************************************/
typedef enum{
	        PCLK2_DIV_2=0,
			PCLK2_DIV_4  ,
			PCLK2_DIV_6  ,
			PCLK2_DIV_8  ,
}ADCPrescelar_t;
/*******************************************************************************************/
/***************************** @ClockState_t ***********************************************/
/*******************************************************************************************/
typedef enum{
			DISABLE=0,
			ENABLE

}ClockState_t;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
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
uint8_t   MRCC_u8SetClockState		    (  ClockType_t       Copy_ClockType , ClockState_t      Copy_ClockState );
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
uint8_t   MRCC_u8SetSystemClock		    (  ClockType_t       Copy_ClockType );
/**
 ******************************************************************************
 * @fn             : MRCC_u8HSEConfiguration
 * @brief          : Set HSE Configuration
 * @param[in]      : Copy_ClockType  --> get option from @HSEConfig_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MRCC_u8HSEConfiguration       (  HSEConfig_t       Copy_HSEConfig );
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
uint8_t   MRCC_u8PLLConfiguration       (  PLLmul_t  		 Copy_PLLmul    , PLLinput_t        Copy_PLLSCR     );
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
uint8_t   MRCC_u8AHBPeripheralsClockState          (  AHBperipherals_t  Copy_PerID     , ClockState_t      Copy_ClockState );
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
uint8_t   MRCC_u8APB2PeripheralsClockState         (  APB2peripherals_t Copy_PerID     , ClockState_t      Copy_ClockState );
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
uint8_t   MRCC_u8APB1PeripheralsClockState         (  APB1peripherals_t Copy_PerID     , ClockState_t      Copy_ClockState );
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
uint8_t   MRCC_u8PeripheralsClockState             (  BUSS_t            Copy_Bus       , uint8_t  Copy_PerID      , ClockState_t Copy_ClockState );
/**
 ******************************************************************************
 * @fn             : MRCC_u8ClockSecurityState
 * @brief          : Set Clock Security State
 * @param[in]      : Copy_ClockState --> get option from @ClockState_t   enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MRCC_u8ClockSecurityState ( ClockState_t Copy_ClockState );
/**
 ******************************************************************************
 * @fn             : MRCC_u8ADCPrescelar
 * @brief          : Set ADC Prescelar
 * @param[in]      : Copy_ADCPrescelar --> get option from @ADCPrescelar_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MRCC_u8ADCPrescelar ( ADCPrescelar_t Copy_ADCPrescelar );

/***********************************************************************************************************************/
/***********************************************************************************************************************/

#endif
