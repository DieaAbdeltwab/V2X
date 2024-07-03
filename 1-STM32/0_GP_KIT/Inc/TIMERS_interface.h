/**
 ******************************************************************************
 * @file           : TIMERS_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : SERVIES
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 19/9/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  TIMERS_INTERFACE_H
#define  TIMERS_INTERFACE_H
/******************************************************************************/
/************************ @ ***************************************************/
/******************************************************************************/
#include "GPTIMER_interface.h"

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : TIMERS_voidDelayMS
 * @brief          : Delay Milliseconds
 * @param[in]      : Copy_u32Milliseconds --> Set Time MS
 * @retval         : void
 ******************************************************************************
 * @attention
 *   This Function not Depend on Any timer , This Dumb Function
 *
 ******************************************************************************
 */

void STIMERS_voidDelayMS(uint32_t Copy_u32Milliseconds);
/**
 ******************************************************************************
 * @fn             : STIMERS_voidDelayUS
 * @brief          : Delay Microseconds
 * @param[in]      : Copy_u32Microseconds --> Set Time US
 * @retval         : void
 ******************************************************************************
 * @attention
 *   This Function not Depend on Any timer , This Dumb Function
 *
 ******************************************************************************
 */
void STIMERS_voidDelayUS(uint32_t Copy_u32Microseconds);
/**
 ******************************************************************************
 * @fn             : STIMERS_u8GeneratePWM
 * @brief          : Generate PWM Signal
 * @param[in]      : Copy_GPTIMERindex  --> get option from @GPTIMERindex_t enum
 * @param[in]      : Copy_Channelindex  --> get option from @Channelindex_t enum
 * @param[in]      : Copy_u16frequencyValue --> Set frequency Value 50000
 * @param[in]      : Copy_u16DutyCycleValue --> Set Duty Value      20
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *  this Function set Prescaler  1024
 *
 ******************************************************************************
 */
uint8_t  STIMERS_u8GeneratePWM ( GPTIMERindex_t Copy_GPTIMERindex ,  Channelindex_t Copy_Channelindex , uint32_t Copy_u32frequencyValue , uint8_t Copy_u8DutyCycleValue );
/**
 ******************************************************************************
 * @fn             : STIMERS_u8SetPeriodicInterval
 * @brief          : Set Interval Counter
 * @param[in]      : Copy_GPTIMERindex  --> get option from   @GPTIMERindex_t enum
 * @param[in]      : Copy_ChannelTMR      --> Get option from @Channelindex_t enum
 * @param[in]      : Copy_u32Ticks -->  Set Number of ticks  uint32_t
 * @param[  ]      : Copy_pFun         --> Set Call back function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 * this Function set Prescaler  1024
 *
 ******************************************************************************
 */
uint8_t STIMERS_u8SetPeriodicInterval   ( GPTIMERindex_t Copy_GPTIMERindex , Channelindex_t Copy_ChannelTMR , uint32_t Copy_u32Ticks , void(*Copy_pFun)(void) );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/



#endif
