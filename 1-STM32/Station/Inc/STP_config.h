
#ifndef STP_CONFIGI_H
#define STP_CONFIGI_H

/******************************************************************************/
/************************ Number IC to Enable *********************************/
/************************ STP_ONE_IC Or STP_TWO_IC ****************************/
/******************************************************************************/
#define STP_NUMBER_IC     STP_TWO_IC
/******************************************************************************/
/************************ Pin and Port Config *********************************/
/******************************************************************************/
#if STP_NUMBER_IC == STP_ONE_IC
#define STP_DATA_PIN_IC1    	 PORTA,PIN0
#define STP_BYTE_STCP_PIN_IC1    PORTA,PIN2
#define STP_BIT_SHCP_PIN_IC1     PORTA,PIN1

#elif STP_NUMBER_IC == STP_TWO_IC
#define STP_DATA_PIN_IC1    	 PORTA,PIN0
#define STP_BYTE_STCP_PIN_IC1    PORTA,PIN2
#define STP_BIT_SHCP_PIN_IC1     PORTA,PIN1

#define STP_DATA_PIN_IC2    	 PORTA,PIN3
#define STP_BYTE_STCP_PIN_IC2    PORTA,PIN4
#define STP_BIT_SHCP_PIN_IC2     PORTA,PIN5

#endif



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/



#endif
