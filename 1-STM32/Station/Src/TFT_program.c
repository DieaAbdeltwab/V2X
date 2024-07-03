/**
 ******************************************************************************
 * @file           : TFT_program.c
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
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "STK_INTERFACE.h"
#include "SPI_INTERFACE.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HTFT_voidInit
 * @brief          : initialization TFT
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention  STK , SPI and GPIO Pins --> TFT_config.h
 *
 *
 ******************************************************************************
 */
void   HTFT_voidInit    ( void ) 
{
	MSTK_u8ClockConfig(STK_AHB_DIV_8);
	MGPIO_u8SetPinDirection( TFT_A0_PIN    , OUTPUT_SPEED_2MHZ_PP    );
	MGPIO_u8SetPinDirection( TFT_RESET_PIN , OUTPUT_SPEED_2MHZ_PP    );
	MGPIO_u8SetPinDirection( TFT_SCK       , OUTPUT_SPEED_10MHZ_AFPP );
	MGPIO_u8SetPinDirection( TFT_MOSI      , OUTPUT_SPEED_10MHZ_AFPP );
	SPIconfig_t SPI_config ={TFT_SPI_INDEX,LEADING_CAPTURE,LEADING_RISING,MASTER,F_CLK_DIV_8,MSB,SELECT_ONE,MANAGMENT_ENABLE,FULL_DUPLEX,FORMAT_8_BIT
				                          ,RX_DMA_DISABLE ,TX_DMA_DISABLE,SS_OUTPUT_DISABLE ,RX_INTERRUPT_MASKED,TX_INTERRUPT_MASKED };
	MSPI_u8SetConfiguration(&SPI_config);

	MGPIO_u8SetPinValue   ( TFT_RESET_PIN , HIGH) ;
	STIMERS_voidDelayUS       ( TFT_RESET_DELAY_1 );
	MGPIO_u8SetPinValue   ( TFT_RESET_PIN , LOW) ;
	STIMERS_voidDelayUS       ( TFT_RESET_DELAY_2 );
	MGPIO_u8SetPinValue   ( TFT_RESET_PIN , HIGH) ;
	STIMERS_voidDelayUS       ( TFT_RESET_DELAY_3 );
	MGPIO_u8SetPinValue   ( TFT_RESET_PIN , LOW) ;
	STIMERS_voidDelayUS       ( TFT_RESET_DELAY_4 );
	MGPIO_u8SetPinValue   ( TFT_RESET_PIN , HIGH) ;
	STIMERS_voidDelayUS       ( TFT_RESET_DELAY_5 );
	
	HTFT_voidWriteCommand ( TFT_SLPOUT );
	STIMERS_voidDelayUS     ( TFT_SLPOUT_DELAY );
	
	HTFT_voidWriteCommand ( TFT_COLMOD );
	HTFT_voidWriteData    ( TFT_COLMOD_DATA );
	
	HTFT_voidWriteCommand ( TFT_DISPON );
	STIMERS_voidDelayUS       ( TFT_DISPON_DELAY );

	HTFT_voidWriteCommand( TFT_MADCTL );
	HTFT_voidWriteData   ( TFT_MADCTL_DATA );
	
} 
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
uint8_t     HTFT_u8DisplayImage   ( const uint16_t * Copy_pu16ImageArray )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_pu16ImageArray != NULL )
	{

		HTFT_voidWriteCommand( TFT_CASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( TFT_XSIZE - 1 );

		HTFT_voidWriteCommand( TFT_RASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( TFT_YSIZE - 1 );

		HTFT_voidWriteCommand( TFT_RAMWR );
		for ( uint16_t Local_u16Counter = 0 ; Local_u16Counter < (TFT_YSIZE * TFT_XSIZE) ; Local_u16Counter++ )
		{
			HTFT_voidWriteData(  Copy_pu16ImageArray[Local_u16Counter] >> 8 );
			HTFT_voidWriteData( (Copy_pu16ImageArray[Local_u16Counter] &  0x00FF)  );
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t     HTFT_u8FillColor  ( uint16_t  Copy_u16Color )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{

		HTFT_voidWriteCommand( TFT_CASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( TFT_XSIZE - 1 );

		HTFT_voidWriteCommand( TFT_RASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( TFT_YSIZE - 1 );

		HTFT_voidWriteCommand( TFT_RAMWR );
		for ( uint16_t Local_u16Counter = 0 ; Local_u16Counter < (TFT_YSIZE * TFT_XSIZE) ; Local_u16Counter++ )
		{
			HTFT_voidWriteData(  Copy_u16Color  >> 8 );
			HTFT_voidWriteData( (Copy_u16Color & 0x00FF)  );
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
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
uint8_t     HTFT_u8DrawRectangle  (uint8_t Copy_u8StartX , uint8_t Copy_u8EndX , uint8_t Copy_u8StartY , uint8_t Copy_u8EndY , uint16_t  Copy_u16Color )
{

	if( Copy_u8StartX > Copy_u8EndX )
	{
		Copy_u8StartX = 0 ;
	}
	if( Copy_u8StartY > Copy_u8EndY )
	{
		Copy_u8StartY = 0 ;
	}
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{
		uint8_t Local_u8Data ;

		uint16_t Local_u16Area = ( Copy_u8EndX - Copy_u8StartX + 1 ) * ( Copy_u8EndY - Copy_u8StartY + 1 ) ;

		HTFT_voidWriteCommand( TFT_CASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( Copy_u8StartX );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( Copy_u8EndX );

		HTFT_voidWriteCommand( TFT_RASET );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( Copy_u8StartY );
		HTFT_voidWriteData   ( 0 );
		HTFT_voidWriteData   ( Copy_u8EndY );

		HTFT_voidWriteCommand( TFT_RAMWR );
		for ( uint16_t Local_u16Counter = 0 ; Local_u16Counter < Local_u16Area ; Local_u16Counter++ )
		{
			Local_u8Data = Copy_u16Color  >> 8 ;
			HTFT_voidWriteData( Local_u8Data );
			Local_u8Data = Copy_u16Color & 0x00FF ;
			HTFT_voidWriteData( Local_u8Data );
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
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
uint8_t     HTFT_u8DrawChar (uint8_t Copy_u8Char, uint8_t Copy_u8X, uint8_t Copy_u8Y, uint8_t Copy_u8Size,uint16_t Copy_u16Color)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( Copy_u8Char!=32 )
	{
		Copy_u8Char -=48;
		for(uint8_t Local_u8Counter1 =0 ; Local_u8Counter1<(8* Copy_u8Size);Local_u8Counter1++)
		{
			for(uint8_t Local_u8Counter2 =0;Local_u8Counter2<(5*Copy_u8Size);Local_u8Counter2++)
			{
				if (Char_Au8Array[Copy_u8Char][Local_u8Counter1/Copy_u8Size] >>(Local_u8Counter2/Copy_u8Size) & 1)
				{
					HTFT_u8DrawRectangle (  Copy_u8X+(Local_u8Counter2),  Copy_u8X+(Local_u8Counter2)+1,  Copy_u8Y+(Local_u8Counter1),  Copy_u8Y+(Local_u8Counter1), Copy_u16Color);
				}
			}
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t     HTFT_u8DrawText (uint8_t* Copy_u8Text, uint8_t Copy_u8X, uint8_t Copy_u8Y, uint8_t Copy_u8Size,uint16_t Copy_u16Color)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{
		for(; *Copy_u8Text; Copy_u8Text++ )
		{
			if(*Copy_u8Text==32)
			{
				Copy_u8X-=3;
			}
			else
			{
				Copy_u8X-=6*Copy_u8Size;
				HTFT_u8DrawChar ( *Copy_u8Text,   Copy_u8X,  Copy_u8Y,  Copy_u8Size, Copy_u16Color);
	         }
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;

}
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
uint8_t     HTFT_u8DrawFrameu8 ( uint8_t * Copy_pu8Frame,uint8_t Copy_u8X, uint8_t Copy_u8Y,uint8_t Copy_u8Width,uint8_t Copy_u8Height,uint8_t Copy_u8Size, uint16_t Copy_u16Color)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{
		for(uint8_t Local_u8Counter1 =0 ; Local_u8Counter1<(Copy_u8Height*Copy_u8Size);Local_u8Counter1++)
		{
			for(uint8_t Local_u8Counter2 =0;Local_u8Counter2<Copy_u8Width*Copy_u8Size;Local_u8Counter2++)
			{
				if (GET_BIT(Copy_pu8Frame[Local_u8Counter1/Copy_u8Size],Local_u8Counter2/Copy_u8Size) )
				{
					HTFT_u8DrawRectangle (  Copy_u8X+Local_u8Counter2,  Copy_u8X+Local_u8Counter2,  Copy_u8Y+(Local_u8Counter1),  Copy_u8Y+(Local_u8Counter1), Copy_u16Color);
				}
			}
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
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
uint8_t     HTFT_u8DrawFrameu16 ( uint16_t * Copy_pu16Frame,uint8_t Copy_u8X, uint8_t Copy_u8Y,uint8_t Copy_u8Width,uint8_t Copy_u8Height,uint8_t Copy_u8Size, uint16_t Copy_u16Color)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if ( 1 )
	{
		for(uint8_t Local_u8Counter1 =0 ; Local_u8Counter1<(Copy_u8Height*Copy_u8Size);Local_u8Counter1++)
		{
			for(uint8_t Local_u8Counter2 =0;Local_u8Counter2<Copy_u8Width*Copy_u8Size;Local_u8Counter2++)
			{
				if (GET_BIT(Copy_pu16Frame[Local_u8Counter1/Copy_u8Size],Local_u8Counter2/Copy_u8Size) )
				{
					HTFT_u8DrawRectangle (  Copy_u8X+Local_u8Counter2,  Copy_u8X+Local_u8Counter2,  Copy_u8Y+(Local_u8Counter1),  Copy_u8Y+(Local_u8Counter1), Copy_u16Color);
				}
			}
		}
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}

/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/
static void HTFT_voidWriteData ( uint8_t Copy_u8Data )
{
	uint8_t Local_u8Temp ;
	MGPIO_u8SetPinValue( TFT_A0_PIN , HIGH ) ;
	MSPI_u8SendReceiveSynch ( TFT_SPI_INDEX,Copy_u8Data , &Local_u8Temp ) ;

}
static void HTFT_voidWriteCommand ( uint8_t Copy_u8Command )
{
	uint8_t Local_u8Temp ;
	MGPIO_u8SetPinValue( TFT_A0_PIN , LOW) ;
	MSPI_u8SendReceiveSynch (TFT_SPI_INDEX ,Copy_u8Command , &Local_u8Temp ) ;

}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
