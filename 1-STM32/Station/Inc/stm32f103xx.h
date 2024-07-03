/**
 ******************************************************************************
 * @file           : stm32f103xx.h
 * @author         : Diea Abdeltwab
 * @brief          : Version 1 For STM32F103C8T6 Drivers
 * @date           : 25/3/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef STM32F103xx_h
#define STM32F103xx_h
/************************************************************************************************/
/******************************** RCC Registers *************************************************/
/************************************************************************************************/

#define RCC_BASE_ADDRESS                              0x40021000U

typedef struct
{
	volatile uint32_t CR		;
	volatile uint32_t CFGR		;
	volatile uint32_t CIR		;
	volatile uint32_t APB2RSTR	;
	volatile uint32_t APB1RSTR	;
	volatile uint32_t AHBENR	;
	volatile uint32_t APB2ENR	;
	volatile uint32_t APB1ENR	;
	volatile uint32_t BDCR		;
	volatile uint32_t CSR		;
}RCC_REG;

#define RCC                           ((RCC_REG*)RCC_BASE_ADDRESS)

/************************************************************************************************/
/************************************* GPIO Registers *******************************************/
/************************************************************************************************/
#define GPIOA_BASE_ADDRESS                       0x40010800U
#define GPIOB_BASE_ADDRESS                       0x40010C00U
#define GPIOC_BASE_ADDRESS                       0x40011000U

typedef struct
{
	volatile uint32_t CR[2]	;
	volatile uint32_t IDR	;
	volatile uint32_t ODR	;
	volatile uint32_t BSRR	;
	volatile uint32_t BRR	;
	volatile uint32_t LCKR	;
}GPIO_REG;

#define GPIOA                          ((GPIO_REG*)GPIOA_BASE_ADDRESS)
#define GPIOB                          ((GPIO_REG*)GPIOB_BASE_ADDRESS)
#define GPIOC                          ((GPIO_REG*)GPIOC_BASE_ADDRESS)

/************************************************************************************************/
/********************************* SYSTICK Registers ********************************************/
/************************************************************************************************/
#define STK_BASE_ADDRESS                               0xE000E010U

typedef struct
{
	volatile uint32_t CTRL  ;
	volatile uint32_t LOAD  ;
	volatile uint32_t VAL   ;
	volatile uint32_t CALIB ;
}STK_REG;

#define STK                                  ((STK_REG*)STK_BASE_ADDRESS)

/************************************************************************************************/
/******************************** NVIC Registers ************************************************/
/************************************************************************************************/
#define NVIC_BASE_ADDRESS                               0xE000E100U

typedef struct
{
	volatile uint32_t ISER[8];		/*Interrupt set-enable register*/
	uint32_t Reserved1[24];
	volatile uint32_t ICER[8];		/*Interrupt clear-enable register*/
	uint32_t Reserved[24];
	volatile uint32_t ISPR[8];		/*Interrupt set-pending register*/
	uint32_t Reserved2[24];
	volatile uint32_t ICPR[8];		/*Interrupt clear-pending register*/
	uint32_t Reserved4[24];
	volatile uint32_t IABR[8];		/*Interrupt active bit register*/
	uint32_t Reserved3[32];
	volatile uint8_t IPR[240];		/*Interrupt priority register*/
}NVIC_REG;

#define NVIC                                  ((NVIC_REG*)NVIC_BASE_ADDRESS)

/************************************************************************************************/
/********************************* EXTI Registers ***********************************************/
/************************************************************************************************/
#define EXTI_BASE_ADDRESS                                0x40010400U

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_REG;

#define EXTI                                  ((EXTI_REG*)EXTI_BASE_ADDRESS)

/************************************************************************************************/
/******************************** AFIO Registers ************************************************/
/************************************************************************************************/
#define AFIO_BASE_ADDRESS                                 0x40010000U
typedef	struct
{
	volatile uint32_t  EVCR       ;
	volatile uint32_t  MAPR       ;
	volatile uint32_t  EXTICR[4]  ;
	volatile uint32_t  MAPR2      ;

}AFIO_REG;

#define  AFIO                     ( ( AFIO_REG *) AFIO_BASE_ADDRESS )

/************************************************************************************************/
/******************************** SCB Registers *************************************************/
/************************************************************************************************/
#define SCB_BASE_ADDRESS                               0xE000ED00U

typedef struct{

	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	volatile uint32_t SHPR1;
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
	volatile uint32_t SHCSR;
	volatile uint32_t CFSR;
	volatile uint32_t HFSR;
	volatile uint32_t RESERVED;
	volatile uint32_t MMFAR;
	volatile uint32_t BFAR;

}SCB_REG;

#define SCB                                   (( SCB_REG *) SCB_BASE_ADDRESS )
/************************************************************************************************/
/******************************** DMA Registers ************************************************/
/************************************************************************************************/
#define DMA1_u32_BASE_ADDRESS                                0x40020000U
#define DMA2_u32_BASE_ADDRESS                                0x40020400U
typedef struct{

	volatile uint32_t CCR       ;
	volatile uint32_t CNDTR     ;
	volatile uint32_t CPAR      ;
	volatile uint32_t CMAR      ;
	volatile uint32_t RESERVED  ;

}DMA_CHANNEL;

typedef struct{

	volatile uint32_t ISR  ;
	volatile uint32_t IFCR ;
	DMA_CHANNEL  CHANNEL[8];

}DMA_REG ;

