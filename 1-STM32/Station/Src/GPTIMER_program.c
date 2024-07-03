/**
 ******************************************************************************
 * @file           : GPTIMER_program.c
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
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include "ERROR_STATE.h"
#include "stm32f103xx.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPTIMER_interface.h"
#include "GPTIMER_config.h"
#include "GPTIMER_private.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void (* GPTIMER_ApfCallBack[GPTIMER_NUMBERS])(void) = {NULL,NULL,NULL,NULL};
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
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
uint8_t  MGPTIMER_u8CounterStatus     ( GPTIMERindex_t Copy_GPTIMERindex ,  CounterStatus_t Copy_CounterStatus )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_CounterStatus <= COUNTER_ENABLE )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CR1 &=~ (GPTIMER_CEN_MASK  << (GPTIMER_CR1_CEN)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CR1 |=  (Copy_CounterStatus<< (GPTIMER_CR1_CEN)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetPrescaler     ( GPTIMERindex_t Copy_GPTIMERindex ,  uint16_t Copy_u16Prescaler )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> PSC =  Copy_u16Prescaler - 1 ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetAutoReload ( GPTIMERindex_t Copy_GPTIMERindex  , uint16_t  Copy_u16AutoReloadValue )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5   )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> ARR =  Copy_u16AutoReloadValue ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetTriggerEdge     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , TriggerEdge_t Copy_TriggerEdge )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_Channelindex <= TMR_CHANNEL_4 && Copy_TriggerEdge <= CCP_FALLING  )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CCER &=~ (GPTIMER_CCP_MASK  << ((Copy_Channelindex * GPTIMER_CCP_ACCSESS_1) + GPTIMER_CCP_ACCSESS_2)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CCER |=  (Copy_TriggerEdge  << ((Copy_Channelindex * GPTIMER_CCP_ACCSESS_1) + GPTIMER_CCP_ACCSESS_2)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8OnePulseModeStatus     ( GPTIMERindex_t Copy_GPTIMERindex ,  OnePulseMode_t Copy_OnePulseMode )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_OnePulseMode <= OPM_ENABLE )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CR1 &=~ (GPTIMER_OPM_MASK  << (GPTIMER_CR1_OPM)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CR1 |=  (Copy_OnePulseMode << (GPTIMER_CR1_OPM)) ;

	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetChannelOutput     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , OutputCompareMode_t  Copy_OutputCompareMode , OutputComparePreloadStatus_t  Copy_OutputComparePreloadStatus  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_Channelindex <= TMR_CHANNEL_4 && Copy_OutputCompareMode <= OCM_PWM_MODE2 )
	{
		uint8_t Local_u8Reg = ( Copy_Channelindex) / GPTIMER_CCMR_ACCSESS_1                            ;
		uint8_t Local_u8Bit = ((Copy_Channelindex) % GPTIMER_CCMR_ACCSESS_1 ) * GPTIMER_CCMR_ACCSESS_2 ;

		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] &=~ (GPTIMER_CCS_MASK  << (Local_u8Bit)) ;

		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] &=~ (GPTIMER_OCM_MASK      << (Local_u8Bit+GPTIMER_OCM_ACCSESS)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] |=  (Copy_OutputCompareMode<< (Local_u8Bit+GPTIMER_OCM_ACCSESS)) ;

		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] &=~ (GPTIMER_OCPE_MASK               << (Local_u8Bit+GPTIMER_OCPE_ACCSESS)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] |=  (Copy_OutputComparePreloadStatus << (Local_u8Bit+GPTIMER_OCPE_ACCSESS)) ;

		SET_BIT( (GPTIMER_Index[Copy_GPTIMERindex] -> CCER ) , ( Copy_Channelindex * GPTIMER_CCE_ACCSESS) );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetChannelInput     ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex  , InputConfig_t Copy_InputConfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_Channelindex <= TMR_CHANNEL_4 && Copy_InputConfig <= CCS_TRC )
	{
		uint8_t Local_u8Reg = ( Copy_Channelindex ) / GPTIMER_CCMR_ACCSESS_1                            ;
		uint8_t Local_u8Bit = ((Copy_Channelindex ) % GPTIMER_CCMR_ACCSESS_1 ) * GPTIMER_CCMR_ACCSESS_2 ;

		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] &=~ (GPTIMER_CCS_MASK                             << (Local_u8Bit)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> CCMR[Local_u8Reg] |=  ((Copy_InputConfig + GPTIMER_CCMR_ACCSESS_3)  << (Local_u8Bit)) ;

		SET_BIT( (GPTIMER_Index[Copy_GPTIMERindex] -> CCER ) , ((Copy_Channelindex * GPTIMER_CCE_ACCSESS)  ) );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetCompareValue ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , uint16_t  Copy_u16CompareValue )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_Channelindex <= TMR_CHANNEL_4  )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CCR[Copy_Channelindex] =  Copy_u16CompareValue ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8GetCompareValue ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , uint16_t  *Copy_pu16CaptureValue )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_Channelindex <= TMR_CHANNEL_4 )
	{
		*Copy_pu16CaptureValue=GPTIMER_Index[Copy_GPTIMERindex] -> CCR[Copy_Channelindex];
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8ClearCounter ( GPTIMERindex_t Copy_GPTIMERindex  )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5   )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CNT =  0 ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetCounter ( GPTIMERindex_t Copy_GPTIMERindex , uint16_t Copy_u16CounterValue)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5   )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> CNT =  Copy_u16CounterValue ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}

/**
 ******************************************************************************
 * @fn             : MGPTIMER_u8CompareInterruptStatus
 * @brief          : Compare Interrupt Status
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_CompareInterruptIndex  --> get option from @CompareInterruptIndex_t enum
 * @param[in]      : Copy_CompareInterruptStatus --> get option from @CompareInterruptStatus_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t  MGPTIMER_u8CompareInterruptStatus ( GPTIMERindex_t Copy_GPTIMERindex , Channelindex_t Copy_CompareInterruptIndex , CompareInterruptStatus_t Copy_CompareInterruptStatus )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 && Copy_CompareInterruptIndex <= TMR_CHANNEL_4 && Copy_CompareInterruptStatus<= CCIE_ENABLE )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> DIER &=~ (GPTIMER_CCIE_MASK          << (Copy_CompareInterruptIndex + GPTIMER_CCIE_ACCSESS)) ;
		GPTIMER_Index[Copy_GPTIMERindex] -> DIER |=  (Copy_CompareInterruptStatus<< (Copy_CompareInterruptIndex + GPTIMER_CCIE_ACCSESS)) ;
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t  MGPTIMER_u8SetCallBack( GPTIMERindex_t Copy_GPTIMERindex , void (*Copy_pFun) (void) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pFun != NULL )
	{
		GPTIMER_ApfCallBack[Copy_GPTIMERindex] = Copy_pFun;
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
 * @fn             : MGPTIMER_u8ClearInterruptFlags
 * @brief          : Clear Interrupt Flags
 * @param[in]      : Copy_GPTIMERindex --> get option from @GPTIMERindex_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t  MGPTIMER_u8ClearInterruptFlags( GPTIMERindex_t Copy_GPTIMERindex )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_GPTIMERindex <= TMR_5 )
	{
		GPTIMER_Index[Copy_GPTIMERindex] -> SR &=~ (GPTIMER_CCIF_MASK << GPTIMER_SR_CC1IF);
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
void TIM2_IRQHandler(void)
{
	if (  GPTIMER_ApfCallBack[TMR_2] != NULL )
	{
		MGPTIMER_u8ClearInterruptFlags(TMR_2);
		GPTIMER_ApfCallBack[TMR_2]();
	}
}
void TIM3_IRQHandler(void)
{
	if (  GPTIMER_ApfCallBack[TMR_3] != NULL )
	{
		MGPTIMER_u8ClearInterruptFlags(TMR_3);
		GPTIMER_ApfCallBack[TMR_3]();
	}
}
void TIM4_IRQHandler(void)
{
	if (  GPTIMER_ApfCallBack[TMR_4] != NULL )
	{
		MGPTIMER_u8ClearInterruptFlags(TMR_4);
		GPTIMER_ApfCallBack[TMR_4]();
	}
}void TIM5_IRQHandler(void)
{
	if (  GPTIMER_ApfCallBack[TMR_5] != NULL )
	{
		MGPTIMER_u8ClearInterruptFlags(TMR_5);
		GPTIMER_ApfCallBack[TMR_5]();
	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
