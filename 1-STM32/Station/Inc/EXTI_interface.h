/**
 ******************************************************************************
 * @file           : EXTI_interface.h
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
#ifndef  EXTI_INTERFACE_H
#define  EXTI_INTERFACE_H
/******************************************************************************/
/*************************** @EXTI_LineNumber_t *******************************/
/******************************************************************************/

typedef enum{
			LINE0=0,
			LINE1  ,
			LINE2  ,
			LINE3  ,
			LINE4  ,
			LINE5  ,
			LINE6  ,
			LINE7  ,
			LINE8  ,
			LINE9  ,
			LINE10 ,
			LINE11 ,
			LINE12 ,
			LINE13 ,
			LINE14 ,
			LINE15

}EXTI_LineNumber_t;
/******************************************************************************/
/*************************** @EXTI_State_t ************************************/
/******************************************************************************/

typedef enum{
			EXTI_DISABLE =0,
			EXTI_ENABLE

}EXTI_State_t;
/******************************************************************************/
/*************************** @EXTI_TrigSrc_t **********************************/
/******************************************************************************/

typedef enum{
			FALLINNG      =0,
			RISING          ,
			FALLINNG_RISING

}EXTI_TrigSrc_t;
/******************************************************************************/
/*************************** @EXTI_config_t ***********************************/
/******************************************************************************/

typedef struct{
				EXTI_LineNumber_t PinNumber ;
				EXTI_TrigSrc_t    TrigSrc   ;
				EXTI_State_t      InitState ;
				void (* CallBackFunc)(void) ;
}EXTI_config_t;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MEXTI_u8Config
 * @brief          : EXTI line Config
 * @param[in]      : Copy_Config --> init Value of Pin from @EXTI_config_t struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8Config    ( EXTI_config_t* Copy_Config );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8SetSignalLatch
 * @brief          : Set Signal Latch
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @param[in]      : Copy_SenseMode  --> init Value of Pin from @EXTI_TrigSrc_t    struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SetSignalLatch   ( EXTI_LineNumber_t Copy_LineNumber , EXTI_TrigSrc_t Copy_SenseMode );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8InterruptState
 * @brief          : Interrupt State
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @param[in]      : Copy_LineState  --> init Value of Pin from @EXTI_State_t    struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8InterruptState       ( EXTI_LineNumber_t Copy_LineNumbe , EXTI_State_t Copy_LineState );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8SoftwareTrigger
 * @brief          : Software Trigger
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SoftwareTrigger  ( EXTI_LineNumber_t Copy_LineNumbe );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8ClearPendingFlag
 * @brief          : Clear Pending Flag
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8ClearPendingFlag  ( EXTI_LineNumber_t Copy_LineNumbe );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8GetPendingFlag
 * @brief          : Get Pending Flag
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @param[OUT]     : Copy_pu8Pendingstate --> GET state of flag
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8GetPendingFlag  ( EXTI_LineNumber_t Copy_LineNumbe , uint8_t *Copy_pu8Pendingstate );
/**
 ******************************************************************************
 * @fn             : MEXTI_u8SetCallBack
 * @brief          : Set Call Back
 * @param[in]      : Copy_LineNumber --> init Value of Pin from @EXTI_LineNumber_t struct
 * @param[in]      : Copy_pfun --> set Call back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MEXTI_u8SetCallBack      ( EXTI_LineNumber_t Copy_LineNumbe   , void (* Copy_pfun)(void) );




#endif
