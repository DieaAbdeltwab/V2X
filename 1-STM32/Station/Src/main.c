/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
/******************************************************************************/
/************************ CORE Layer ******************************************/
/******************************************************************************/
#include "STK_interface.h"
#include "NVIC_interface.h"
#include "SCB_interface.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "AFIO_interface.h"
#include "EXTI_interface.h"
#include "USART_interface.h"
#include "SPI_interface.h"
#include "I2C_interface.h"
#include "GPTIMER_interface.h"
#include "DMA_interface.h"

#include "ADC_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "7SEG_interface.h"
#include "KPD_interface.h"
#include "LCD_interface.h"
#include "IR_interface.h"
#include "LEDMRX_interface.h"
#include "STP_interface.h"
#include "DAC_interface.h"
#include "DAC_data.h"
#include "TFT_interface.h"
#include "TFT_data.h"
#include "MPU6050_interface.h"
#include "RTC_interface.h"
#include "ULTRASONIC_interface.h"
#include "INA219_interface.h"

/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "TIMERS_interface.h"
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
uint8_t  Global_pu8VIN[18] ;
uint8_t  Global_u8ChargingVolt = 0 ;
uint8_t  Global_u8StartVolt    = 0 ;
uint8_t  Global_u8EndtVolt     = 0 ;
uint8_t  Global_u8StartEndFlag = 0 ;

/********************************************************************************************************************************************/
/**************************************************** Global Variables **********************************************************************/
/********************************************************************************************************************************************/
#define SE_PLUG_CABLE      	                 0x51
#define SE_IDENTIFICATION     	             0x52
#define SE_CHARGE_PARAMETAR                  0x53
#define SE_CHARGING_COST                     0x54
#define SE_START_CHARGING                    0x55
#define SE_END_CHARGING                      0x56
#define SE_SEND_ENERGY_AMOUNT                0x57

#define SE_ACK					             0xA5
#define SE_NACK					             0x7F



#define SE_ADD_COST_SCCESS           		 0xB0
#define SE_ADD_COST_FAIL             		 0xB1

#define SE_VERIFY_IDENTIFICATION_SCCESS      0xB3
#define SE_VERIFY_IDENTIFICATION_FAIL        0xB4

#define SE_ACCEPT_CHARGING	                 0xB5
#define SE_REJECT_CHARGING                   0xB6

#define SE_ACCEPT_START_CHARGING             0xB8
#define SE_ACCEPT_END_CHARGING               0xB9


#define SE_ACCEPT_UPDATE_ENARGY              0xB5

