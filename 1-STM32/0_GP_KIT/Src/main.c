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
#include "rgb565_colors.h"
#include "MPU6050_interface.h"
#include "RTC_interface.h"
#include "ULTRASONIC_interface.h"
#include "INA219_interface.h"

/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "TIMERS_interface.h"

#include "CARKIT_interface.h"
#include "GUI_interface.h"
#include "V2G_interface.h"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/********************************************************************************************************************************************/
/**************************************************** Global Variables **********************************************************************/
/********************************************************************************************************************************************/
#define V2X_NACK_FOUND					    0xA1
#define V2X_CHECK_OBJECT                    0xA2
#define V2X_SPECIAL_VEHICLE                 0xA3
/******************************************************************************************/
/******************************* V2I ******************************************************/
/******************************************************************************************/
/*------------------------------------------------*/
#define V2I_ID_STOP                         0xB0
#define V2I_ID_SPEED_50                     0xB1
#define V2I_ID_SPEED_25                     0xB2
#define V2I_ID_TRAFFIC_RED                  0xB4
#define V2I_ID_TRAFFIC_YELLOW               0xB5
#define V2I_ID_TRAFFIC_GREAN                0xB6
/*------------------------------------------------*/
#define V2P_ID_VEHICLE_PEDESTRIAN           0xD0
/*------------------------------------------------*/

/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/

/********************************************************************************************************************************************/
/**************************************************** Functions *****************************************************************************/
/********************************************************************************************************************************************/
volatile uint8_t Global_u8FoundFlag              = 0 ;
volatile uint8_t Global_u8ReceiveFlag            = 0 ;
volatile uint8_t Global_u8PreviousNotAckORSignID = V2X_NACK_FOUND ;
volatile uint8_t Global_u8GuiSignFlag            = 0 ;
volatile uint8_t Global_u8GuiFristSignFlag       = 0 ;

volatile uint8_t Global_u8SpecialVehicleFlag     = 0 ;
volatile uint8_t Global_u8GUITrafficSignFlag     = 1 ;

