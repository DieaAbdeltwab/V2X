


#ifndef  EXTI_PRIVATE_H
#define  EXTI_PRIVATE_H

/******************************************************************************/
/************************ MACROS **********************************************/
/******************************************************************************/
#define  EXTI_LINE_RISING   1
/******************************************************************************/
/*********************** Handlers Flags ***************************************/
/******************************************************************************/
#define  EXTI_LINE5_FLAGE    GET_BIT(EXTI->PR,5)
#define  EXTI_LINE6_FLAGE    GET_BIT(EXTI->PR,6)
#define  EXTI_LINE7_FLAGE    GET_BIT(EXTI->PR,7)
#define  EXTI_LINE8_FLAGE    GET_BIT(EXTI->PR,8)
#define  EXTI_LINE9_FLAGE    GET_BIT(EXTI->PR,9)
#define  EXTI_LINE10_FLAGE   GET_BIT(EXTI->PR,10)
#define  EXTI_LINE11_FLAGE   GET_BIT(EXTI->PR,11)
#define  EXTI_LINE12_FLAGE   GET_BIT(EXTI->PR,12)
#define  EXTI_LINE13_FLAGE   GET_BIT(EXTI->PR,13)
#define  EXTI_LINE14_FLAGE   GET_BIT(EXTI->PR,14)
#define  EXTI_LINE15_FLAGE   GET_BIT(EXTI->PR,15)

/******************************************************************************/
/************************ MASKS ***********************************************/
/******************************************************************************/
#define  EXTI_TRIGSRC_MASK    0b1
#define  EXTI_STATE_MASK      0b1
#define  EXTI_SOFT_TRIG_MASK  0b1
#define  EXTI_FLAG_MASK       0b1
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/





#endif