/********************************************************************************************************************************************/
/**************************************************** Functions *****************************************************************************/
/********************************************************************************************************************************************/
static uint8_t u8Identification ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 1 + sizeof(Global_pu8VIN) ;
	MUSART_u8TransmitArraySynch(USART_2, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  SE_IDENTIFICATION ;
	MUSART_u8TransmitArraySynch(USART_2, &Local_u8SelectCmd , 1);
	MUSART_u8TransmitArraySynch(USART_2, Global_pu8VIN       , sizeof(Global_pu8VIN));

	MUSART_u8ReceiveArraySynch(USART_2, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == SE_ACK )
	{
		MUSART_u8ReceiveArraySynch(USART_2, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if ( Local_u8ReceivedData[0] == SE_VERIFY_IDENTIFICATION_SCCESS )
		{
			Local_u8SuccessFlag =  1;
		}
	}
	return Local_u8SuccessFlag ;
}
static uint8_t u8ChargingCost ( void )
{
	uint8_t Local_u8SuccessFlag     =  0  ;
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	uint8_t Local_u8ACTStatus[2]    = {0} ;
	uint8_t Local_u8ReceivedData[3] = {0} ;

	Local_u8LengthToFollow = 2 ;
	MUSART_u8TransmitArraySynch(USART_2, &Local_u8LengthToFollow, 1);
	Local_u8SelectCmd =  SE_CHARGING_COST ;
	MUSART_u8TransmitArraySynch(USART_2, &Local_u8SelectCmd   , 1);
	MUSART_u8TransmitArraySynch(USART_2, &Global_u8ChargingVolt, 1 );

	MUSART_u8ReceiveArraySynch(USART_2, Local_u8ACTStatus, 2);
	if (Local_u8ACTStatus[0] == SE_ACK  )
	{
		MUSART_u8ReceiveArraySynch(USART_2, Local_u8ReceivedData, Local_u8ACTStatus[1] );
		if (Local_u8ReceivedData[0] == SE_ADD_COST_SCCESS  )
		{
			Local_u8SuccessFlag = 1 ;
		}
	}
	return Local_u8SuccessFlag ;
}
static void voidSendAck (uint8_t Copy_u8ReplyLength )
{
	uint8_t Local_u8AckBuffer [2] = { SE_ACK , Copy_u8ReplyLength };
	MUSART_u8TransmitArraySynch( USART_1 , Local_u8AckBuffer , 2 );
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

void SE_voidPlugCable (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8V2GVersion   = 0x1 ;
	MGPIO_u8SetPinValue ( PORTA , PIN1 , HIGH );
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"---Plug Cable---");
	HLCD_voidSetCursor(Location0, LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"-----Success----");
	/*----------------------------------------------------*/
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch ( USART_1 , &Local_u8V2GVersion , 1 );
}
void SE_voidIdentification (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t   Local_u8VerifyFlag = 0 ;
	uint8_t   Local_u8VerifyIdentificationStatus = SE_VERIFY_IDENTIFICATION_FAIL ;
	for ( uint8_t Local_u8Counter = 0 ; Local_u8Counter<18 ; Local_u8Counter++ )
	{
		Global_pu8VIN[Local_u8Counter] = Copy_pu8CmdPacket[Local_u8Counter+2];
	}
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"-Identification-");
	/*----------------------------------------------------*/
	//Local_u8VerifyFlag = u8Identification();
	Local_u8VerifyFlag = 1 ;
	if ( Local_u8VerifyFlag == 1 )
	{
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"-----Success----");
		/*----------------------------------------------------*/
		Local_u8VerifyIdentificationStatus = SE_VERIFY_IDENTIFICATION_SCCESS ;
	}
	else
	{
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"-----Fail!------");
		/*----------------------------------------------------*/
		Global_u8StartEndFlag = 0 ;
	}
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8VerifyIdentificationStatus , 1 );
}
void SE_voidChargeParameter (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8ChargStatus  = SE_REJECT_CHARGING ;
	Global_u8StartVolt  = *((uint8_t *) &Copy_pu8CmdPacket[2] );
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"Charge Parameter");

	if ( Global_u8StartVolt <= 70 )
	{
		Local_u8ChargStatus = SE_ACCEPT_CHARGING ;
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"-----Success----");
		/*----------------------------------------------------*/
	}
	else
	{
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"Must->(Volt<70%)");
		/*----------------------------------------------------*/
		Global_u8StartEndFlag = 0 ;
	}
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8ChargStatus , 1 );
}
void SE_voidStartCharging (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8StartCharging = SE_ACCEPT_START_CHARGING ;
	MGPIO_u8SetPinValue(PORTB, PIN5  , HIGH);
	MGPIO_u8SetPinValue(PORTC, PIN15 , HIGH);
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"-Start Charging--");
	HLCD_voidSetCursor(Location0, LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"-----Success----");
	/*----------------------------------------------------*/
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8StartCharging , 1 );
}
void SE_voidSendEnergyAmount (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8ChargStatus  = SE_ACCEPT_UPDATE_ENARGY  ;
	Global_u8EndtVolt  = *((uint8_t *) &Copy_pu8CmdPacket[2] );
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"--EnergyAmount--");
	HLCD_voidSetCursor(Location0, LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"-----Volt=");
	HLCD_voidSetCursor(Location10, LCD_LINE1);
	HLCD_voidSendNumber(Global_u8EndtVolt);
	HLCD_voidSetCursor(Location12, LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"%---");
	/*----------------------------------------------------*/
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8ChargStatus , 1 );
}
void SE_voidChargingCost (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t  Local_u8CostFlag = 0 ;
	uint8_t Local_u8ChargCostStatus =  SE_ADD_COST_FAIL ;
	Global_u8ChargingVolt =  Global_u8EndtVolt - Global_u8StartVolt  ;
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"--Charging Cost-");
	/*----------------------------------------------------*/
	//Local_u8CostFlag = u8ChargingCost();
	Local_u8CostFlag = 1 ;
	if ( Local_u8CostFlag == 1 )
	{
		Local_u8ChargCostStatus = SE_ADD_COST_SCCESS ;
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"----Cost");
		HLCD_voidSetCursor(Location9, LCD_LINE1);
		HLCD_voidSendNumber( Global_u8ChargingVolt * 1 );
		HLCD_voidSetCursor(Location11, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"$----");
		/*----------------------------------------------------*/
	}
	else
	{
		/*----------------------------------------------------*/
		HLCD_voidSetCursor(Location0, LCD_LINE1);
		HLCD_voidSendString((uint8_t *)"-----Fail!------");
		/*----------------------------------------------------*/
		Global_u8StartEndFlag = 0 ;
	}
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8ChargCostStatus , 1 );
}
void SE_voidEndCharging (uint8_t * Copy_pu8CmdPacket )
{
	uint8_t Local_u8EndCharging = SE_ACCEPT_END_CHARGING ;
	MGPIO_u8SetPinValue(PORTB, PIN5  , LOW);
	MGPIO_u8SetPinValue(PORTC, PIN15 , LOW);
	MGPIO_u8SetPinValue(PORTA, PIN1  , LOW);
	/*----------------------------------------------------*/
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location0, LCD_LINE0);
	HLCD_voidSendString((uint8_t *)"--End Charging--");
	HLCD_voidSetCursor(Location0, LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"-----Success----");
	/*----------------------------------------------------*/
	Global_u8ChargingVolt = 0 ;
	Global_u8StartVolt    = 0 ;
	Global_u8EndtVolt     = 0 ;
	Global_u8StartEndFlag = 0 ;
	/*----------------------------------------------------*/
	voidSendAck(1u);
	MUSART_u8TransmitArraySynch( USART_1 , (uint8_t *)&Local_u8EndCharging , 1 );
}

