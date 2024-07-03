/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of LCD ************************************************************************************/
/***************** Date : 29/7/2023   ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For LCD ******************************************************************************/
/****************************************************************************************************************************/
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "STK_INTERFACE.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
void HLCD_voidInit(void)
{
  MSTK_u8ClockConfig(STK_AHB_DIV_8);
  #if   LCD_u8_MODE == LCD_u8_MODE_8_BIT
	 MGPIO_u8SetPortDirection (LCD_u8_DATA_PORT    , LCD_u8_DATA_Position,OUTPUT_SPEED_2MHZ_PP);
	 MGPIO_u8SetPinDirection  (LCD_u8_CONTRAL_PORT , LCD_u8_RS_PIN,OUTPUT_SPEED_10MHZ_PP);
	 MGPIO_u8SetPinDirection  (LCD_u8_CONTRAL_PORT , LCD_u8_RW_PIN,OUTPUT_SPEED_10MHZ_PP);
	 MGPIO_u8SetPinDirection  (LCD_u8_CONTRAL_PORT , LCD_u8_E_PIN, OUTPUT_SPEED_10MHZ_PP);
	 /*************************************************/
	 MSTK_u8BusyWait(LCD_u8_WAIT_VOLT);
     HLCD_voidSendCmnd(LCD_FUN_SIT);
     MSTK_u8BusyWait(LCD_u8_WAIT_DISPLAY);
	 HLCD_voidSendCmnd(LCD_DISPLAY_ON_OF_CONTROL);
	 MSTK_u8BusyWait(LCD_u8_WAIT_DISPLAY);
	 HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
	 MSTK_u8BusyWait(LCD_u8_WAIT_ENTRY);
  #elif   LCD_u8_MODE == LCD_u8_MODE_4_BIT
	 MGPIO_u8SetPinDirection(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN0,OUTPUT_SPEED_2MHZ_PP);
	 MGPIO_u8SetPinDirection(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN1,OUTPUT_SPEED_2MHZ_PP);
	 MGPIO_u8SetPinDirection(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN2,OUTPUT_SPEED_2MHZ_PP);
	 MGPIO_u8SetPinDirection(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN3,OUTPUT_SPEED_2MHZ_PP);

	 MGPIO_u8SetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,OUTPUT_SPEED_2MHZ_PP);
	 //MGPIO_u8SetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,OUTPUT_SPEED_2MHZ_PP);
	 MGPIO_u8SetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN, OUTPUT_SPEED_2MHZ_PP);
	 /**********************************************************/
	 MSTK_u8BusyWait(LCD_u8_WAIT_VOLT);
	 HLCD_voidSendCmnd(LCD_FUN_SIT_1);
	 HLCD_voidSendCmnd(LCD_FUN_SIT_2);
	 MSTK_u8BusyWait(LCD_u8_WAIT_DISPLAY);
	 HLCD_voidSendCmnd(LCD_DISPLAY_ON);
	 MSTK_u8BusyWait(LCD_u8_WAIT_DISPLAY);
	 HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
	 MSTK_u8BusyWait(LCD_u8_WAIT_ENTRY);
	 HLCD_voidSendCmnd(LCD_ENTRY_MODE);
	 MSTK_u8BusyWait(LCD_u8_WAIT_ENTRY);
  #endif
}
void HLCD_voidClearLCD(void)
{
	HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
	MSTK_u8BusyWait(3000);
}
void HLCD_voidHiddenCursor(void)
{
	HLCD_voidSendCmnd(LCD_HIDDEN_CURSOR);
	MSTK_u8BusyWait(2000);
}
static void HLCD_voidSendCmnd(uint8_t Copy_u8Comnd)
{
  #if   LCD_u8_MODE  ==  LCD_u8_MODE_8_BIT
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,LOW);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	MGPIO_u8SetPortValue(LCD_u8_DATA_PORT,LCD_u8_DATA_Position,Copy_u8Comnd);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(1);;
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
  #elif   LCD_u8_MODE  ==  LCD_u8_MODE_4_BIT
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,LOW);
	//MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN0,GET_BIT(Copy_u8Comnd,4));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN1,GET_BIT(Copy_u8Comnd,5));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN2,GET_BIT(Copy_u8Comnd,6));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN3,GET_BIT(Copy_u8Comnd,7));
	/********************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(LCD_u8_WAIT_ENABLE_PULSE);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
	/************************/
	MSTK_u8BusyWait(LCD_u8_WAIT_SHIFT);
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN0,GET_BIT(Copy_u8Comnd,0));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN1,GET_BIT(Copy_u8Comnd,1));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN2,GET_BIT(Copy_u8Comnd,2));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN3,GET_BIT(Copy_u8Comnd,3));
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(LCD_u8_WAIT_ENABLE_PULSE);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
	MSTK_u8BusyWait(LCD_u8_WAIT_SHIFT);
  #endif
}
void HLCD_voidSendChar(uint8_t Copy_u8Char)
{
  #if   LCD_u8_MODE  ==  LCD_u8_MODE_8_BIT
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,HIGH);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	MGPIO_u8SetPortValue(LCD_u8_DATA_PORT,LCD_u8_DATA_Position,Copy_u8Char);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(1);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
  #elif   LCD_u8_MODE  ==  LCD_u8_MODE_4_BIT
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,HIGH);
	//MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN0,GET_BIT(Copy_u8Char,4));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN1,GET_BIT(Copy_u8Char,5));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN2,GET_BIT(Copy_u8Char,6));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN3,GET_BIT(Copy_u8Char,7));
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(LCD_u8_WAIT_ENABLE_PULSE);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
    /************************/
	MSTK_u8BusyWait(LCD_u8_WAIT_SHIFT);
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN0,GET_BIT(Copy_u8Char,0));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN1,GET_BIT(Copy_u8Char,1));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN2,GET_BIT(Copy_u8Char,2));
	MGPIO_u8SetPinValue(LCD_u8_DATA_PORT,LCD_u8_DATA_PIN3,GET_BIT(Copy_u8Char,3));
	/*******************************************************************/
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	MSTK_u8BusyWait(LCD_u8_WAIT_ENABLE_PULSE);
	MGPIO_u8SetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
	MSTK_u8BusyWait(LCD_u8_WAIT_SHIFT);
  #endif
}
void HLCD_voidSendString(uint8_t *Copy_pu8String)
{
	for(uint8_t Local_u8Counter=0; Copy_pu8String[Local_u8Counter] != '\0' ; Local_u8Counter++)
	{
		  HLCD_voidSendChar(Copy_pu8String[Local_u8Counter]);
	}
}