#define DMA ( ( DMA_REG * ) DMA1_u32_BASE_ADDRESS )
//#define DMA2 ( ( volatile DMA_REG * ) DMA2_u32_BASE_ADDRESS )
/************************************************************************************************/
/******************************** USART Registers ***********************************************/
/************************************************************************************************/
#define USART1_u32_BASE_ADDRESS                                0x40013800U
#define USART2_u32_BASE_ADDRESS                                0x40004400U
#define USART3_u32_BASE_ADDRESS                                0x40004800U
#define  UART4_u32_BASE_ADDRESS                                0x40004C00U
#define  UART5_u32_BASE_ADDRESS                                0x40005000U
 typedef	struct
{
	volatile uint32_t SR     ;
	volatile uint32_t DR     ;
	volatile uint32_t BRR      ;
	volatile uint32_t CR1      ;
	volatile uint32_t CR2   ;
	volatile uint32_t CR3  ;
	volatile uint32_t GTPR  ;

} USART_REG ;

#define  USART1                     ( (  USART_REG *) USART1_u32_BASE_ADDRESS )
#define  USART2                     ( (  USART_REG *) USART2_u32_BASE_ADDRESS )
#define  USART3                     ( (  USART_REG *) USART3_u32_BASE_ADDRESS )
#define   UART4                     ( (  USART_REG *) UART4_u32_BASE_ADDRESS  )
#define   UART5                     ( (  USART_REG *) UART5_u32_BASE_ADDRESS  )
/************************************************************************************************/
/******************************** SPI Registers ************************************************/
/************************************************************************************************/
#define SPI1_u32_BASE_ADDRESS                                0x40013000U
#define SPI2_u32_BASE_ADDRESS                                0x40003800U
#define SPI3_u32_BASE_ADDRESS                                0x40003C00U

 typedef	struct
{
	volatile uint32_t CR1     ;
	volatile uint32_t CR2     ;
	volatile uint32_t SR      ;
	volatile uint32_t DR      ;
	volatile uint32_t CRCPR   ;
	volatile uint32_t RXCRCR  ;
	volatile uint32_t TXCRCR  ;
	volatile uint32_t I2SCFGR ;
	volatile uint32_t I2SPR   ;

} SPI_REG ;

#define  SPI1                     ( ( SPI_REG *) SPI1_u32_BASE_ADDRESS )
#define  SPI2                     ( ( SPI_REG *) SPI2_u32_BASE_ADDRESS )
#define  SPI3                     ( ( SPI_REG *) SPI3_u32_BASE_ADDRESS )
/************************************************************************************************/
/******************************** I2C Registers *************************************************/
/************************************************************************************************/
#define I2C1_u32_BASE_ADDRESS                                0x40005400U
#define I2C2_u32_BASE_ADDRESS                                0x40005800U

typedef struct{

	volatile uint32_t	CR1;
	volatile uint32_t   CR2;
	volatile uint32_t	OAR1;
	volatile uint32_t	OAR2;
	volatile uint32_t	DR;
	volatile uint32_t	SR1;
	volatile uint32_t	SR2;
	volatile uint32_t	CCR;
	volatile uint32_t	TRISE;

}I2C_REG;

#define I2C1		(( I2C_REG*)(I2C1_u32_BASE_ADDRESS))
#define I2C2		(( I2C_REG*)(I2C2_u32_BASE_ADDRESS))
/************************************************************************************************/
/******************************** GPTIMER Registers *********************************************/
/************************************************************************************************/
#define TMR2_u32_BASE_ADDRESS                                0x40000000U
#define TMR3_u32_BASE_ADDRESS                                0x40000400U
#define TMR4_u32_BASE_ADDRESS                                0x40000800U
#define TMR5_u32_BASE_ADDRESS                                0x40000C00U



typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR[2];
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t CCR[4];
	volatile uint32_t RESERVED_2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
}GPTIMER_REG;


#define TMR2		(( GPTIMER_REG *)(TMR2_u32_BASE_ADDRESS))
#define TMR3		(( GPTIMER_REG *)(TMR3_u32_BASE_ADDRESS))
#define TMR4		(( GPTIMER_REG *)(TMR4_u32_BASE_ADDRESS))
#define TMR5		(( GPTIMER_REG *)(TMR5_u32_BASE_ADDRESS))

/************************************************************************************************/
/******************************** BTIMER Registers **********************************************/
/************************************************************************************************/
#define TMR6_u32_BASE_ADDRESS                                0x40001000U
#define TMR7_u32_BASE_ADDRESS                                0x40001400U

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t Reserved_0;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t Reserved_1[2];
	volatile uint32_t Reserved_2;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}BTIMER_REG;


#define TMR6		(( BTIMER_REG *)(TMR6_u32_BASE_ADDRESS))
#define TMR7		(( BTIMER_REG *)(TMR7_u32_BASE_ADDRESS))
/************************************************************************************************/
/******************************** ADC Registers *************************************************/
/************************************************************************************************/
#define ADC1_u32_BASE_ADDRESS                                0x40012400U
#define ADC2_u32_BASE_ADDRESS                                0x40012800U
#define ADC3_u32_BASE_ADDRESS                                0x40013C00U

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR[3];
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
}ADC_REG;

#define ADC1		(( ADC_REG *)(ADC1_u32_BASE_ADDRESS))
#define ADC2		(( ADC_REG *)(ADC2_u32_BASE_ADDRESS))
#define ADC3		(( ADC_REG *)(ADC3_u32_BASE_ADDRESS))



/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

#endif
