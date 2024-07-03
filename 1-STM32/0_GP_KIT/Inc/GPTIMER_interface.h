/**
 ******************************************************************************
 * @file           : GPTIMER_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 13/9/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  GPTIMER_INTERFACE_H
#define  GPTIMER_INTERFACE_H
/******************************************************************************/
/************************ @GPTIMERindex_t *************************************/
/******************************************************************************/
typedef enum{
			TMR_2   =0,
			TMR_3     ,
			TMR_4     ,
			TMR_5
}GPTIMERindex_t;
/******************************************************************************/
/************************ @Channelindex_t *************************************/
/******************************************************************************/
typedef enum{
			TMR_CHANNEL_1  =0,
			TMR_CHANNEL_2    ,
			TMR_CHANNEL_3    ,
			TMR_CHANNEL_4
}Channelindex_t;
/******************************************************************************/
/************************ @CounterStatus_t ************************************/
/******************************************************************************/
typedef enum{
			COUNTER_DISABLE   =0,
			COUNTER_ENABLE
}CounterStatus_t;
/******************************************************************************/
/************************ @OutputCompareMode_t ********************************/
/******************************************************************************/
typedef enum{
			OCM_FROZEN         =0,
			OCM_ACTIVE           ,
			OCM_INACTIVE         ,
			OCM_TOGGLE           ,
			OCM_INACTIVE_FORCE   ,
			OCM_ACTIVE_FORCE     ,
			OCM_PWM_MODE1        ,
			OCM_PWM_MODE2
}OutputCompareMode_t;
/******************************************************************************/
/************************ @OutputComparePreloadStatus_t ***********************/
/******************************************************************************/
typedef enum{
			OCPE_DISABLE  =0,
			OCPE_ENABLE
}OutputComparePreloadStatus_t;
/******************************************************************************/
/************************ @OnePulseMode_t *************************************/
/******************************************************************************/
typedef enum{
			OPM_DISABLE   =0,
			OPM_ENABLE
}OnePulseMode_t;
/******************************************************************************/
/************************ @CounterStatus_t ************************************/
/******************************************************************************/
typedef enum{
			CCIE_DISABLE   =0,
			CCIE_ENABLE
}CompareInterruptStatus_t;
/******************************************************************************/
/************************ @CounterStatus_t ************************************/
/******************************************************************************/
typedef enum{
			CCP_RISING   =0,
			CCP_FALLING
}TriggerEdge_t;
/******************************************************************************/
/************************ @InputConfig_t **************************************/
/******************************************************************************/
typedef enum{
			CCS_TI1   =0,
			CCS_TI2     ,
			CCS_TRC
}InputConfig_t;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8CounterStatus
 * @brief          : Counter Status
 * @param[in]      : Copy_GPTIMERindex  --> get option from @GPTIMERindex_t  enum
 * @param[in]      : Copy_CounterStatus --> get option from @CounterStatus_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8CounterStatus     ( GPTIMERindex_t Copy_GPTIMERindex ,  CounterStatus_t Copy_CounterStatus );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetPrescaler
 * @brief          : Set Prescaler
 * @param[in]      : Copy_GPTIMERindex  --> get option from @GPTIMERindex_t  enum
 * @param[in]      : Copy_u16Prescaler --> Set Prescaler Value
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetPrescaler     ( GPTIMERindex_t Copy_GPTIMERindex ,  uint16_t Copy_u16Prescaler );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetAutoReload
 * @brief          : Set Auto Reload
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t  enum
 * @param[in]      : Copy_u16AutoReloadValue --> Set Auto Reload Value
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetAutoReload ( GPTIMERindex_t Copy_GPTIMERindex  , uint16_t  Copy_u16AutoReloadValue );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetTriggerEdge
 * @brief          : Set Trigger Edge
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex --> get option from @Channelindex_t enum
 * @param[in]      : Copy_TriggerEdge  --> get option from @TriggerEdge_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetTriggerEdge     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , TriggerEdge_t Copy_TriggerEdge );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8OnePulseModeStatus
 * @brief          : One Pulse Mode Status
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_OnePulseMode --> get option from @OnePulseMode_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8OnePulseModeStatus     ( GPTIMERindex_t Copy_GPTIMERindex ,  OnePulseMode_t Copy_OnePulseMode );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetChannelOutput
 * @brief          : Set Channel Output Configuration
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex --> get option from @Channelindex_t enum
 * @param[in]      : Copy_OutputCompareMode  --> get option from @OutputCompareMode_t  enum
 * @param[in]      : Copy_OutputComparePreloadStatus  --> get option from @OutputComparePreloadStatus_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetChannelOutput     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , OutputCompareMode_t  Copy_OutputCompareMode , OutputComparePreloadStatus_t  Copy_OutputComparePreloadStatus  );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetChannelInput
 * @brief          : Set Channel Input Configuration
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex --> get option from @Channelindex_t enum
 * @param[in]      : Copy_InputConfig  --> get option from @InputConfig_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetChannelInput     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex  , InputConfig_t Copy_InputConfig );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetCompareValue
 * @brief          : Set Compare Value
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex --> get option from @Channelindex_t enum
 * @param[in]      : Copy_u16CompareValue  --> Set Compare Value
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetCompareValue ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , uint16_t  Copy_u16CompareValue );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8GetCompareValue
 * @brief          : Get Compare Value
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex --> get option from @Channelindex_t enum
 * @param[out]     : Copy_pu16CaptureValue  --> Get Compare Value
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8GetCompareValue ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , uint16_t  *Copy_pu16CaptureValue );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8ClearCounter
 * @brief          : Clear Counter
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8ClearCounter ( GPTIMERindex_t Copy_GPTIMERindex  );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetCounter
 * @brief          : Set Counter
 * @param[in]      : Copy_GPTIMERindex  --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_u16CountValue --> Set Counter Value
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetCounter ( GPTIMERindex_t Copy_GPTIMERindex , uint16_t Copy_u16CounterValue);

/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8CompareInterruptStatus
 * @brief          : Compare Interrupt Status
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Channelindex_t  --> get option from @Channelindex_t enum
 * @param[in]      : Copy_CompareInterruptStatus --> get option from @CompareInterruptStatus_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8CompareInterruptStatus ( GPTIMERindex_t Copy_GPTIMERindex , Channelindex_t Copy_CompareInterruptIndex , CompareInterruptStatus_t Copy_CompareInterruptStatus );
/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8SetCallBack
 * @brief          : Set Call Back
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_pFun         --> Set Address of Call Back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8SetCallBack( GPTIMERindex_t Copy_GPTIMERindex , void (*Copy_pFun) (void) );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
#endif
