 /**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MRCC_int.h
 *         @Module	:  RCC
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MRCC_INT_H_
#define MRCC_INT_H_


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

// Peripheral CLOCK

#define MRCC_DMA1			0
#define MRCC_SRAM			2
#define MRCC_FLITF			4
#define MRCC_CRC			6
#define MRCC_FSMCEN			8
#define MRCC_SDIOEN			10
#define MRCC_TIM2			32
#define MRCC_TIM3 			33
#define MRCC_TIM4			34
#define MRCC_WWD			43
#define MRCC_SPI2			46
#define MRCC_USART2			49
#define MRCC_USART3			50
#define MRCC_I2C1			53
#define MRCC_I2C2			54
#define MRCC_USB			55
#define MRCC_CAN			57
#define MRCC_BKPRST			59
#define MRCC_PWRRST			60
#define MRCC_DACRST			61
#define MRCC_AFIO			64
#define MRCC_IOPA			66
#define MRCC_IOPB			67
#define MRCC_IOPC			68
#define MRCC_ADC1			73
#define MRCC_ADC2			74
#define MRCC_TIM1			75
#define MRCC_SPI1			76
#define MRCC_USART1			78


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorState_t MRCC_enSysClkINIT(void);
ErrorState_t MRCC_enEnablePeripheralCLK(u8 copy_u8Peripheral);
ErrorState_t MRCC_enDisablePeripheralCLK(u8 copy_u8Peripheral);

#endif  /* MRCC_INT_H_ */

/**********************************************************************************************************************
 *  END OF FILE: MRCC_int.h
 *********************************************************************************************************************/

