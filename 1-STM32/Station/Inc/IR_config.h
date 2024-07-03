


#ifndef  IR_CONFIG_H
#define  IR_CONFIG_H
/******************************************************************************/
/************************ Pin and Port Config *********************************/
/******************************************************************************/
/*
 * LINE0
 * LINE1
 * LINE2
 * ...
 * ...
 * LINE15
 * Get option From @EXTI_LineNumber_t
 *
 */
#define  IR_EXTI_LINE        LINE0
/*
 * PORTA
 * PORTB
 * PORTC
 * Get option From GPIO --> @Port_t
 */
#define  IR_EXTI_PORT         PORTA
/******************************************************************************/
/*************************** Delays *******************************************/
/******************************************************************************/

#define  IR_MAX_TakeAction_TIME                      300000
#define  IR_MAX_RANGE_TIME_FOR_START_BIT             14000
#define  IR_MIN_RANGE_TIME_FOR_START_BIT             10000
#define  IR_MAX_RANGE_TIME_FOR_ONE                   2300
#define  IR_MIN_RANGE_TIME_FOR_ONE                   2000
/******************************************************************************/
/*************************** Commend ******************************************/
/******************************************************************************/

#define  IR_DATA_COMMEND_START_EDGE                  17
#define  IR_DATA_COMMEND_END_EDGE                    25
#define  IR_ADDRESS_COMMEND_START_EDGE               1
#define  IR_ADDRESS_COMMEND_END_EDGE                 9
#define  IR_END_OF_FRAME                             33

/******************************************************************************/
/*************************** Remote Config ************************************/
/******************************************************************************/

#define  IR_REMOTE_ADDRESS               (uint8_t)0
#define IR_POWER_DATA_BUTTON             (uint8_t)69
#define IR_MODE_DATA_BUTTON              (uint8_t)70
#define IR_MUTE_DATA_BUTTON              (uint8_t)71
#define IR_RPT_DATA_BUTTON               (uint8_t)25
#define IR_USD_DATA_BUTTON               (uint8_t)13
#define IR_PLAY_DATA_BUTTON              (uint8_t)67
#define IR_PREV_DATA_BUTTON              (uint8_t)68
#define IR_NEXT_DATA_BUTTON              (uint8_t)64
#define IR_EQ_DATA_BUTTON                (uint8_t)9
#define IR_VOL_DOWN_DATA_BUTTON          (uint8_t)7
#define IR_VOL_UP_DATA_BUTTON            (uint8_t)21
#define IR_ZER0_DATA_BUTTON              (uint8_t)22
#define IR_ONE_DATA_BUTTON               (uint8_t)12
#define IR_TWO_DATA_BUTTON               (uint8_t)24
#define IR_THREE_DATA_BUTTON             (uint8_t)94
#define IR_FOUR_DATA_BUTTON              (uint8_t)8
#define IR_FIVE_DATA_BUTTON              (uint8_t)28
#define IR_SIX_DATA_BUTTON               (uint8_t)90
#define IR_SEVEN_DATA_BUTTON             (uint8_t)66
#define IR_EIGHT_DATA_BUTTON             (uint8_t)82
#define IR_NINE_DATA_BUTTON              (uint8_t)74

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


#endif
