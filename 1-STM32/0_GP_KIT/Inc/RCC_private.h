#ifndef  RCC_PRIVATE_H
#define  RCC_PRIVATE_H

/*************************************************************************************/
/******************************* CR BITS *********************************************/
/*************************************************************************************/
#define  RCC_CR_HSION     				 0
#define  RCC_CR_HSIRDY                   1
#define  RCC_CR_HSEON                    16
#define  RCC_CR_HSERD                    17
#define  RCC_CR_HSEBYP                   18
#define  RCC_CR_CSSON                    19
#define  RCC_CR_PLLON                    24
#define  RCC_CR_PLLRDY                   25

/*************************************************************************************/
/******************************* CFGR BITS *******************************************/
/*************************************************************************************/
#define  RCC_CFGR_SW                     0
#define  RCC_CFGR_ADCPRE                 14
#define  RCC_CFGR_PLLSRC                 16
#define  RCC_CFGR_PLLXTPRE               17
#define  RCC_CFGR_PLLMUL                 18

/*************************************************************************************/
/******************************* MASKS ***********************************************/
/*************************************************************************************/
#define  RCC_CLK_NOT_RDY                 0
#define  RCC_CLOCK_STATE_MASK            0b1
#define  RCC_SYS_CLOCK_MASK              0b11
#define  RCC_HSE_CONFIG_MASK             0b1
#define  RCC_HSE_BYP_MASK                0b1
#define  RCC_PLL_INPUT_MASK              0b1
#define  RCC_PLL_MUL_MASK                0b1111
#define  RCC_ADC_PRE_MASK                0b11



#endif
