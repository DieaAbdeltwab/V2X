#ifndef	I2C_PRIVATE_H
#define I2C_PRIVATE_H


/******************************************************************************/
/************************ @FunctionalState_t *********************************/
/******************************************************************************/
typedef enum{
			FUNC_STATE_DISABBLE  =0,
			FUNC_STATE_ENABLE
}FunctionalState_t ;
/******************************************************************************/
/************************ @FlagStatus_t **************************************/
/******************************************************************************/
typedef enum{
			FLAG_RESET  =0,
			FLAG_SET
}FlagStatus_t ;
/******************************************************************************/
/************************ @FlagStatus_t ***************************************/
/******************************************************************************/
typedef enum{
			FLAG_BUSY              =0,
			FLAG_EV5                 ,
			FLAG_EV6                 ,
			MASTER_BYTE_TRANSMITTER  ,
			FLAG_EV8                 ,
			FLAG_EV8_1               ,
			FLAG_EV7

}Flag_t ;
/******************************************************************************/
/************************ @FlagStatus_t ***************************************/
/******************************************************************************/
typedef enum{
			TRANSMITTER  =0,
			RECEIVER

}Direction_t ;
/*************************************************************************************************************************************/
/************************************************** Static Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MI2C_u8GetFlagStatus
 * @brief          : Get Flag Status
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_Flag  --> Get option From @Flag_t enum
 * @retval         : FlagStatus_t --> enum
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static FlagStatus_t MI2C_u8GetFlagStatus( I2Cindex_t Copy_I2Cindex , Flag_t Copy_Flag);
/**
 ******************************************************************************
 * @fn             : MI2C_u8GenerateStop
 * @brief          : Generate Stop
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_StopCondition     --> Get option From @StopCondition_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8GenerateStop( I2Cindex_t Copy_I2Cindex , StopCondition_t Copy_StopCondition );
/**
 ******************************************************************************
 * @fn             : MI2C_u8GenerateStart
 * @brief          : Generate Start
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_FunctionalState --> Get option From @FunctionalState_t enum
 * @param[in]      : Copy_StartRepeat     --> Get option From @StartRepeat_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8GenerateStart( I2Cindex_t Copy_I2Cindex , FunctionalState_t Copy_FunctionalState , StartRepeat_t Copy_StartRepeat);
/**
 ******************************************************************************
 * @fn             : MI2C_u8SendAddress
 * @brief          : Send Address
 * @param[in]      : Copy_I2Cindex   --> Get option From @I2Cindex_t enum
 * @param[in]      : Copy_Direction  --> Get option From @Direction_t enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8SendAddress( I2Cindex_t Copy_I2Cindex , uint16_t Copy_u16SlaveAddress , Direction_t Copy_Direction );
/**
 ******************************************************************************
 * @fn             : MI2C_u8AcknowledgeConfig
 * @brief          : Acknowledge Config
 * @param[in]      : Copy_I2Cindex         --> Get option From @I2Cindex_t enum
 * @param[in]      : Acknowledge_t  --> Set Slave Address
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
static uint8_t MI2C_u8AcknowledgeConfig( I2Cindex_t Copy_I2Cindex , Acknowledge_t Copy_Acknowledge );
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/


/************************************************************************************/
/********************************  Flags ********************************************/
/************************************************************************************/
#define I2C_EVENT_MASTER_BYTE_TRANSMITTER  ((uint32_t)0x00070080)

/************************************************************************************/
/******************************** Register Bits *************************************/
/************************************************************************************/
#define I2C_SR2_BUSY         		        1

#define I2C_SR1_SB          		        0
#define I2C_SR1_ADDR         		        1
#define I2C_SR1_RxNE         		        6
#define I2C_SR1_TxE         		        7

#define I2C_CR1_PE                          0
#define I2C_CR1_SMBUS                       1
#define I2C_CR1_ENGC                        6
#define I2C_CR1_NOSTRETCH                   7
#define I2C_CR1_START       		        8
#define I2C_CR1_STOP         		        9
#define I2C_CR1_ACK          		        10
#define I2C_CR1_SWRST                       15

#define I2C_CR2_FREQ                        0
#define I2C_CR2_DMAEN                       11

#define I2C_CCR_F_S                         15
/************************************************************************************/
/******************************** Flags Mask ****************************************/
/************************************************************************************/

#define I2C_BYTE_TRANSMITTER_MASK            16
#define I2C_MASTER_BYTE_TRANSMITTER_MASK     0x00FFFFFF
#define I2C_STOP_MASK                        0b1
#define I2C_START_MASK                       0b1
#define I2C_ACK_MASK                         0b1
#define I2C_SLAVE_ADDRESS_MASK               1
#define I2C_SLAVE_ADDRESS_RX_TX_BIT          0
#define I2C_ENGC_MASK                        0b1
#define I2C_NOSTRETCH_MASK                   0b1
#define I2C_SMBUS_MASK                       0b1
#define I2C_TRISE_MASK                       1
#define I2C_F_S_MASK                         1
#define I2C_FREQ_MASK                        0b111111
#define I2C_SWRST_MASK                       0b1

#define I2C_DMA_MASK                         0b1
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/






#endif
