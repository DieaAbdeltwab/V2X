/**
 ******************************************************************************
 * @file           : NVIC_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : MCAL (Core Peripherals )
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 25/7/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  NVIC_INTERFACE_H
#define  NVIC_INTERFACE_H
/******************************************************************************/
/*************************** @IntNumber_t *************************************/
/******************************************************************************/
typedef enum
{

           NVIC_PENDSV      =-2                	 ,
           NVIC_SYSTICK                     	 ,
           NVIC_WWDG                             ,
           NVIC_PVD                              ,
           NVIC_TAMPER                           ,
           NVIC_RTC                              ,
           NVIC_FLASH                            ,
           NVIC_RCC                              ,
           NVIC_EXTI0                            ,
           NVIC_EXTI1                            ,
           NVIC_EXTI2                            ,
           NVIC_EXTI3                            ,
           NVIC_EXTI4                            ,
           NVIC_DMA1_Channel1                    ,
           NVIC_DMA1_Channel2                    ,
           NVIC_DMA1_Channel3                    ,
           NVIC_DMA1_Channel4                    ,
           NVIC_DMA1_Channel5                    ,
           NVIC_DMA1_Channel6                    ,
           NVIC_DMA1_Channel7                    ,
           NVIC_ADC1_2                           ,
           NVIC_USB_HP_CAN_TX                    ,
           NVIC_USB_LP_CAN_RX0                   ,
           NVIC_CAN1_RX1                         ,
           NVIC_CAN1_SCE                         ,
           NVIC_EXTI9_5                          ,
           NVIC_TIM1_BRK                         ,
           NVIC_TIM1_UP                          ,
           NVIC_TIM1_TRG_COM                     ,
           NVIC_TIM1_CC                          ,
           NVIC_TIM2                             ,
           NVIC_TIM3                             ,
           NVIC_TIM4                             ,
           NVIC_I2C1_EV                          ,
           NVIC_I2C1_ER                          ,
           NVIC_I2C2_EV                          ,
           NVIC_I2C2_ER                          ,
           NVIC_SPI1                             ,
           NVIC_SPI2                             ,
           NVIC_USART1                           ,
           NVIC_USART2                           ,
           NVIC_USART3                           ,
           NVIC_EXTI15_10                        ,
           NVIC_RTCAlarm                         ,
           NVIC_USBWakeup                        ,
           NVIC_TIM8_BRK                         ,
           NVIC_TIM8_UP                          ,
           NVIC_TIM8_TRG_COM                     ,
           NVIC_TIM8_CC                          ,
           NVIC_ADC3                             ,
           NVIC_FSMC                             ,
           NVIC_SDIO                             ,
           NVIC_TIM5                             ,
           NVIC_SPI3                             ,
           NVIC_UART4                            ,
           NVIC_UART5                            ,
           NVIC_TIM6                             ,
           NVIC_TIM7                             ,
           NVIC_DMA2_Channel1                    ,
           NVIC_DMA2_Channel2                    ,
           NVIC_DMA2_Channel3                    ,
           NVIC_DMA2_Channel4_5                 
}IntNumber_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MNVIC_u8EnableInterrupt
 * @brief          : Enable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8EnableInterrupt    ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8DisableInterrupt
 * @brief          : Disable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8DisableInterrupt   ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPendingFlag
 * @brief          : Set Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPendingFlag     ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ClearPendingFlag
 * @brief          : Clear Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ClearPendingFlag   ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ReadActiveFlag
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[OUT]     : Copy_pu8StatusActiveFlag --> get Active Flag
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ReadActiveFlag     ( IntNumber_t Copy_IntNumber ,  uint8_t* Copy_pu8StatusActiveFlag );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPriority
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[in]      : Copy_u8GroubSubPriority --> Set Group Sub Priority
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPriority ( IntNumber_t Copy_IntNumber ,  uint8_t Copy_u8GroubSubPriority );

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
#endif
