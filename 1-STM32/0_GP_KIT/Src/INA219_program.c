/**
 ******************************************************************************
 * @file           : INA219_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 21/10/2023
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
#include "I2C_INTERFACE.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "INA219_interface.h"
#include "INA219_private.h"
#include "INA219_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
uint16_t ina219_calibrationValue;
int16_t ina219_currentDivider_mA;
int16_t ina219_powerMultiplier_mW;
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
uint16_t Read16( uint8_t Register)
{
	uint8_t Value[2];

	//HAL_I2C_Mem_Read(ina219->ina219_i2c, (INA219_ADDRESS<<1), Register, 1, Value, 2, 1000);
	MI2C_u8SendSynch    ( INA219_I2C , INA219_ADDRESS ,  &Register         , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( INA219_I2C , INA219_ADDRESS ,  Value             , 2 , STOP_ENABLE , REPEAT_ENABLE  );
	return ((Value[0] << 8) | Value[1]);
}


void Write16( uint8_t Register, uint16_t Value)
{

	uint8_t addr[2];
	addr[0] = (Value >> 8) & 0xff;  // upper byte
	addr[1] = (Value >> 0) & 0xff; // lower byte
	//HAL_I2C_Mem_Write(ina219->ina219_i2c, (INA219_ADDRESS<<1), Register, 1, (uint8_t*)addr, 2, 1000);
	MI2C_u8SendSynch    ( INA219_I2C , INA219_ADDRESS ,  &Register         , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8SendSynch    ( INA219_I2C , INA219_ADDRESS ,  (uint8_t*)addr    , 2 , STOP_ENABLE , REPEAT_ENABLE  );
}
void INA219_setCalibration( uint16_t CalibrationData)
{
	Write16(INA219_REG_CALIBRATION, CalibrationData);
}

uint16_t INA219_getConfig(void)
{
	uint16_t result = Read16( INA219_REG_CONFIG);
	return result;
}

void INA219_setConfig( uint16_t Config)
{
	Write16( INA219_REG_CONFIG, Config);
}
void HINA219_voidInit (void)
{
	ina219_currentDivider_mA = 0;
	ina219_powerMultiplier_mW = 0;
	MSTK_u8ClockConfig(STK_AHB_DIV_8);
	/*********************************************************************************************/
	MGPIO_u8SetPinDirection(INA219_I2C_PORT, INA219_I2C_SDA_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (INA219_I2C_PORT, INA219_I2C_SDA_PIN, INA219_I2C_PULL);
	MGPIO_u8SetPinDirection(INA219_I2C_PORT, INA219_I2C_SCL_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (INA219_I2C_PORT, INA219_I2C_SCL_PIN, INA219_I2C_PULL);
	I2Cconfig_t I2cCinfig ={INA219_I2C,SM,SCL_SM_100K,STRETCHING_ENABLE,I2C_MODE,ACK_ENABLE,ENGC_ENABLE};
	MI2C_u8SetConfiguration(&I2cCinfig);
	/*********************************************************************************************/
	Write16( INA219_REG_CONFIG, INA219_CONFIG_RESET);
	MSTK_u8BusyWait(5000);
	/****************************************************************************************/
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
	             INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	             INA219_CONFIG_SADCRES_12BIT_1S_532US |
	             INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219_calibrationValue = 4096;
	ina219_currentDivider_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
	ina219_powerMultiplier_mW = 2; // Power LSB = 1mW per bit (2/1)

	INA219_setCalibration( ina219_calibrationValue);
	INA219_setConfig( config);

}
uint16_t INA219_ReadBusVoltage()
{
	uint16_t result = Read16( INA219_REG_BUSVOLTAGE);

	return ((result >> 3  ) * 4);

}
int16_t INA219_ReadCurrent_raw()
{
	int16_t result = Read16( INA219_REG_CURRENT);

	return (result );
}
int16_t INA219_ReadCurrent()
{
	int16_t result = INA219_ReadCurrent_raw();

	return (result / ina219_currentDivider_mA );
}

uint16_t INA219_ReadShuntVolage()
{
	uint16_t result = Read16(INA219_REG_SHUNTVOLTAGE);

	return (result * 0.01 );
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


