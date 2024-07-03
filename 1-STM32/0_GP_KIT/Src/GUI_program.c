/**
 ******************************************************************************
 * @file           : GUI_program.c
 * @author         : Diea Abdeltwab
 * @layer          : Service
 * @brief          : 
 * @date           : 7/3/2024
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

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "TFT_interface.h"

/******************************************************************************/
/************************ SERVIES Layer ***************************************/
/******************************************************************************/
#include "rgb565_colors.h"

#include "GUI_interface.h"
#include "GUI_config.h"
#include "GUI_private.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
void SGUI_voidInit (void)
{
	HTFT_voidInit    (                );
}
void SGUI_voidMainFrame ( uint8_t Copy_u8SpeedValue , uint8_t Copy_u8BattaryVolt , GUIDirection_t  Copy_Direction  )
{
	uint16_t Local_pu16X[16]={128, 128, 128, 128, 128, 128, 128, 128, 65535, 128, 128, 128, 128, 128, 128, 128};
	uint16_t Local_pu16BattaryFrame[16]= {0, 16380, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 15996, 576};

	HTFT_u8FillColor                                                ( GUI_GUI_MAIN_BACKGROUND );
	HTFT_u8DrawFrameu16(Local_pu16X, 0 , 15  , 16  , 16 , 8         , GUI_MAIN_FRAME );
	HTFT_u8DrawText((uint8_t *)"SPEED" , 125 , 130 , 2              , GUI_MAIN_FRAME );
	HTFT_u8DrawFrameu16(Local_pu16BattaryFrame,65 ,10 ,16,16, 4     , GUI_MAIN_FRAME );
	/*-------------------------------------------------------------------------------------------------------*/
	SGUI_voidUpdateSpeed(Copy_u8SpeedValue);
	/*-------------------------------------------------------------------------------------------------------*/
	SGUI_voidUpdateBattaryVolt(Copy_u8BattaryVolt ) ;
	/*-------------------------------------------------------------------------------------------------------*/
	SGUI_voidUpdateDirection(Copy_Direction);
	/*-------------------------------------------------------------------------------------------------------*/
}
void SGUI_voidUpdateSpeed (uint8_t Copy_u8SpeedValue)
{
	HTFT_u8DrawRectangle(75  , 110 , 95  , 120                        , GUI_GUI_MAIN_BACKGROUND );
	if ( Copy_u8SpeedValue < 100 )
	{
		uint8_t Local_u8TempNumber1 = Copy_u8SpeedValue % 10   ;
		uint8_t Local_u8TempNumber2 = Copy_u8SpeedValue / 10   ;
		HTFT_u8DrawChar(Local_u8TempNumber2 +'0', 90, 100 , 2         , GUI_SPEED_DIRECTION );
		HTFT_u8DrawChar(Local_u8TempNumber1 +'0', 80, 100 , 2         , GUI_SPEED_DIRECTION );
	}
	else
	{
		uint8_t Local_u8TempNumber1 = Copy_u8SpeedValue % 10   ;
		uint8_t Local_u8TempNumber2 = Copy_u8SpeedValue / 10   ;
		uint8_t Local_u8TempNumber3 = Local_u8TempNumber2 % 10   ;
		uint8_t Local_u8TempNumber4 = Local_u8TempNumber2 / 10   ;
		HTFT_u8DrawChar(Local_u8TempNumber4 +'0', 100 , 100 , 2       , GUI_SPEED_DIRECTION);
		HTFT_u8DrawChar(Local_u8TempNumber3 +'0', 90  , 100 , 2       , GUI_SPEED_DIRECTION);
		HTFT_u8DrawChar(Local_u8TempNumber1 +'0', 80  , 100 , 2       , GUI_SPEED_DIRECTION);
	}
}
void SGUI_voidUpdateDirection (GUIDirection_t  Copy_Direction)
{
	uint16_t Local_pu16DirFront[16]= {384, 384, 384, 384, 384, 384, 384, 384, 32766, 32766, 16380, 8184, 4080, 2016, 960, 384};
	uint16_t Local_pu16DirBack [16]= {384, 960, 2016, 4080, 8184, 16380, 32766, 32766, 384, 384, 384, 384, 384, 384, 384, 384};
	uint16_t Local_pu16DirRight[16]= {0, 192, 224, 240, 248, 252, 254, 65535, 65535, 254, 252, 248, 240, 224, 192, 0};
	uint16_t Local_pu16DirLeft [16]= {0, 768, 1792, 3840, 7936, 16128, 32512, 65535, 65535, 32512, 16128, 7936, 3840, 1792, 768, 0};
	uint16_t Local_pu16StopStopsign[16]={4080, 4104, 8324, 24194, 37617, 37521, 40689, 32769, 40481, 33313, 40481, 36897, 24314, 8196, 4104, 4080};

	HTFT_u8DrawRectangle(3  , 53 , 10  , 65                              , GUI_GUI_MAIN_BACKGROUND );
	if ( Copy_Direction == GUI_FORWARD )
	{
		HTFT_u8DrawFrameu16(Local_pu16DirFront, 5 , 15  , 16, 16, 3      , GUI_SPEED_DIRECTION);
	}
	else if ( Copy_Direction == GUI_RIGHT )
	{
		HTFT_u8DrawFrameu16(Local_pu16DirRight , 5 , 15  , 16, 16, 3     , GUI_SPEED_DIRECTION);
	}
	else if ( Copy_Direction == GUI_LEFT )
	{
		HTFT_u8DrawFrameu16(Local_pu16DirLeft , 5 , 15  , 16, 16, 3      , GUI_SPEED_DIRECTION);

	}
	else if ( Copy_Direction == GUI_BACKWARD )
	{
		HTFT_u8DrawFrameu16(Local_pu16DirBack , 5 , 15  , 16, 16, 3      , GUI_SPEED_DIRECTION);
	}
	else if ( Copy_Direction == GUI_STOP )
	{
		HTFT_u8DrawFrameu16(Local_pu16StopStopsign , 5 , 15  , 16, 16, 3 , GUI_SPEED_DIRECTION);
	}
}
void SGUI_voidUpdateBattaryVolt (uint8_t Copy_u8BattaryVolt)
{
	uint16_t Local_pu16BattaryLimit[16]= {0, 0, 8184, 8184, 8184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if ( Copy_u8BattaryVolt >= 9 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 10  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 22  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 34  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 46  , 16, 16, 4, TFT_GREEN);
	}
	else if ( Copy_u8BattaryVolt >= 6 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 10  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 22  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 34  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 46  , 16, 16, 4, TFT_RED);
	}
	else if ( Copy_u8BattaryVolt >= 3 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 10  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 22  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 34  , 16, 16, 4, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 46  , 16, 16, 4, TFT_RED);
	}
	else
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 10  , 16, 16, 4, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 22  , 16, 16, 4, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 34  , 16, 16, 4, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 65 , 46  , 16, 16, 4, TFT_RED);
	}
}
/*************************************************************************************************************************************/
/********************************************************************** V2I **********************************************************/
/*************************************************************************************************************************************/

