#ifndef  RTC_PRIVATE_H
#define  RTC_PRIVATE_H

/******************************************************************************/
/************************ Register Bit ****************************************/
/******************************************************************************/
#define RTC_HRS_PM_AM_BIT            5
#define RTC_HRS_12_24_BIT            6
#define RTC_SEC_CH_BIT               7
/******************************************************************************/
/************************ Mask ************************************************/
/******************************************************************************/
#define RTC_SEC_CH_MASK              0b1
#define RTC_SEC_MASK                 0x00
#define RTC_HRS_12_24_PM_AM_MASK     0b11
#define RTC_HRS_PM_AM_MASK           0b1
#define RTC_HRS_12_24_MASK           0b1

/******************************************************************************/
/************************ Addresses *******************************************/
/******************************************************************************/
#define RTC_ADDRESS_SEC               0x00
#define RTC_ADDRESS_MIN               0x01
#define RTC_ADDRESS_HRS               0x02
#define RTC_ADDRESS_DAY               0x03
#define RTC_ADDRESS_DATE              0x04
#define RTC_ADDRESS_MONTH             0x05
#define RTC_ADDRESS_YEAR              0x06
#define RTC_I2C_SLAVE_ADDRESS         0b01101000
/*************************************************************************************************************************************/
/********************************************************* Static Functions Prototype ************************************************/
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
static void RTC_voidWriteRegister( uint8_t Copy_u8Value , uint8_t Copy_u8RegAddress );
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
static uint8_t RTC_voidReadRegister( uint8_t Copy_u8RegAddress );
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
static uint8_t BinaryToBCD (uint8_t Copy_u8BinaryVlaue );
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
static uint8_t BCDToBinary (uint8_t Copy_u8BcdVlaue );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/









#endif