void HLCD_voidSendNumber(uint32_t Copy_u8Number)
{
	uint32_t Local_remainder=LCD_u8_Zero,Local_reverse=LCD_u8_Zero,Local_TMP=LCD_u8_Zero,Local_Counter,Local_TMPNum=Copy_u8Number;
	if (Copy_u8Number==LCD_u8_Zero)
	{
		HLCD_voidSendChar('0');
	}
	else
	{
		for(Local_Counter=-1;LCD_u8_Zero==Local_TMP;Local_Counter++)
		{
			Local_TMP=Local_TMPNum %LCD_u8_GET_ANOTHER_DIGIT;
			Local_TMPNum=Local_TMPNum / LCD_u8_GET_ANOTHER_DIGIT;
		}
		while(Copy_u8Number!=LCD_u8_Zero)
		{
			Local_remainder=Copy_u8Number %LCD_u8_GET_ANOTHER_DIGIT;
			Local_reverse=Local_reverse*LCD_u8_GET_ANOTHER_DIGIT+Local_remainder;
			Copy_u8Number=Copy_u8Number / LCD_u8_GET_ANOTHER_DIGIT;
		}
		Local_TMP=0;
		while (Local_reverse!=LCD_u8_Zero)
		{
			Local_TMP=Local_reverse%LCD_u8_GET_ANOTHER_DIGIT;
			HLCD_voidSendChar(Local_TMP+'0');
			Local_reverse=Local_reverse / LCD_u8_GET_ANOTHER_DIGIT;
		}
		while(0 != Local_Counter)
		{
			HLCD_voidSendChar('0');
			Local_Counter--;
		}
	}

}

void HLCD_voidSetCursor           ( LCDlocation Copy_Location      , LCDLineNum  Copy_LineNum  )
{
    switch (Copy_LineNum)
    {
          case LCD_LINE0 : HLCD_voidSendCmnd((0x80+Copy_Location)); break;
          case LCD_LINE1 : HLCD_voidSendCmnd((0xC0+Copy_Location)); break;
    }
}

void HLCD_voidWriteSpicalCaracter(LCDPatternNumper Copy_PatternNumper,uint8_t* Copy_u8Patterns)
{
	uint8_t Local_u8CGRAMAddress=0,Local_u8Iterator;
	Local_u8CGRAMAddress=Copy_PatternNumper*8;
	HLCD_voidSendCmnd(Local_u8CGRAMAddress+64);
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		HLCD_voidSendChar(Copy_u8Patterns[Local_u8Iterator]);
	}
}

