/**
 ******************************************************************************
 * @file           : GPIO_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 2 For STM32F103C8T6 Drivers
 * @date           : 26/7/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  GPIO_INTERFACE_H
#define  GPIO_INTERFACE_H
/********************************************************/
/******* @Port_t  ***************************************/
/********************************************************/
typedef enum{
			PORTA =0,
			PORTB   ,
			PORTC   ,
			PORTD   ,
			PORTE   ,
			PORTF   ,
			PORTG
}Port_t;

/********************************************************/
/******* @Pin_t *****************************************/
/********************************************************/
typedef enum{
             PIN0=0,
             PIN1  ,
             PIN2  ,
             PIN3  ,
             PIN4  ,
             PIN5  ,
             PIN6  ,
             PIN7  ,
             PIN8  ,
             PIN9  ,
             PIN10 ,
             PIN11 ,
             PIN12 , 
             PIN13 , 
             PIN14 , 
             PIN15
}Pin_t;

/********************************************************/
/******* @Mode_t ****************************************/
/********************************************************/
typedef enum{
             INPUT               =0,
             OUTPUT_SPEED_10MHZ    ,
			 OUTPUT_SPEED_2MHZ     ,
			 OUTPUT_SPEED_50MHZ

}Mode_t;

/********************************************************/
/******* @OutputMode_t **********************************/
/********************************************************/
typedef enum{
             GP_PUSH_PULL    =0,
			 GP_OPEN_DRAIN     ,
	         AF_PUSH_PULL      ,
		     AF_OPEN_DRAIN

}OutputMode_t;

/********************************************************/
/******* @InputMode_t ***********************************/
/********************************************************/
typedef enum{
             ANALOG       =0,
			 FLOATING       ,
	         PULL_UP_DOWEN  ,

}InputMode_t;

/********************************************************/
/******* @PinConfig_t ***********************************/
/********************************************************/

typedef struct{
             Port_t        Port       ;
             Pin_t         PinNum     ;
             Mode_t        Mode       ;
             OutputMode_t  Outputmode ;
             InputMode_t   Inputmode  ;
}PinConfig_t;

/********************************************************/
/******* @PinValue_t ************************************/
/********************************************************/
typedef enum{
	        LOW=0,
			HIGH

}PinValue_t;

/********************************************************/
/******* @PortPosition_t ********************************/
/********************************************************/
typedef enum{
			PORT_LOW=0,
			PORT_HIGH

}PortPosition_t;

/********************************************************/
/******* @PinPortMode_t *********************************/
/********************************************************/
typedef enum{
			INPUT_ANALOG                  =0b0000,
			INPUT_FLOATING                =0b0100,
			INPUT_PULL_UP_DOWEN           =0b1000,
			OUTPUT_SPEED_10MHZ_PP         =0b0001,
			OUTPUT_SPEED_10MHZ_OD         =0b0101,
			OUTPUT_SPEED_10MHZ_AFPP       =0b1001,
			OUTPUT_SPEED_10MHZ_AFOD       =0b1101,
			OUTPUT_SPEED_2MHZ_PP          =0b0010,
			OUTPUT_SPEED_2MHZ_OD          =0b0110,
			OUTPUT_SPEED_2MHZ_AFPP        =0b1010,
			OUTPUT_SPEED_2MHZ_AFOD        =0b1110,
			OUTPUT_SPEED_50MHZ_PP         =0b0011,
			OUTPUT_SPEED_50MHZ_OD         =0b0111,
			OUTPUT_SPEED_50MHZ_AFPP       =0b1011,
			OUTPUT_SPEED_50MHZ_AFOD       =0b1111

}PinPortMode_t;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MGPIO_u8PinInit
 * @brief          : initialization Value of Pin
 * @param[in]      : PinConfig  --> init Value of Pin from @PinConfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8PinInit ( const PinConfig_t* PinConfig );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPinDirection
 * @brief          : Set Pin Direction
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[in]      : Copy_Mode   --> get option from @PinPortMode_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPinDirection ( Port_t Copy_PortID , Pin_t Copy_PinID , PinPortMode_t Copy_Mode    );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPortDirection
 * @brief          : Set Port Direction
 * @param[in]      : Copy_PortID   --> get option from @Port_t         enum
 * @param[in]      : Copy_Position --> get option from @PortPosition_t enum
 * @param[in]      : Copy_Mode     --> get option from @PinPortMode_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPortDirection ( Port_t Copy_PortID , PortPosition_t Copy_Position , PinPortMode_t Copy_Mode       );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPinValue
 * @brief          : Set Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[in]      : Copy_Value  --> get option from @PinValue_t     enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPinValue     ( Port_t Copy_PortID , Pin_t Copy_PinID , PinValue_t Copy_Value   );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8GetPinValue
 * @brief          : Get Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @param[out]     : Copy_Value  --> Set value in Copy_pu8Result     uint8_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

uint8_t  MGPIO_u8GetPinValue    ( Port_t Copy_PortID , Pin_t Copy_PinID , uint8_t *Copy_pu8Result );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8TogPinValue
 * @brief          : TOG Pin Value
 * @param[in]      : Copy_PortID --> get option from @Port_t         enum
 * @param[in]      : Copy_PinID  --> get option from @Pin_t          enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8TogPinValue     ( Port_t Copy_PortID , Pin_t Copy_PinID  );
/**
 ******************************************************************************
 * @fn             : MGPIO_u8SetPortValue
 * @brief          : Set Port Value
 * @param[in]      : Copy_PortID --> get option from @Port_t            enum
 * @param[in]      : Copy_Position  --> get option from @PortPosition_t enum
 * @param[in]      : Copy_u16Value  --> Set Value in Copy_u16Value      uint16_t
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MGPIO_u8SetPortValue     ( Port_t Copy_PortID , PortPosition_t Copy_Position , uint16_t Copy_u16Value    );

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
#endif
