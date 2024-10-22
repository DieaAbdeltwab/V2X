
#ifndef CARKIT_CONFIG_H
#define CARKIT_CONFIG_H
/******************************************************************************************/
/******************************* Function IDs *********************************************/
/******************************************************************************************/
/*==================================================================*/
/*=========================== ADC ==================================*/
/*==================================================================*/
#define CARKIT_ADC_VOLT_PIN             PORTB, PIN0
#define CARKIT_ADC_VOLT_CHANNEL         CHANNEL8
/*==================================================================*/
/*=========================== L298N ================================*/
/*==================================================================*/
#define CARKIT_TIMER_PORT_REMAP         PARATIAL_REMAP
#define CARKIT_SPEED_TIMER_CHANNEL_R    TMR_3 , TMR_CHANNEL_2
#define CARKIT_SPEED_TIMER_CHANNEL_L    TMR_3 , TMR_CHANNEL_4
#define CARKIT_L298N_FREQ               530
#define CARKIT_L298N_INIT_SPEED         50
/*==================================================================*/
#define CARKIT_L298N_EN_A_PIN           PORTB , PIN1
#define CARKIT_L298N_IN_1_PIN           PORTB , PIN6
#define CARKIT_L298N_IN_2_PIN           PORTB , PIN7
#define CARKIT_L298N_EN_B_PIN           PORTB , PIN5
#define CARKIT_L298N_IN_3_PIN           PORTB , PIN8
#define CARKIT_L298N_IN_4_PIN           PORTB , PIN9
/*==================================================================*/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/


#endif
