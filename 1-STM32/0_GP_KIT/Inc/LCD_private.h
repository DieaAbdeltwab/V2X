/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Private of LCD ************************************************************************************/
/***************** Date : 11/10/2022  ***************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For LCD ******************************************************************************/
/****************************************************************************************************************************/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

/******************************************************************************/
/************************ Commands ********************************************/
/******************************************************************************/
#define LCD_FUN_SIT                 0b00111000
#define LCD_DISPLAY_ON_OF_CONTROL   0b00001111
#define LCD_HIDDEN_CURSOR           0b00001100

#define LCD_DISPLAY_CLEAR           0x01          // replace all characters with ASCII 'space'
#define LCD_HOME                    0x02          // return cursor to first position on first line
#define LCD_ENTRY_MODE              0x06          // shift cursor from left to right on read/write
#define LCD_DISPLAY_OFF             0x08          // turn display off
#define LCD_DISPLAY_ON              0x0C          // display on, cursor off, don't blink character
#define LCD_FUNCTION_RESET          0x30          // reset the LCD
#define LCD_FUNCTION_SET_8BIT       0x38          // 8-bit data, 2-line display, 5 x 7 font
#define LCD_SET_CURSOR              0x80          // set cursor position

#define LCD_FUN_SIT_1               0x02
#define LCD_FUN_SIT_2               0x28
/******************************************************************************/
/************************ Mode  ***********************************************/
/******************************************************************************/
#define LCD_u8_MODE_8_BIT               0
#define LCD_u8_MODE_4_BIT               1

//*****************************************************************************/
/************************ Delay ***********************************************/
/******************************************************************************/
#define LCD_u8_WAIT_VOLT           35000
#define LCD_u8_WAIT_DISPLAY        1000
#define LCD_u8_WAIT_ENTRY          2000
#define LCD_u8_WAIT_SHIFT          2
#define LCD_u8_WAIT_ENABLE_PULSE   2
//*****************************************************************************/
/************************ Access **********************************************/
/******************************************************************************/
#define LCD_u8_GET_ANOTHER_DIGIT   10
#define LCD_u8_Zero                0

/******************************************************************************/
/************************ Static Function *************************************/
/******************************************************************************/

static void HLCD_voidSendCmnd(uint8_t Copy_u8Comnd);

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
#endif



