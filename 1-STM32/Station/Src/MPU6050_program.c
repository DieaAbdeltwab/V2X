/**
 ******************************************************************************
 * @file           : MPU6050_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 11/9/2023
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
//#include "STK_INTERFACE.h"
#include "I2C_INTERFACE.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "MPU6050_interface.h"
#include "MPU6050_private.h"
#include "MPU6050_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MPU6050_voidInit
 * @brief          : initialization MPU6050
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HMPU6050_voidInit (void)
{
	/*********************************************************************************************/
	uint8_t Local_u8CheckAdress;
	uint8_t Local_Au8RegDataTemp[2];
	uint8_t Local_u8RegTemp=MPU6050_WHO_AM_I_REG;
	/*********************************************************************************************/
	//MSTK_u8ClockConfig		(STK_AHB_DIV_8);
	/*********************************************************************************************/
	MGPIO_u8SetPinDirection(MPU6050_I2C_PORT, MPU6050_I2C_SDA_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (MPU6050_I2C_PORT, MPU6050_I2C_SDA_PIN, MPU6050_I2C_PULL);
	MGPIO_u8SetPinDirection(MPU6050_I2C_PORT, MPU6050_I2C_SCL_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (MPU6050_I2C_PORT, MPU6050_I2C_SCL_PIN, MPU6050_I2C_PULL);
	I2Cconfig_t I2cCinfig ={MPU6050_I2C,SM,SCL_SM_100K,STRETCHING_ENABLE,I2C_MODE,ACK_ENABLE,ENGC_ENABLE};
	MI2C_u8SetConfiguration(&I2cCinfig);
	/*********************************************************************************************/
	MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS , &Local_u8RegTemp     , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( MPU6050_I2C , MPU6050_I2C_ADDRRESS , &Local_u8CheckAdress , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
	if (Local_u8CheckAdress == MPU6050_I2C_ADDRRESS)  // 0x68 will be returned by the sensor if everything goes well
	{
		/*******************************************************************************************************/
		Local_Au8RegDataTemp[0]=MPU6050_PWR_MGMT_1_REG;
		Local_Au8RegDataTemp[1]=MPU6050_PWR_MGMT_1_DATA;
		MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,Local_Au8RegDataTemp , 2 , STOP_ENABLE , REPEAT_DISABBLE  );
		//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
		/*******************************************************************************************************/
		Local_Au8RegDataTemp[0]=MPU6050_SMPLRT_DIV_REG;
		Local_Au8RegDataTemp[1]=MPU6050_SMPLRT_DIV_DATA;
		MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,Local_Au8RegDataTemp  , 2 , STOP_ENABLE , REPEAT_DISABBLE);
		//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
		/*******************************************************************************************************/
		Local_Au8RegDataTemp[0]=MPU6050_ACCEL_CONFIG_REG;
		Local_Au8RegDataTemp[1]=MPU6050_ACCEL_CONFIG_DATA;
		MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,Local_Au8RegDataTemp  , 2 , STOP_ENABLE , REPEAT_DISABBLE);
		//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
		/*******************************************************************************************************/
		Local_Au8RegDataTemp[0]=MPU6050_GYRO_CONFIG_REG;
		Local_Au8RegDataTemp[1]=MPU6050_GYRO_CONFIG_DATA;
		MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,Local_Au8RegDataTemp  , 2 , STOP_ENABLE , REPEAT_DISABBLE);
		//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
		/*******************************************************************************************************/
	}

}
/**
 ******************************************************************************
 * @fn             : HMPU6050_voidReadAccel
 * @brief          : Get Read Accel  X , Y , Z
 * @param[OUT]     : MPU6050_ Accel --> Get Values @MPU6050_Accel_t struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HMPU6050_voidReadAccel (MPU6050_Accel_t *MPU6050_Accel)
{
	/*********************************************************************************************/
	int16_t Local_int16AccelX = 0 , Local_int16AccelY = 0 ,Local_int16AccelZ = 0;
	uint8_t Local_Au8RecData[6];
	uint8_t Local_u8RegTemp=MPU6050_ACCEL_XOUT_H_REG;
	/*********************************************************************************************/
	MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS , &Local_u8RegTemp  , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,  Local_Au8RecData , 6 , STOP_ENABLE , REPEAT_ENABLE  );
	//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
	/*********************************************************************************************/
	Local_int16AccelX = (int16_t)(Local_Au8RecData[0] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [1]);
	Local_int16AccelY = (int16_t)(Local_Au8RecData[2] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [3]);
	Local_int16AccelZ = (int16_t)(Local_Au8RecData[4] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [5]);
	MPU6050_Accel->ACCEL_X = Local_int16AccelX/MPU6050_ACCEL_DIVIDE;
	MPU6050_Accel->ACCEL_Y = Local_int16AccelY/MPU6050_ACCEL_DIVIDE;
	MPU6050_Accel->ACCEL_Z = Local_int16AccelZ/MPU6050_ACCEL_DIVIDE;
	/*********************************************************************************************/
}

/**
 ******************************************************************************
 * @fn             : HMPU6050_voidReadGyro
 * @brief          : Get Read Gyro  X , Y , Z
 * @param[OUT]     : MPU6050_ Gyro --> Get Values @MPU6050_Gyro_t struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HMPU6050_voidReadGyro (MPU6050_Gyro_t *MPU6050_Gyro )
{
	/*********************************************************************************************/
	int16_t Local_int16GyroX = 0 , Local_int16GyroY = 0 , Local_int16GyroZ = 0;
	uint8_t Local_Au8RecData[6];
	uint8_t Local_u8RegTemp=MPU6050_GYRO_XOUT_H_REG;
	/*********************************************************************************************/
	MI2C_u8SendSynch    ( MPU6050_I2C , MPU6050_I2C_ADDRRESS , &Local_u8RegTemp  , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( MPU6050_I2C , MPU6050_I2C_ADDRRESS ,  Local_Au8RecData , 6 , STOP_ENABLE , REPEAT_ENABLE  );
	//MSTK_u8Delayms(MPU6050_SEND_RECEIVE_DELAY);
	/*********************************************************************************************/
	Local_int16GyroX = (int16_t)(Local_Au8RecData[0] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [1]);
	Local_int16GyroY = (int16_t)(Local_Au8RecData[2] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [3]);
	Local_int16GyroZ = (int16_t)(Local_Au8RecData[4] << MPU6050_ACCESS_HIGH_REG | Local_Au8RecData [5]);
	MPU6050_Gyro->GYRO_X = Local_int16GyroX/MPU6050_GYRO_DIVIDE;
	MPU6050_Gyro->GYRO_Y = Local_int16GyroY/MPU6050_GYRO_DIVIDE;
	MPU6050_Gyro->GYRO_Z = Local_int16GyroZ/MPU6050_GYRO_DIVIDE;
	/*********************************************************************************************/

}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


