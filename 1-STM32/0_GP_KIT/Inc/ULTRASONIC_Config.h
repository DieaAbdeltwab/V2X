
#ifndef ULTRASONIC_CONFIG_H
#define ULTRASONIC_CONFIG_H
/******************************************************************************************/
/******************************* GPTIMER Configuration ************************************/
/******************************************************************************************/
#define ULTRASONIC_AUTO_RELOAD_INT_VALUE      65535
#define ULTRASONIC_TMR_PRESCALER              1024
/******************************************************************************************/
/******************************** PINS ****************************************************/
/******************************************************************************************/
#define ULTRASONIC_1_TRIGGER_PORT         PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_1_TRIGGER_PIN          PIN2    /* Get Option From GPIO Interface    */
#define ULTRASONIC_1_ECHO_PORT         	  PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_1_ECHO_PIN             PIN1    /* Get Option From GPIO Interface    */

#define ULTRASONIC_2_TRIGGER_PORT         PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_2_TRIGGER_PIN          PIN1    /* Get Option From GPIO Interface    */
#define ULTRASONIC_2_ECHO_PORT         	  PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_2_ECHO_PIN             PIN7    /* Get Option From GPIO Interface    */

#define ULTRASONIC_3_TRIGGER_PORT         PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_3_TRIGGER_PIN          PIN2    /* Get Option From GPIO Interface    */
#define ULTRASONIC_3_ECHO_PORT         	  PORTB   /* Get Option From GPIO Interface    */
#define ULTRASONIC_3_ECHO_PIN             PIN0    /* Get Option From GPIO Interface    */


#define ULTRASONIC_4_TRIGGER_PORT         PORTA   /* Get Option From GPIO Interface    */
#define ULTRASONIC_4_TRIGGER_PIN          PIN3    /* Get Option From GPIO Interface    */
#define ULTRASONIC_4_ECHO_PORT         	  PORTB   /* Get Option From GPIO Interface    */
#define ULTRASONIC_4_ECHO_PIN             PIN1    /* Get Option From GPIO Interface    */
/******************************************************************************************/
/******************************* ULTRASONIC Configuration *********************************/
/******************************************************************************************/
#define ULTRASONIC_TRIGGER_TIME               5
#define ULTRASONIC_DISTANCE_EQ                2.24
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/


#endif