void SGUI_voidV2IStopSign (void)
{
	uint16_t Local_pu16StopStopsign[16]={4080, 4104, 8324, 24194, 37617, 37521, 40689, 32769, 40481, 33313, 40481, 36897, 24314, 8196, 4104, 4080};
	HTFT_u8FillColor                                                  ( GUI_V2I_STOP_SIGN_BACKGROUND );
	HTFT_u8DrawFrameu16(Local_pu16StopStopsign, 10, 40, 16, 16, 6     , GUI_V2I_STOP_SIGN_FRAME      );
}
void SGUI_voidV2ISpeedSign(uint8_t Copy_u8SpeedSignID)
{
	uint16_t Local_pu16SpeedLimit25[16]={65532, 32772, 48884, 40980, 48660, 33524, 33412, 48884, 32772, 32772, 32772, 32772, 32772, 32772, 32772, 65532};
	uint16_t Local_pu16SpeedLimit50[16]={65532, 32772, 48884, 33428, 48788, 41108, 41108, 48884, 32772, 32772, 32772, 32772, 32772, 32772, 32772, 65532};
	HTFT_u8FillColor                                                  ( GUI_V2I_SPEED_SIGN_BACKGROUND );
	HTFT_u8DrawText((uint8_t *)"SPEED", 95 , 100, 2                   , GUI_V2I_SPEED_SIGN_FRAME      );
	HTFT_u8DrawText((uint8_t *)"LIMIT", 95 , 85 , 2                   , GUI_V2I_SPEED_SIGN_FRAME      );
	if ( Copy_u8SpeedSignID == GUI_ID_SPEED_25 )
	{
		HTFT_u8DrawFrameu16(Local_pu16SpeedLimit25, 10, 30, 16, 16, 6 , GUI_V2I_SPEED_SIGN_FRAME      );
	}
	else if ( Copy_u8SpeedSignID == GUI_ID_SPEED_50 )
	{
		HTFT_u8DrawFrameu16(Local_pu16SpeedLimit50, 10, 30, 16, 16, 6 , GUI_V2I_SPEED_SIGN_FRAME      );
	}
}
void SGUI_voidV2ITrafficSign(uint8_t Copy_u8TrafficSignID , uint8_t Copy_u8FirstFlag )
{
	uint16_t Local_pu16Circle[16]={8184, 16380, 32766, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 32766, 16380, 8184};
	uint16_t Local_pu16Traffic[16]={384, 576, 1056, 3024, 5064, 9156, 17346, 33729, 33729, 17346, 9156, 5064, 3024, 1056, 576, 384};
	if ( Copy_u8FirstFlag == 1 )
	{
		HTFT_u8FillColor                                              ( GUI_V2I_TRAFFIC_SIGN_BACKGROUND );
		HTFT_u8DrawFrameu16(Local_pu16Traffic, 15, 35, 16, 16, 6      , GUI_V2I_TRAFFIC_SIGN_FRAME      );
	}
	if ( Copy_u8TrafficSignID == GUI_ID_TRAFFIC_RED )
	{
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 95, 16, 16, 1, TFT_Bright_RED);
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 75, 16, 16, 1, TFT_DARK_YELLOW);
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 55, 16, 16, 1, TFT_DARK_GREEN);
	}
	else if ( Copy_u8TrafficSignID == GUI_ID_TRAFFIC_YELLOW )
	{
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 95, 16, 16, 1, TFT_DARK_RED);
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 75, 16, 16, 1, TFT_Bright_YELLOW );
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 55, 16, 16, 1, TFT_DARK_GREEN);
	}
	else if ( Copy_u8TrafficSignID == GUI_ID_TRAFFIC_GREAN )
	{
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 95, 16, 16, 1, TFT_DARK_RED);
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 75, 16, 16, 1, TFT_DARK_YELLOW);
		HTFT_u8DrawFrameu16(Local_pu16Circle, 55, 55, 16, 16, 1, TFT_Bright_GREEN);
	}
}
/*************************************************************************************************************************************/
/*********************************************************************************** V2P *********************************************/
/*************************************************************************************************************************************/
void SGUI_voidV2PPedestrian (void)
{
	uint16_t Local_pu16Pedestrian[16]={4112, 2080, 1088, 896, 256, 256, 256, 896, 1344, 2336, 5008, 1088, 1088, 1088, 896, 0};
	HTFT_u8FillColor                                                  ( GUI_V2P_BACKGROUND );
	HTFT_u8DrawFrameu16(Local_pu16Pedestrian, 5, 50, 16, 16, 7        , GUI_V2P_FRAME );
	HTFT_u8DrawText((uint8_t *)"STOP", 100 , 20 , 3                   , GUI_V2P_FRAME );

}
/*************************************************************************************************************************************/
/*********************************************************************************** V2G *********************************************/
/*************************************************************************************************************************************/

