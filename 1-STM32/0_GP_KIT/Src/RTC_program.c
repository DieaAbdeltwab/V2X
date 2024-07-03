/**
 ******************************************************************************
 * @file           : RTC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : 
 * @date           : 22/8/2023
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
#include <string.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_interface.h"
#include "I2C_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_interface.h"
#include "RTC_private.h"
#include "RTC_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HRTC_u8Init
 * @brief          : initialization RTC
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_u8Init(void)
{
	/*********************************************************************************************/
	MGPIO_u8SetPinDirection(RTC_I2C_PORT, RTC_I2C_SDA_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (RTC_I2C_PORT, RTC_I2C_SDA_PIN, RTC_I2C_PULL);
	MGPIO_u8SetPinDirection(RTC_I2C_PORT, RTC_I2C_SCL_PIN, OUTPUT_SPEED_10MHZ_AFOD);
	MGPIO_u8SetPinValue    (RTC_I2C_PORT, RTC_I2C_SCL_PIN, RTC_I2C_PULL);
	/*********************************************************************************************/
	I2Cconfig_t I2cCinfig ={RTC_I2C,SM,SCL_SM_100K,STRETCHING_ENABLE,I2C_MODE,ACK_ENABLE,ENGC_ENABLE};
	MI2C_u8SetConfiguration(&I2cCinfig);
	/*********************************************************************************************/
	RTC_voidWriteRegister( RTC_SEC_MASK , RTC_ADDRESS_SEC );
	/*********************************************************************************************/
}
/**
 ******************************************************************************
 * @fn             : HRTC_u8GetRtcStatus
 * @brief          : Get Rtc Status
 * @param[in]      : Copy_u8Status --> Get Value
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_u8GetRtcStatus ( uint8_t *Copy_u8Status )
{
	*Copy_u8Status = GET_BIT( RTC_voidReadRegister( RTC_ADDRESS_SEC ) , RTC_SEC_CH_BIT );
}
/**
 ******************************************************************************
 * @fn             : HRTC_voidSetCurrentTime
 * @brief          : Set Current Time
 * @param[in]      : RTC_time_t --> Set Value @RTC_time struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_voidSetCurrentTime ( RTC_time_t *RTC_time )
{
	/*********************************************************************************************/
	uint8_t Local_u8Second = BinaryToBCD(RTC_time->seconds);
	Local_u8Second &= ~(RTC_SEC_CH_MASK<<RTC_SEC_CH_BIT);
	RTC_voidWriteRegister(Local_u8Second , RTC_ADDRESS_SEC );
	/*********************************************************************************************/
	RTC_voidWriteRegister(BinaryToBCD(RTC_time->minutes) , RTC_ADDRESS_MIN );
	/*********************************************************************************************/
	uint8_t Local_u8Hours = BinaryToBCD(RTC_time->hours);
	if ( RTC_time-> time_format == _24HRS )
	{
		Local_u8Hours &= ~(RTC_HRS_12_24_MASK<<RTC_HRS_12_24_BIT);
	}
	else
	{
		Local_u8Hours |= (RTC_HRS_12_24_MASK<<RTC_HRS_12_24_BIT);
		if (RTC_time->time_format == _12HRS_PM)
		{
			Local_u8Hours |=   (RTC_HRS_PM_AM_MASK<<RTC_HRS_PM_AM_BIT);
		}
		else
		{
			Local_u8Hours &=  ~ (RTC_HRS_PM_AM_MASK<<RTC_HRS_PM_AM_BIT);
		}
	}
	RTC_voidWriteRegister(Local_u8Hours , RTC_ADDRESS_HRS );
	/*********************************************************************************************/
}
/**
 ******************************************************************************
 * @fn             : HRTC_voidGetCurrentTime
 * @brief          : Get Current Time
 * @param[in]      : RTC_time_t --> Get Value @RTC_time struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_voidGetCurrentTime(RTC_time_t *RTC_time)
{
	uint8_t Local_u8RegAddress=RTC_ADDRESS_SEC;
	uint8_t Local_u8Data[4];
	MI2C_u8SendSynch    ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS ,&Local_u8RegAddress , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS , Local_u8Data      , 4 , STOP_ENABLE , REPEAT_ENABLE  );


	/*********************************************************************************************/
	uint8_t Local_u8Second = Local_u8Data[0];
	Local_u8Second &= ~(RTC_SEC_CH_MASK<<RTC_SEC_CH_BIT);
	RTC_time->seconds = BCDToBinary(Local_u8Second);
	/*********************************************************************************************/
	RTC_time->minutes = BCDToBinary(Local_u8Data[1]);
	/*********************************************************************************************/
	uint8_t Local_u8Hours  = Local_u8Data[3] ;
	if (  Local_u8Hours & (RTC_HRS_12_24_MASK << RTC_HRS_12_24_BIT ))
	{
		if (  Local_u8Hours & (RTC_HRS_PM_AM_MASK << RTC_HRS_PM_AM_BIT ) )
		{

			RTC_time->time_format = _12HRS_PM;
		}
		else
		{
			RTC_time->time_format = _12HRS_AM;

		}
		Local_u8Hours &= ~(RTC_HRS_12_24_PM_AM_MASK<<RTC_HRS_PM_AM_BIT);
	}
	else
	{
		RTC_time->time_format = _24HRS ;

	}
	RTC_time->hours   = BCDToBinary(Local_u8Hours);
	/*********************************************************************************************/
}
/**
 ******************************************************************************
 * @fn             : HRTC_voidSetCurrentDate
 * @brief          : Set Current Date
 * @param[in]      : RTC_data_t --> Set Value @RTC_date struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_voidSetCurrentDate(RTC_date_t *RTC_date)
{
	RTC_voidWriteRegister( BinaryToBCD(RTC_date->date) ,  RTC_ADDRESS_DATE  );
	RTC_voidWriteRegister( BinaryToBCD(RTC_date->month),  RTC_ADDRESS_MONTH );
	RTC_voidWriteRegister( BinaryToBCD(RTC_date->year) ,  RTC_ADDRESS_YEAR  );
	RTC_voidWriteRegister( BinaryToBCD(RTC_date->day)  ,  RTC_ADDRESS_DAY   );
}
/**
 ******************************************************************************
 * @fn             : HRTC_voidGetCurrentDate
 * @brief          : Get Current Date
 * @param[in]      : RTC_data_t --> Get Value @RTC_date struct
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_voidGetCurrentDate(RTC_date_t *RTC_date)
{
	uint8_t Local_u8RegAddress=RTC_ADDRESS_DAY;
	uint8_t Local_u8Data[4];
	MI2C_u8SendSynch    ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS ,&Local_u8RegAddress , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS , Local_u8Data      , 4 , STOP_ENABLE , REPEAT_ENABLE  );

	RTC_date->date   = BCDToBinary (Local_u8Data[1]);
	RTC_date->month  = BCDToBinary (Local_u8Data[2]);
	RTC_date->year   = BCDToBinary (Local_u8Data[3]);
	RTC_date->day    = BCDToBinary (Local_u8Data[0]);
}
/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : RTC_voidWriteRegister
 * @brief          : Write Data on Rtc Register
 * @param[in]      : Copy_u8Value --> Set Value
 * @param[in]      : Copy_u8RegAddress --> Set Register Address
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static void RTC_voidWriteRegister( uint8_t Copy_u8Value , uint8_t Copy_u8RegAddress )
{
    uint8_t Local_Au8TransmitArray[2] ;
    Local_Au8TransmitArray[0] = Copy_u8RegAddress ;
    Local_Au8TransmitArray[1] = Copy_u8Value ;
	MI2C_u8SendSynch ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS , Local_Au8TransmitArray , 2 , STOP_ENABLE , REPEAT_DISABBLE );

}
/**
 ******************************************************************************
 * @fn             : RTC_voidReadRegister
 * @brief          : Read Data From Rtc Register
 * @param[in]      : Copy_u8RegAddress --> Set Register Address
 * @retval         : Register Value u8
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t RTC_voidReadRegister( uint8_t Copy_u8RegAddress )
{
	uint8_t Local_u8Data ;
	MI2C_u8SendSynch    ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS ,&Copy_u8RegAddress , 1 , STOP_ENABLE , REPEAT_DISABBLE);
	MI2C_u8ReceiveSynch ( RTC_I2C , RTC_I2C_SLAVE_ADDRESS ,&Local_u8Data      , 1 , STOP_ENABLE , REPEAT_ENABLE  );
	return Local_u8Data ;

}
/**
 ******************************************************************************
 * @fn             : BinaryToBCD
 * @brief          : Convert From Binary To BCD
 * @param[in]      : Copy_u8Vlaue --> Set Binary Vlaue
 * @retval         : Get BCD Value u8
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t BinaryToBCD (uint8_t Copy_u8BinaryVlaue )
{
	uint8_t Local_u8Tens , Local_u8Ones ,Local_u8BCD ;
	Local_u8BCD = Copy_u8BinaryVlaue ;
	if ( Copy_u8BinaryVlaue >= 10 )
	{
		Local_u8Tens = Copy_u8BinaryVlaue/10;
		Local_u8Ones = Copy_u8BinaryVlaue%10;
		Local_u8BCD = (uint8_t)((Local_u8Tens<<4) | Local_u8Ones) ;
	}
	return Local_u8BCD ;

}
/**
 ******************************************************************************
 * @fn             : BinaryToBCD
 * @brief          : Convert From Binary To BCD
 * @param[in]      : Copy_u8Vlaue --> Set   Vlaue
 * @retval         : Get  Binary Value u8
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t BCDToBinary (uint8_t Copy_u8BcdVlaue )
{
	uint8_t Local_u8Tens , Local_u8Ones ,Local_u8Binary ;
	Local_u8Tens = (uint8_t)((Copy_u8BcdVlaue >> 4) * 10) ;
	Local_u8Ones = Copy_u8BcdVlaue & (uint8_t)0x0F;
	Local_u8Binary = Local_u8Tens + Local_u8Ones ;
	return Local_u8Binary ;

}

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