/********************************************************************************************************************************************/
/**************************************************** Call Back Functions *******************************************************************/
/********************************************************************************************************************************************/

/********************************************************************************************************************************************/
/**************************************************** Main Function  ************************************************************************/
/********************************************************************************************************************************************/
int main(void)
{
	/********************************************************************************************************************************************/
	/**************************************************** Local Variables ***********************************************************************/
	/********************************************************************************************************************************************/

	/********************************************************************************************************************************************/
	/**************************************************** CORE Configurations *******************************************************************/
	/********************************************************************************************************************************************/
	MSTK_u8ClockConfig     (STK_AHB_DIV_8 );
	/********************************************************************************************************************************************/
	/**************************************************** RCC Configurations ********************************************************************/
	/********************************************************************************************************************************************/
	MRCC_u8SetClockState(HSE,ENABLE);
	MRCC_u8SetSystemClock(HSE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPA,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPB,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPC,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_USART1,ENABLE);
	MRCC_u8PeripheralsClockState(APB1,PER_USART2,ENABLE);

	/********************************************************************************************************************************************/
	/**************************************************** MCAL Configurations *******************************************************************/
	/********************************************************************************************************************************************/
	MGPIO_u8SetPinDirection(PORTA, PIN1 , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_u8SetPinDirection(PORTB, PIN5 , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_u8SetPinDirection(PORTC, PIN15, OUTPUT_SPEED_2MHZ_PP);

	MGPIO_u8SetPinDirection(PORTA, PIN9 , OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_u8SetPinDirection(PORTA, PIN10, INPUT_FLOATING);

	USARTconfig_t UART = {USART_1,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_DISABLE
						,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
						,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,ONE_BIT
						,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART);
	MUSART_u8UsartStatus(USART_1, USART_ENABLE);
	/*************************************************************************************************************/
	MGPIO_u8SetPinDirection(PORTA, PIN2 , OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_u8SetPinDirection(PORTA, PIN3 , INPUT_FLOATING);

	USARTconfig_t UART2 = {USART_2,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_DISABLE
						,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
						,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,ONE_BIT
						,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART2);
	MUSART_u8UsartStatus(USART_2, USART_ENABLE);
	/********************************************************************************************************************************************/
	/**************************************************** HAL Configurations ********************************************************************/
	/********************************************************************************************************************************************/
	HLCD_voidInit();
	/********************************************************************************************************************************************/
	/**************************************************** SERVIES Configurations ****************************************************************/
	/********************************************************************************************************************************************/

	/********************************************************************************************************************************************/
	/**************************************************** Loop **********************************************************************************/
	/********************************************************************************************************************************************/
	uint8_t Local_u8CmdPacket[255]={0};

	while(1)
	{
		if ( Global_u8StartEndFlag == 0 )
		{
			STIMERS_voidDelayMS(2000);
			HLCD_voidClearLCD();
			HLCD_voidSetCursor(Location0, LCD_LINE0);
			HLCD_voidSendString((uint8_t *)"-Welcome To V2G-");
			Global_u8StartEndFlag = 1 ;
		}
		memset(Local_u8CmdPacket,0,255);
		MUSART_u8ReceiveArraySynch(USART_1 , &Local_u8CmdPacket[0], 1);
		MUSART_u8ReceiveArraySynch(USART_1 , &Local_u8CmdPacket[1], Local_u8CmdPacket[0] );
		switch (Local_u8CmdPacket[1])
		{
		case SE_PLUG_CABLE      		:      SE_voidPlugCable         (Local_u8CmdPacket)    ; break ;
		case SE_IDENTIFICATION     	    :      SE_voidIdentification    (Local_u8CmdPacket)    ; break ;
		case SE_CHARGE_PARAMETAR        :      SE_voidChargeParameter   (Local_u8CmdPacket)    ; break ;
		case SE_CHARGING_COST           :      SE_voidChargingCost      (Local_u8CmdPacket)    ; break ;
		case SE_START_CHARGING          :      SE_voidStartCharging     (Local_u8CmdPacket)    ; break ;
		case SE_END_CHARGING            :      SE_voidEndCharging       (Local_u8CmdPacket)    ; break ;
		case SE_SEND_ENERGY_AMOUNT      :      SE_voidSendEnergyAmount  (Local_u8CmdPacket)    ; break ;
		default                         :                                                      ; break ;
		}

	}
}
