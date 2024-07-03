/**
 ******************************************************************************
 * @file           : BIT_MATH.h
 * @author         : Diea Abdeltwab
 * @layer          : Library
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 25/7/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef BIT_MATH_H
#define BIT_MATH_H



#define SET_BIT(REG , BITNUM) REG |= 0b1<<BITNUM
#define CLR_BIT(REG , BITNUM) REG &= ~(0b1<<BITNUM)
#define TOG_BIT(REG , BITNUM) REG ^= 0b1<<BITNUM
#define GET_BIT(REG , BITNUM) ( (REG >> BITNUM) & 0b1 )





#endif
