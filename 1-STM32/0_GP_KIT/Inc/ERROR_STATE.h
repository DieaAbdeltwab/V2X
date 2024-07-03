/**
 ******************************************************************************
 * @file           : ERROR_STATE.h
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
#ifndef  ERROR_STATE_H
#define  ERROR_STATE_H


#define NULL ((void*)0)

typedef enum
{
		ERROR_STATE_NOK         =0,
		ERROR_STATE_OK         	  ,
		ERROR_STATE_NULL_PTR  	  ,
        ERROR_STATE_TIME_OUT

}ERROR_STATE_t;

typedef enum
{
	NO_ERROR         =0,
	Ready_QUEUE_INIT_ERROR ,
	TASK_EXCEEDED_STACK_SIZE,
}RTOS_ERROR_ID_t;





#endif