void USART1_voidCallBackFunc ( uint8_t Copy_u8NotAckORSignID )
{
	switch (Copy_u8NotAckORSignID)
	{
	case V2X_NACK_FOUND :
		Global_u8FoundFlag   = 0 ;
		Global_u8GuiSignFlag = 1 ;
		MGPIO_u8TogPinValue          ( PORTA , PIN11       );
		MGPIO_u8SetPinValue          ( PORTA , PIN12 , LOW );
		break;
	case V2I_ID_STOP :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 2 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );

		break;
	case V2I_ID_SPEED_50 :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 3 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );
		break;
	case V2I_ID_SPEED_25 :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 4 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );
		break;
	case V2I_ID_TRAFFIC_RED :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 5 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );
		Global_u8SpecialVehicleFlag = 1 ;
		break;
	case V2I_ID_TRAFFIC_YELLOW :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 6 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );
		Global_u8SpecialVehicleFlag = 0 ;
		break;
	case V2I_ID_TRAFFIC_GREAN :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 7 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );
		Global_u8SpecialVehicleFlag = 0 ;
		break;
	case V2P_ID_VEHICLE_PEDESTRIAN :
		Global_u8FoundFlag   = 1 ;
		Global_u8GuiSignFlag = 8 ;
		MGPIO_u8SetPinValue         ( PORTA , PIN11 , LOW  );
		MGPIO_u8SetPinValue         ( PORTA , PIN12 , HIGH );

		break;
	}
	if ( Copy_u8NotAckORSignID != Global_u8PreviousNotAckORSignID)
	{
		Global_u8PreviousNotAckORSignID = Copy_u8NotAckORSignID ;
		Global_u8GuiFristSignFlag = 1 ;
	}
	Global_u8ReceiveFlag = 0 ;
}
void V2X_voidCheckIorP ( void )
{
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(USART_1 , &Local_u8LengthToFollow , 1);
	Local_u8SelectCmd =  V2X_CHECK_OBJECT ;
	MUSART_u8TransmitArraySynch(USART_1 , &Local_u8SelectCmd      , 1);
}
/********************************************************************************************************************************************/
/**************************************************** Call Back Functions *******************************************************************/
/********************************************************************************************************************************************/
volatile uint8_t  Global_u8BluetoothPreviousAction = 0  ;
volatile uint8_t  Global_u8SpeedValue              = 50 ;
void USART2_voidCallBackFunc ( uint8_t Copy_u8BluetoothAction )
{
	/*********************************************************************/
	if ( Copy_u8BluetoothAction != Global_u8BluetoothPreviousAction )
	{
		Global_u8BluetoothPreviousAction = Copy_u8BluetoothAction ;
		switch (Copy_u8BluetoothAction)
		{
		case 'F':
			SCARKIT_voidCarDirection(CAR_FORWARD);
			SGUI_voidUpdateDirection(GUI_FORWARD);
			SGUI_voidUpdateSpeed(Global_u8SpeedValue);
			break;
		case 'B':
			SCARKIT_voidCarDirection(CAR_BACKWARD);
			SGUI_voidUpdateDirection(GUI_BACKWARD);
			SGUI_voidUpdateSpeed(Global_u8SpeedValue);
			break;
		case 'R':
			SCARKIT_voidCarDirection(CAR_RIGHT);
			SGUI_voidUpdateDirection(GUI_RIGHT);
			SGUI_voidUpdateSpeed(Global_u8SpeedValue);
			break;
		case 'L':
			SCARKIT_voidCarDirection(CAR_LEFT);
			SGUI_voidUpdateDirection(GUI_LEFT);
			SGUI_voidUpdateSpeed(Global_u8SpeedValue);
			break;
		case 'S':
			SCARKIT_voidCarDirection(CAR_STOP);
			SGUI_voidUpdateDirection(GUI_STOP);
			SGUI_voidUpdateSpeed(0);
			break;
		case '1':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,10);
			Global_u8SpeedValue=10;
			break;
		case '2':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,20);
			Global_u8SpeedValue=20;
			break;
		case '3':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,30);
			Global_u8SpeedValue=30;
			break;
		case '4':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,40);
			Global_u8SpeedValue=40;
			break;
		case '5':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,50);
			Global_u8SpeedValue=50;
			break;
		case '6':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,60);
			Global_u8SpeedValue=60;
			break;
		case '7':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,70);
			Global_u8SpeedValue=70;
			break;
		case '8':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,80);
			Global_u8SpeedValue=80;
			break;
		case '9':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,90);
			Global_u8SpeedValue=90;
			break;
		case 'q':
			SCARKIT_voidCarSpeed(SPEED_BOTH_WHEEL,100);
			Global_u8SpeedValue=100;
			break;
		}
	}
	/*********************************************************************/
}
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
void V2X_voidSpecialVehicle ( void )
{
	uint8_t Local_u8LengthToFollow  =  0  ;
	uint8_t Local_u8SelectCmd       =  0  ;
	Local_u8LengthToFollow = 1 ;
	MUSART_u8TransmitArraySynch(USART_1 , &Local_u8LengthToFollow , 1);
	Local_u8SelectCmd =  V2X_SPECIAL_VEHICLE ;
	MUSART_u8TransmitArraySynch(USART_1 , &Local_u8SelectCmd      , 1);
}
void EXTI_voidPB15CallBack ( void )
{
	if ( Global_u8SpecialVehicleFlag == 1 )
	{
		V2X_voidSpecialVehicle();
		Global_u8SpecialVehicleFlag = 0;
	}
}
volatile uint8_t Global_u8StartCounter = 0 ;
volatile uint8_t Global_u8ModeFlag     = 0 ;
volatile uint8_t Global_u8InitVoltage  = 5 ;
void EXTI_voidPB14CallBack ( void )
{
	if ( Global_u8StartCounter ==  0 )
	{
		Global_u8StartCounter =  V2G_u8PlugCable();
		STIMERS_voidDelayMS(1000);
		if ( Global_u8StartCounter ==  1 )
		{
			Global_u8StartCounter += V2G_u8Identification();
			STIMERS_voidDelayMS(1000);
			if ( Global_u8StartCounter ==  2 )
			{
				Global_u8StartCounter += V2G_u8ChargeParameter();
				STIMERS_voidDelayMS(1000);
				if ( Global_u8StartCounter ==  3 )
				{
					V2G_voidStartCharging();
					SGUI_voidV2GStartEnd(GUI_V2G_START);
					Global_u8StartCounter++;
					STIMERS_voidDelayMS(1000);
					SGUI_voidV2GBattaryLimit ( Global_u8InitVoltage , 1 );
					STIMERS_voidDelayMS(1000);
					Global_u8ModeFlag  = 1 ;
				}
				else
				{
					Global_u8StartCounter = 0 ;
				}
			}
			else
			{
				Global_u8StartCounter = 0 ;
			}
		}
		else
		{
			Global_u8StartCounter = 0 ;
		}
	}
}
void EXTI_voidPB13CallBack ( void )
{
	if ( Global_u8StartCounter ==  4 )
	{
		V2G_voidSendEnergyAmount();
		STIMERS_voidDelayMS(1000);
		Global_u8StartCounter += V2G_u8ChargingCost();
		STIMERS_voidDelayMS(1000);
		if ( Global_u8StartCounter ==  5 )
		{
			V2G_voidEndCharging ();
			SGUI_voidV2GStartEnd(GUI_V2G_END);
			Global_u8StartCounter = 0 ;
			STIMERS_voidDelayMS(1000);
			SGUI_voidMainFrame( 0 , Global_u8InitVoltage , GUI_STOP );
			STIMERS_voidDelayMS(1000);
			Global_u8ModeFlag  = 0 ;
			Global_u8GuiFristSignFlag = 1 ;
			Global_u8GuiSignFlag = 1 ;
		}
	}
}
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
	MSTK_u8ClockConfig      ( STK_AHB_DIV_8  );
	MNVIC_u8EnableInterrupt ( NVIC_USART1    );
	MNVIC_u8EnableInterrupt ( NVIC_USART2    );
	MNVIC_u8EnableInterrupt ( NVIC_EXTI15_10 );


	/********************************************************************************************************************************************/
	/**************************************************** RCC Configurations ********************************************************************/
	/********************************************************************************************************************************************/
	MRCC_u8SetClockState(HSE,ENABLE);
	MRCC_u8SetSystemClock(HSE);
	MRCC_u8PeripheralsClockState(APB2,PER_AFIO,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPA,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPB,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_IOPC,ENABLE);
	MRCC_u8PeripheralsClockState(APB2,PER_USART1,ENABLE);
	MRCC_u8PeripheralsClockState(APB1,PER_USART2,ENABLE);
	MRCC_u8PeripheralsClockState(APB1,PER_USART3,ENABLE);
	MRCC_u8APB1PeripheralsClockState(PER_TIM2,ENABLE);
	MRCC_u8APB1PeripheralsClockState(PER_TIM3,ENABLE);
	MRCC_u8APB2PeripheralsClockState(PER_SPI1,ENABLE);
	MRCC_u8APB2PeripheralsClockState(PER_ADC1,ENABLE);

	/********************************************************************************************************************************************/
	/**************************************************** MCAL Configurations *******************************************************************/
	/********************************************************************************************************************************************/
	MGPIO_u8SetPinDirection(PORTA, PIN9 , OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_u8SetPinDirection(PORTA, PIN10, INPUT_FLOATING);
	USARTconfig_t UART = {USART_1,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_ENABLE
			,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
			,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,ONE_BIT
			,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART);
	MUSART_u8UsartStatus(USART_1, USART_ENABLE);
	MUSART_u8ReceiveCharNonSynch(USART_1,USART1_voidCallBackFunc);
	/*************************************************************************************************************/
	MGPIO_u8SetPinDirection(PORTA, PIN2 , OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_u8SetPinDirection(PORTA, PIN3 , INPUT_FLOATING);
	USARTconfig_t UART2 = {USART_2,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_ENABLE
			,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
			,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,ONE_BIT
			,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART2);
	MUSART_u8UsartStatus(USART_2, USART_ENABLE);
	MUSART_u8ReceiveCharNonSynch(USART_2,USART2_voidCallBackFunc);
	/*************************************************************************************************************/
	MGPIO_u8SetPinDirection(PORTB, PIN10 , OUTPUT_SPEED_2MHZ_AFPP);
	MGPIO_u8SetPinDirection(PORTB, PIN11 , INPUT_FLOATING);

	USARTconfig_t UART3 = {USART_3,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_DISABLE
						,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
						,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,ONE_BIT
						,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART3);
	MUSART_u8UsartStatus(USART_3, USART_ENABLE);
	/*************************************************************************************************************/
	/*************************************************************************************************************/
	/*************************************************************************************************************/
	/*------------------------------------------------------------------------------------*/
	MAFIO_u8EXTIPortRemap   (AFIO_LINE13  , AFIO_Port_B);
	MAFIO_u8EXTIPortRemap   (AFIO_LINE14  , AFIO_Port_B);
	MAFIO_u8EXTIPortRemap   (AFIO_LINE15  , AFIO_Port_B);
	MGPIO_u8SetPinDirection(PORTB, PIN13 , INPUT_PULL_UP_DOWEN );
	MGPIO_u8SetPinValue    (PORTB, PIN13 , HIGH );
	MGPIO_u8SetPinDirection(PORTB, PIN14 , INPUT_PULL_UP_DOWEN );
	MGPIO_u8SetPinValue    (PORTB, PIN14 , HIGH );
	MGPIO_u8SetPinDirection(PORTB, PIN15 , INPUT_PULL_UP_DOWEN );
	MGPIO_u8SetPinValue    (PORTB, PIN15 , HIGH );
	EXTI_config_t EXTI_PB13 = { LINE13 , RISING , EXTI_ENABLE , EXTI_voidPB13CallBack };
	EXTI_config_t EXTI_PB14 = { LINE14 , RISING , EXTI_ENABLE , EXTI_voidPB14CallBack };
	EXTI_config_t EXTI_PB15 = { LINE15 , RISING , EXTI_ENABLE , EXTI_voidPB15CallBack };
	MEXTI_u8Config ( &EXTI_PB13 );
	MEXTI_u8Config ( &EXTI_PB14 );
	MEXTI_u8Config ( &EXTI_PB15 );
	/*------------------------------------------------------------------------------------*/
	/********************************************************************************************************************************************/
	/**************************************************** HAL Configurations ********************************************************************/
	/********************************************************************************************************************************************/

	/********************************************************************************************************************************************/
	/**************************************************** SERVIES Configurations ****************************************************************/
	/********************************************************************************************************************************************/
	SCARKIT_voidInit();
	SCARKIT_voidCarDirection ( CAR_STOP );

    Global_u8InitVoltage = SCARKIT_u8GetVoltageValue ( );
	SGUI_voidInit();
	SGUI_voidMainFrame ( 0 , Global_u8InitVoltage , GUI_STOP   );


	MGPIO_u8SetPinDirection(PORTA, PIN11 , OUTPUT_SPEED_10MHZ_PP);
	MGPIO_u8SetPinDirection(PORTA, PIN12 , OUTPUT_SPEED_10MHZ_PP);

	/********************************************************************************************************************************************/
	/**************************************************** Loop **********************************************************************************/
	/********************************************************************************************************************************************/

	while(1)
	{
		/********************************************************************************/
		if ( Global_u8ModeFlag == 1 )
		{
			V2G_voidSendEnergyAmount();
			STIMERS_voidDelayMS(5000);
		}
		else
		{
			/*********************************************************************/
			if ( Global_u8ReceiveFlag == 0 )
			{
				V2X_voidCheckIorP();
				Global_u8ReceiveFlag = 1 ;
			}
			if ( Global_u8FoundFlag == 1 )
			{
				STIMERS_voidDelayMS(5000);
			}
			else
			{
				STIMERS_voidDelayMS(2000);
			}
			/*********************************************************************/
			if ( Global_u8GuiFristSignFlag == 1 )
			{
				switch (Global_u8GuiSignFlag)
				{
				case 1 :
					SGUI_voidMainFrame( 0 , Global_u8InitVoltage , GUI_STOP );
					Global_u8GUITrafficSignFlag = 1 ;
					break;
				case 2 :
					SGUI_voidV2IStopSign();
					break;
				case 3 :
					SGUI_voidV2ISpeedSign(GUI_ID_SPEED_50);
					break;
				case 4 :
					SGUI_voidV2ISpeedSign(GUI_ID_SPEED_25);
					break;
				case 5 :
					SGUI_voidV2ITrafficSign( GUI_ID_TRAFFIC_RED    , Global_u8GUITrafficSignFlag );
					Global_u8GUITrafficSignFlag = 0 ;
					break;
				case 6 :
					SGUI_voidV2ITrafficSign( GUI_ID_TRAFFIC_YELLOW , Global_u8GUITrafficSignFlag );
					Global_u8GUITrafficSignFlag = 0 ;
					break;
				case 7 :
					SGUI_voidV2ITrafficSign( GUI_ID_TRAFFIC_GREAN  , Global_u8GUITrafficSignFlag );
					Global_u8GUITrafficSignFlag = 0 ;
					break;
				case 8 :
					SGUI_voidV2PPedestrian();
					break;

				}
				Global_u8GuiFristSignFlag = 0 ;
			}
			/*********************************************************************/
		}
		/********************************************************************************/
		uint8_t Local_u8Voltage = SCARKIT_u8GetVoltageValue();
		if ( (Local_u8Voltage - Global_u8InitVoltage) >= 3 )
		{
			if ( Global_u8ModeFlag == 1 )
			{
				SGUI_voidV2GBattaryLimit ( Local_u8Voltage , 0 );
			}
			else
			{
				SGUI_voidUpdateBattaryVolt(Local_u8Voltage);
			}
			Global_u8InitVoltage = Local_u8Voltage ;
		}
		/********************************************************************************/

	}
}
