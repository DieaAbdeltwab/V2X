/**
 ******************************************************************************
 * @file           : ULTRASONIC_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 11/9/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef ULTRASONIC_INTERFACE_H
#define ULTRASONIC_INTERFACE_H
/******************************************************************************/
/************************ @ULTRASONICindex_t **********************************/
/******************************************************************************/
typedef enum
{
	ULTRASONIC_1 =0 ,
	ULTRASONIC_2    ,
	ULTRASONIC_3    ,
	ULTRASONIC_4

}ULTRASONICindex_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : ULTRASONIC_voidConfig
 * @brief          : Initialization of ULTRASONIC With ICU
 * @param[in]      : Copy_TMR             --> Get option from  GPTIMERindex_t
 * @param[in]      : Copy_ChannelTMR      --> Get option from  Channelindex_t
 * @param[in]      : Copy_ULTRASONICindex --> Get option from  ULTRASONICindex_t
 * @retval         : void
 ******************************************************************************
 * @attention
 * Configuration STK , NVIC , GPIO And GPTIMER
 *
 ******************************************************************************
 */
void ULTRASONIC_voidConfig   ( GPTIMERindex_t Copy_TMR , Channelindex_t Copy_ChannelTMR , ULTRASONICindex_t Copy_ULTRASONICindex );
/**
 ******************************************************************************
 * @fn             : ULTRASONIC_voidGetDistance
 * @brief          : Get Distance
 * @param[in]      : Copy_ULTRASONICindex --> Get option from  ULTRASONICindex_t
 * @param[out]     : Copy_pu16Distance    --> Get Distance Value
 * @retval         : void
 ******************************************************************************
 * @attention
 * Trigger  ULTRASONIC then Calculate Distance
 *
 ******************************************************************************
 */
void ULTRASONIC_voidGetDistance( ULTRASONICindex_t Copy_ULTRASONICindex , uint16_t *Copy_pu16DistanceValue );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


#endif
