/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  REGISTERS.h
 *         @Module	:  LIB
 *
 *  Description:  This file provide All STM32F103C8 (Blue Pill) Registers
 * 			      https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html#documentation
 *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 * HEADER GUARD
 *********************************************************************************************************************/
#ifndef REGISTERS_H_
#define REGISTERS_H_

 /*********************************************************************************************************************
 * RCC REGISTERS
 *********************************************************************************************************************/
#define RCC_u32BASE_ADDRESS		 0x40021000

typedef struct 
{
	volatile u32 RCC_CR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_AHBENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
}RCC_REG_DEF_t;

#define RCC			((RCC_REG_DEF_t*)RCC_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * GPIO REGISTERS
**********************************************************************************************************************/
#define GPIOA_u32BASE_ADDRESS		 0x40010800
#define GPIOB_u32BASE_ADDRESS		 0x40010C00
#define GPIOC_u32BASE_ADDRESS		 0x40011000

typedef struct
{
	volatile u32 GPIO_CRL;
	volatile u32 GPIO_CRH;
	volatile u32 GPIO_IDR;
	volatile u32 GPIO_ODR;
	volatile u32 GPIO_BSRR;
	volatile u32 GPIO_BRR;
	volatile u32 GPIO_LCKR;
}GPIO_REG_DEF_t;

#define GPIOA		((GPIO_REG_DEF_t*)GPIOA_u32BASE_ADDRESS)
#define GPIOB		((GPIO_REG_DEF_t*)GPIOB_u32BASE_ADDRESS)
#define GPIOC		((GPIO_REG_DEF_t*)GPIOC_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * NVIC REGISTERS
**********************************************************************************************************************/
#define NVIC_u32BASE_ADDRESS		 0xE000E100

typedef struct
{
	volatile u32 NVIC_ISER[3];
	volatile u32 RESERVED1[29];

	volatile u32 NVIC_ICER[3];
	volatile u32 RESERVED2[29];

	volatile u32 NVIC_ISPR[3];
	volatile u32 RESERVED3[29];

	volatile u32 NVIC_ICPR[3];
	volatile u32 RESERVED4[29];

	volatile u32 NVIC_IABR[3];
	volatile u32 RESERVED5[61];

	volatile u8 NVIC_IPR[84];

}NVIC_REG_DEF_t;

#define NVIC		((NVIC_REG_DEF_t*)NVIC_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * CSB REGISTER
**********************************************************************************************************************/
#define SCB_AIRCR 		*((volatile u32*)0xE000ED0C)


/**********************************************************************************************************************
 * EXTI REGISTERS
**********************************************************************************************************************/
#define EXTI_u32BASE_ADDRESS		 0x40010400

typedef struct
{
	volatile u32 EXTI_IMR;
	volatile u32 EXTI_EMR;
	volatile u32 EXTI_RTSR;
	volatile u32 EXTI_FTSR;
	volatile u32 EXTI_SWIER;
	volatile u32 EXTI_PR;

}EXTI_REG_DEF_t;

#define EXTI		((EXTI_REG_DEF_t*)EXTI_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * AFIO REGISTERS
**********************************************************************************************************************/
#define AFIO_u32BASE_ADDRESS		 0x40010000

typedef struct
{
	volatile u32 AFIO_EVCR;
	volatile u32 AFIO_MAPR;
	volatile u32 AFIO_EXTICR[4];
	volatile u32 AFIO_MAPR2;

}AFIO_REG_DEF_t;

#define AFIO		((AFIO_REG_DEF_t*)AFIO_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * SYSTICK REGISTERS
**********************************************************************************************************************/
#define STK_u32BASE_ADDRESS		 0xE000E010

typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;

}STK_REG_DEF_t;

#define STK			((STK_REG_DEF_t*)STK_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * TIM1 REGISTERS
 **********************************************************************************************************************/
#define TIM1_u32BASE_ADDRESS		 0x40012C00