void SGUI_voidV2GBattaryLimit(uint8_t Copy_u8BattaryVolt , uint8_t Copy_u8FirstFlag )
{
	uint16_t Local_pu16BattaryFrame[16]= {0, 16380, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 8196, 15996, 576};
	uint16_t Local_pu16BattaryLimit[16]= {0, 0, 8184, 8184, 8184, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if ( Copy_u8FirstFlag == 1 )
	{
		HTFT_u8FillColor                                               ( GUI_V2G_BACKGROUND );
		HTFT_u8DrawText((uint8_t *)"V2G", 90 , 5 , 3                   , GUI_V2G_FRAME  );
		HTFT_u8DrawFrameu16(Local_pu16BattaryFrame, 1 , 25 , 16, 16, 8 , GUI_V2G_FRAME  );
	}
	if ( Copy_u8BattaryVolt >= 9 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 25  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 50  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 75  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 100 , 16, 16, 8, TFT_GREEN);
	}
	else if ( Copy_u8BattaryVolt >= 6 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 25  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 50  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 75  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 100 , 16, 16, 8, TFT_RED);
	}
	else if ( Copy_u8BattaryVolt >= 3 )
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 25  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 50  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 75  , 16, 16, 8, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 100 , 16, 16, 8, TFT_RED);
	}
	else
	{
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 25  , 16, 16, 8, TFT_GREEN);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 50  , 16, 16, 8, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 75  , 16, 16, 8, TFT_RED);
		HTFT_u8DrawFrameu16(Local_pu16BattaryLimit, 1 , 100 , 16, 16, 8, TFT_RED);
	}

}
void SGUI_voidV2GStartEnd ( GUIV2GStartEnd_t Copy_u8StartEnd )
{
	uint16_t Local_pu16Success[16]={16380, 16386, 32769, 38913, 37889, 37377, 37121, 36993, 36929, 32801, 32785, 32777, 32773, 32769, 16386, 16380};
	HTFT_u8FillColor                                                ( GUI_V2G_BACKGROUND );
	HTFT_u8DrawText((uint8_t *)"V2G", 100 , 120 , 4                 , GUI_V2G_FRAME  );
	HTFT_u8DrawText((uint8_t *)"------------------", 120 , 100 , 1  , GUI_V2G_FRAME  );
	HTFT_u8DrawText((uint8_t *)"CHARGING ", 110 , 45 , 2            , GUI_V2G_FRAME  );
	HTFT_u8DrawFrameu16(Local_pu16Success, 50 , 10 , 16, 16, 2      , GUI_V2G_FRAME  );
	if ( Copy_u8StartEnd == GUI_V2G_START )
	{
		HTFT_u8DrawText((uint8_t *)"START ", 105 , 70 , 3           , GUI_V2G_FRAME  );
	}
	else if ( Copy_u8StartEnd == GUI_V2G_END )
	{
		HTFT_u8DrawText((uint8_t *)"END ", 100  , 70 , 4            , GUI_V2G_FRAME  );
	}

}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Static Functions implementations ******************************************/
/*************************************************************************************************************************************/



/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

