
#ifndef V2G_CONFIG_H
#define V2G_CONFIG_H
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
#define V2G_USART_INDEX      		            USART_3
/******************************************************************************************/
/******************************* V2G ******************************************************/
/******************************************************************************************/
#define VEHICLE_VIN      		               "XP7SA1DG9SFC14705"

#define V2G_EV_PLUG_CABLE      		            0x51
#define V2G_EV_IDENTIFICATION                   0x52
#define V2G_EV_CHARGE_PARAMETAR                 0x53
#define V2G_EV_CHARGING_PROFILE                 0x54
#define V2G_EV_START_CHARGING                   0x55
#define V2G_EV_END_CHARGING                     0x56
#define V2G_EV_SEND_ENERGY_AMOUNT               0x57


#define V2G_EV_ACK					            0xA5
#define V2G_EV_NACK					            0x7F

#define V2G_EV_ACCEPT_CHARGING	                0xB5
#define V2G_EV_REJECT_CHARGING                  0xB6

#define V2G_EV_ADD_COST_SCCESS           	    0xB0
#define V2G_EV_ADD_COST_FAIL             	    0xB1

#define V2G_EV_ACCEPT_START_CHARGING            0xB8
#define V2G_EV_ACCEPT_END_CHARGING              0xB9

#define V2G_EV_VERIFY_IDENTIFICATION_SCCESS     0xB3
#define V2G_EV_VERIFY_IDENTIFICATION_FAIL       0xB4

#define V2G_EV_ACCEPT_UPDATE_ENARGY             0xB5
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/


#endif
