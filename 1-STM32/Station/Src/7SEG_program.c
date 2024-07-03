/**
 ******************************************************************************
 * @file           : 7SEG_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 25/7/2023
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
#include "BIT_MATH.h"

/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_INTERFACE.h"
#include "STK_INTERFACE.h"

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "7SEG_interface.h"
#include "7SEG_private.h"
#include "7SEG_config.h"

/******************************************************************************/
/********************** ARRAY of Numbers **************************************/
/******************************************************************************/
static uint8_t Numbers[10]= { SEVEN_SEG_ZERO   ,
							  SEVEN_SEG_ONE    ,
							  SEVEN_SEG_TWO    ,
							  SEVEN_SEG_THREE  ,
							  SEVEN_SEG_FOUR   ,
							  SEVEN_SEG_FIVE   ,
							  SEVEN_SEG_SIX    ,
							  SEVEN_SEG_SEVEN  ,
							  SEVEN_SEG_EIGHT  ,
							  SEVEN_SEG_NINE   };
/**
 ******************************************************************************
 * @fn             : HSevenSeg_voidInit
 * @brief          : Init 7 Segment
 * @param          : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
void HSevenSeg_voidInit(void)
{
	MSTK_u8ClockConfig(STK_AHB_DIV_8);

	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN0 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN1 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN2 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN3 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN4 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN5 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN6 , OUTPUT_SPEED_2MHZ_PP );
	MGPIO_u8SetPinDirection   ( SEVEN_SEG_PIN7 , OUTPUT_SPEED_2MHZ_PP );

	#if     SEVEN_SEG_NUMBER == SEVEN_SEG_ONE
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM1 , OUTPUT_SPEED_2MHZ_PP );
	#elif   SEVEN_SEG_NUMBER == SEVEN_SEG_TWO
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM1 , OUTPUT_SPEED_2MHZ_PP );
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM2 , OUTPUT_SPEED_2MHZ_PP );
	#elif   SEVEN_SEG_NUMBER == SEVEN_SEG_THREE
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM1 , OUTPUT_SPEED_2MHZ_PP );
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM2 , OUTPUT_SPEED_2MHZ_PP );
			MGPIO_u8SetPinDirection   ( SEVEN_SEG_COM3 , OUTPUT_SPEED_2MHZ_PP );
	#else
			#error "Wrong Input"
	#endif

}
/**
 ******************************************************************************
 * @fn             : HSevenSeg_u8DisplayNum1Digit
 * @brief          : Display Number(1-9) On 7 Segment
 * @param[in]      : Copy_u8Number  --> get option from @Numbers_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t HSevenSeg_u8DisplayNum1Digit( Numbers_t  Copy_Number )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if ( Copy_Number <= NINE  )
	{
		#if   SEVEN_SEG_TYPE == COMMON_KA
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN0 , GET_BIT( Numbers[Copy_Number] ,0) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN1 , GET_BIT( Numbers[Copy_Number] ,1) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN2 , GET_BIT( Numbers[Copy_Number] ,2) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN3 , GET_BIT( Numbers[Copy_Number] ,3) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN4 , GET_BIT( Numbers[Copy_Number] ,4) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN5 , GET_BIT( Numbers[Copy_Number] ,5) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN6 , GET_BIT( Numbers[Copy_Number] ,6) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN7 , GET_BIT( Numbers[Copy_Number] ,7) );
		#if     SEVEN_SEG_NUMBER == SEVEN_SEG_ONE
				MGPIO_u8SetPinValue   ( SEVEN_SEG_COM1 , HIGH );
		#endif
		#elif SEVEN_SEG_TYPE == COMMON_AN
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN0 , ~GET_BIT( Numbers[Copy_Number],0) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN1 , ~GET_BIT( Numbers[Copy_Number],1) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN2 , ~GET_BIT( Numbers[Copy_Number],2) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN3 , ~GET_BIT( Numbers[Copy_Number],3) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN4 , ~GET_BIT( Numbers[Copy_Number],4) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN5 , ~GET_BIT( Numbers[Copy_Number],5) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN6 , ~GET_BIT( Numbers[Copy_Number],6) );
				MGPIO_u8SetPinValue   ( SEVEN_SEG_PIN7 , ~GET_BIT( Numbers[Copy_Number],7) );
		#if     SEVEN_SEG_NUMBER == SEVEN_SEG_ONE
				MGPIO_u8SetPinValue   ( SEVEN_SEG_COM1 , LOW );
		#endif
		#else
		#error "Wrong Input"
		#endif
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState;

}
/**
 ******************************************************************************
 * @fn             : HSevenSeg_u8DisplayNum2Digit
 * @brief          : Display Number(1-99) On 7 Segment
 * @param[in]      : Copy_NumOnes  --> get option from @Numbers_t  enum
 * @param[in]      : Copy_NumTens  --> get option from @Numbers_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t HSevenSeg_u8DisplayNum2Digit (Numbers_t Copy_NumOnes,Numbers_t Copy_NumTens)
{

	#if     SEVEN_SEG_NUMBER == SEVEN_SEG_TWO
			uint8_t Local_u8ErrorState = ERROR_STATE_OK;
			if ( Copy_NumOnes <= NINE && Copy_NumTens <= NINE )
			{
				MGPIO_u8SetPinValue(SEVEN_SEG_COM1,LOW);
				MGPIO_u8SetPinValue(SEVEN_SEG_COM2,LOW);

				MGPIO_u8SetPinValue(SEVEN_SEG_COM1,HIGH);
				HSevenSeg_u8DisplayNum1Digit(Copy_NumOnes);
				MSTK_u8BusyWait(15000);
				MGPIO_u8SetPinValue(SEVEN_SEG_COM1,LOW);

				MGPIO_u8SetPinValue(SEVEN_SEG_COM2,HIGH);
				HSevenSeg_u8DisplayNum1Digit(Copy_NumTens);
				MSTK_u8BusyWait(5000);
			}
			else
			{
				Local_u8ErrorState = ERROR_STATE_NOK;
			}
			return Local_u8ErrorState;
	#endif


}