typedef struct
{
	volatile u32 TIM1_CR1;
	volatile u32 TIM1_CR2;
	volatile u32 TIM1_SMCR;
	volatile u32 TIM1_DIER;
	volatile u32 TIM1_SR;
	volatile u32 TIM1_EGR;
	volatile u32 TIM1_CCMR1;
	volatile u32 TIM1_CCMR2;
	volatile u32 TIM1_CCER;
	volatile u32 TIM1_CNT;
	volatile u32 TIM1_PSC;
	volatile u32 TIM1_ARR;
	volatile u32 TIM1_RCR;
	volatile u32 TIM1_CCR1;
	volatile u32 TIM1_CCR2;
	volatile u32 TIM1_CCR3;
	volatile u32 TIM1_CCR4;
	volatile u32 TIM1_BDTR;
	volatile u32 TIM1_DCR;
	volatile u32 TIM1_DMAR;

}TIM1_REG_DEF_t;


#define TIM1			((TIM1_REG_DEF_t*)TIM1_u32BASE_ADDRESS)
/**********************************************************************************************************************
 * DMA REGISTERS
**********************************************************************************************************************/
#define DMA_u32BASE_ADDRESS		 0x40020000

typedef struct
{
	volatile u32 DMA_CCR;
	volatile u32 DMA_CNDTR;
	volatile u32 DMA_CPAR;
	volatile u32 DMA_CMAR;
	volatile u32 RESERVED;
}DMA_CHANNEL_t;

typedef struct
{
	volatile u32 DMA_ISR;
	volatile u32 DMA_IFCR;
	DMA_CHANNEL_t CHANNEL[7];
}DMA_REG_DEF_t;

#define DMA			((DMA_REG_DEF_t*)DMA_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * ADC REGISTERS
**********************************************************************************************************************/
#define ADC_u32BASE_ADDRESS		0x40012400

typedef struct
{
	u32 ADC_SR;
	u32 ADC_CR1;
	u32 ADC_CR2;
	u32 ADC_SMPR[2];
	u32 ADC_JOFR[4];
	u32 ADC_HTR;
	u32 ADC_LTR;
	u32 ADC_SQR[3];
	u32 ADC_JSQR;
	u32 ADC_JDR[4];
	u32 ADC_DR;
}ADC_REG_DEF_t;


#define ADC			((ADC_REG_DEF_t*)ADC_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * USART REGISTERS
**********************************************************************************************************************/
#define USART1_u32BASE_ADDRESS		 0x40013800
#define USART2_u32BASE_ADDRESS		 0x40004400
#define USART3_u32BASE_ADDRESS		 0x40004800

typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}USART_REG_DEF_t;

#define USART1		((USART_REG_DEF_t*)USART1_u32BASE_ADDRESS)
#define USART2		((USART_REG_DEF_t*)USART2_u32BASE_ADDRESS)
#define USART3		((USART_REG_DEF_t*)USART3_u32BASE_ADDRESS)


/**********************************************************************************************************************
 * SPI REGISTERS
**********************************************************************************************************************/
#define SPI1_u32BASE_ADDRESS		0x40013000
#define SPI2_u32BASE_ADDRESS		0x40003800

typedef struct
{
	volatile u32	SPI_CR1;
	volatile u32	SPI_CR2;
	volatile u32	SPI_SR;
	volatile u32	SPI_DR;
	volatile u32	SPI_CRCPR;
	volatile u32	SPI_RXCRCR;
	volatile u32	SPI_TXCRCR;
	volatile u32	SPI_I2SCFGR;
	volatile u32	SPI_I2SPR;
}SPI_REG_DEF_t;


#define SPI1		((SPI_REG_DEF_t*)SPI1_u32BASE_ADDRESS)
#define SPI2		((SPI_REG_DEF_t*)SPI2_u32BASE_ADDRESS)


#endif /* REGISTERS_H_ */

/**********************************************************************************************************************
 *  END OF FILE:  REGISTERS.h
 *********************************************************************************************************************/
