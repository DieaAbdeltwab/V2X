#ifndef	I2C_INTERFACE_H
#define I2C_INTERFACE_H



/******************************************************************************/
/************************ @I2Cindex_t *****************************************/
/******************************************************************************/
typedef enum{
			I2C_1   =0,
			I2C_2

}I2Cindex_t;
/******************************************************************************/
/************************ @MasterMode_t ***************************************/
/******************************************************************************/
typedef enum{
			SM   =0,
			FM
}MasterMode_t ;
/******************************************************************************/
/************************ @ClockSpeed_t ***************************************/
/******************************************************************************/
typedef enum{
			SCL_SM_50K    =50000,
			SCL_SM_100K   =100000
}ClockSpeed_t ;
/******************************************************************************/
/************************ @Clock_Stretching_t *********************************/
/******************************************************************************/
typedef enum{
			STRETCHING_ENABLE   =0,
			STRETCHING_DISABLE
}ClockStretching_t ;

/******************************************************************************/
/************************ @I2Cmode_t ******************************************/
/******************************************************************************/
typedef enum{
			I2C_MODE  =0,
			SMBUS_MODE
}I2Cmode_t ;
/******************************************************************************/
/************************ @Acknowledge_t **************************************/
/******************************************************************************/
typedef enum{
			ACK_DISABBLE  =0,
			ACK_ENABLE
}Acknowledge_t ;
/******************************************************************************/
/************************ @GeneralCall_t **************************************/
/******************************************************************************/
typedef enum{
			ENGC_DISABBLE  =0,
			ENGC_ENABLE
}GeneralCall_t ;

/******************************************************************************/
/************************ @StopCondition_t ************************************/
/******************************************************************************/
typedef enum{
			STOP_DISABBLE  =0,
			STOP_ENABLE
}StopCondition_t ;
/******************************************************************************/
/************************ @StopCondition_t ************************************/
/******************************************************************************/
typedef enum{
			REPEAT_DISABBLE  =0,
			REPEAT_ENABLE
}StartRepeat_t ;
/******************************************************************************/
/************************ @StopCondition_t ************************************/
/******************************************************************************/
typedef enum{
			I2C_DMA_DISABLE  =0,
			I2C_DMA_ENABLE
}DMArequests_t ;
/******************************************************************************/
/************************ @I2Cconfig_t ****************************************/
/******************************************************************************/
typedef struct{

	I2Cindex_t               I2Cindex        ;
	MasterMode_t             MasterMode      ;
	ClockSpeed_t             ClockSpeed      ;
	ClockStretching_t        Clock_Stretching;
	I2Cmode_t                I2Cmode         ;
	Acknowledge_t            Acknowledge     ;
	GeneralCall_t            GeneralCall     ;

}I2Cconfig_t;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MI2C_u8SetConfiguration
 * @brief          : initialization Value of I2C Configuration
 * @param[in]      : I2Cconfig  --> get option from @I2Cconfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t MI2C_u8SetConfiguration ( const I2Cconfig_t* I2Cconfig );

/**
 ******************************************************************************
 * @fn             : MI2C_u8SendSynch
 * @brief          : Send Synchronization Function
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_u16SlaveAddress  --> Set Slave Address
 * @param[in]      : Copy_pu8DataToTransmit--> Get Data To Transmit
 * @param[in]      : Copy_u32DataLenght    --> Set Data Lenght
 * @param[in]      : Copy_StopCondition    --> Get option From @StopCondition_t enum
 * @param[in]      : Copy_StartRepeat      --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MI2C_u8SendSynch    ( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress ,uint8_t *Copy_pu8DataToTransmit , uint32_t Copy_u32DataLenght
		                    , StopCondition_t Copy_StopCondition , StartRepeat_t Copy_StartRepeat);
/**
 ******************************************************************************
 * @fn             : MI2C_u8ReceiveSynch
 * @brief          : Receive Synchronization Function
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_u16SlaveAddress  --> Set Slave Address
 * @param[out]     : Copy_pu8DataToReveive --> Get Data To Reveive
 * @param[in]      : Copy_u32DataLenght    --> Set Data Lenght
 * @param[in]      : Copy_StopCondition    --> Get option From @StopCondition_t enum
 * @param[in]      : Copy_StartRepeat      --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MI2C_u8ReceiveSynch ( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress ,uint8_t *Copy_pu8DataToReveive , uint32_t Copy_u32DataLenght
		                    , StopCondition_t Copy_StopCondition , StartRepeat_t Copy_StartRepeat);
/**
 ******************************************************************************
 * @fn             : MI2C_u8DMArequests
 * @brief          : DMA requests
 * @param[in]      : Copy_I2Cindex  --> get option from @I2Cindex_t  enum
 * @param[in]      : Copy_DMArequests --> get option from @DMArequests_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t MI2C_u8DMArequests (  I2Cindex_t Copy_I2Cindex , DMArequests_t Copy_DMArequests );

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
#endif
