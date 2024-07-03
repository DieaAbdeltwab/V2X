/**
 ******************************************************************************
 * @file           : TFT_interface.h
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
#ifndef  TFT_INTERFACE_H
#define  TFT_INTERFACE_H


/******************************************************************************/
/************************ Color Constants *************************************/
/******************************************************************************/
#define TFT_BLACK        0x0000
#define TFT_BLUE         0x001F
#define TFT_RED          0xF800
#define TFT_GREEN        0x0400
#define TFT_LIME         0x07E0
#define TFT_CYAN         0x07FF
#define TFT_MAGENTA      0xF81F
#define TFT_YELLOW       0xFFE0
#define TFT_WHITE        0xFFFF


#define TFT_Bright_RED      0xF840
#define TFT_DARK_RED        0x9800
#define TFT_Bright_GREEN    0x67EC
#define TFT_DARK_GREEN      0x048A
#define TFT_Bright_YELLOW   0xFFE0
#define TFT_DARK_YELLOW     0xFD68

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HTFT_voidInit
 * @brief          : initialization TFT
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention  SPI and GPIO Pins --> TFT_config.h
 *
 *
 ******************************************************************************
 */
void        HTFT_voidInit             ( void ) ;
/**
 ******************************************************************************
 * @fn             : HTFT_u8DisplayImage
 * @brief          : Display Image
 * @param[in]      : Copy_pu16ImageArray --> Set Address of image
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *   image Dimensions is 128*160
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DisplayImage       ( const uint16_t * Copy_pu16ImageArray );
/**
 ******************************************************************************
 * @fn             : HTFT_u8FillColor
 * @brief          : Fill Color
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8FillColor          ( uint16_t Copy_u16Coler ) ;
/**
 ******************************************************************************
 * @fn             : HTFT_u8DrawRectangle
 * @brief          : Draw Rectangle
 * @param[in]      : Copy_u8StartX --> Rectangle Start X
 * @param[in]      : Copy_u8EndX   --> Rectangle End   X
 * @param[in]      : Copy_u8StartY --> Rectangle Start Y
 * @param[in]      : Copy_u8EndY   --> Rectangle End   Y
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DrawRectangle      ( uint8_t  Copy_u8StartX   , uint8_t Copy_u8EndX  , uint8_t Copy_u8StartY  , uint8_t Copy_u8EndY     , uint16_t Copy_u16Coler );
/**
 ******************************************************************************
 * @fn             : HTFT_u8DrawRectangle
 * @brief          : Draw Rectangle
 * @param[in]      : Copy_u8Char  --> Set Char
 * @param[in]      : Copy_u8X     --> Position of Char   X
 * @param[in]      : Copy_u8Y     --> Position of Char   Y
 * @param[in]      : Copy_u8Size  --> Size of Char
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DrawChar           ( uint8_t Copy_u8Char      , uint8_t Copy_u8X     , uint8_t Copy_u8Y       , uint8_t Copy_u8Size     , uint16_t Copy_u16Color );
/**
 ******************************************************************************
 * @fn             : HTFT_u8DrawRectangle
 * @brief          : Draw Rectangle
 * @param[in]      : Copy_u8Text  --> Set String
 * @param[in]      : Copy_u8X     --> Position of Char   X
 * @param[in]      : Copy_u8Y     --> Position of Char   Y
 * @param[in]      : Copy_u8Size  --> Size of Char
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DrawText           ( uint8_t  *Copy_u8Text    , uint8_t Copy_u8X     , uint8_t Copy_u8Y       , uint8_t Copy_u8Size     , uint16_t Copy_u16Color );
/**
 ******************************************************************************
 * @fn             : HTFT_u8DrawFrameu8
 * @brief          : Draw Rectangle
 * @param[in]      : Copy_pu8Frame  --> Set Array of Shape
 * @param[in]      : Copy_u8X     --> Position of Char   X
 * @param[in]      : Copy_u8Y     --> Position of Char   Y
 * @param[in]      : Copy_u8Width     --> Set Width of Shape
 * @param[in]      : Copy_u8Height    --> Set Height of Shape
 * @param[in]      : Copy_u8Size  --> Size of Char
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DrawFrameu8 ( uint8_t * Copy_pu8Frame,uint8_t Copy_u8X, uint8_t Copy_u8Y,uint8_t Copy_u8Width,uint8_t Copy_u8Height,uint8_t Copy_u8Size, uint16_t Copy_u16Color);
/**
 ******************************************************************************
 * @fn             : HTFT_u8DrawFrameu16
 * @brief          : Draw Rectangle
 * @param[in]      : Copy_pu16Frame  --> Set Array of Shape
 * @param[in]      : Copy_u8X     --> Position of Char   X
 * @param[in]      : Copy_u8Y     --> Position of Char   Y
 * @param[in]      : Copy_u8Width     --> Set Width of Shape
 * @param[in]      : Copy_u8Height    --> Set Height of Shape
 * @param[in]      : Copy_u8Size  --> Size of Char
 * @param[in]      : Copy_u16Color --> Set Color ID
 * @retval         : ERROR_STATE
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t     HTFT_u8DrawFrameu16 ( uint16_t * Copy_pu16Frame,uint8_t Copy_u8X, uint8_t Copy_u8Y,uint8_t Copy_u8Width,uint8_t Copy_u8Height,uint8_t Copy_u8Size, uint16_t Copy_u16Color);
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

#endif
