/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MNVIC_int.h
 *         @Module	:  NVIC
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MNVIC_MNVIC_INT_H_
#define MNVIC_MNVIC_INT_H_

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
// NVIC Vector Table

#define   MNVIC_WWDG_INT		        0
#define   MNVIC_PVD_INT			        1
#define   MNVIC_TAMPER_IN		        2
#define   MNVIC_RTC_INT			        3
#define   MNVIC_FLASH_INT		        4
#define   MNVIC_RCC_INT			        5
#define   MNVIC_EXT0_INT                6
#define   MNVIC_EXT1_INT                7
#define   MNVIC_EXT2_INT                8
#define   MNVIC_EXT3_INT                9
#define   MNVIC_EXT4_INT                10
#define   MNVIC_DMA1_CH1_INT            11
#define   MNVIC_DMA1_CH2_INT            12
#define   MNVIC_DMA1_CH3_INT            13
#define   MNVIC_DMA1_CH4_INT            14
#define   MNVIC_DMA1_CH5_INT            15
#define   MNVIC_DMA1_CH6_INT            16
#define   MNVIC_DMA1_CH7_INT            17
#define   MNVIC_ADC1_2_INT              18
#define   MNVIC_USBHP_CANTX_INT         19
#define   MNVIC_USBLP_CANTX_INT         20
#define   MNVIC_CANRX1_INT              21
#define   MNVIC_CAN_SCE_INT             22
#define   MNVIC_EXT9_5INT               23
#define   MNVIC_TIM1_BRK_INT            24
#define   MNVIC_TIM1_UP_INT             25
#define   MNVIC_TIME1_TRG_COM_INT       26
#define   MNVIC_TIM1_CC_INT             27
#define   MNVIC_TIM2_INT                28
#define   MNVIC_TIM3_INT                29
#define   MNVIC_TIM4_INT                30
#define   MNVIC_I2C1_EV_INT             31
#define   MNVIC_I2C1_ER_INT             32
#define   MNVIC_I2C2_EV_INT             33
#define   MNVIC_I2C2_ER_INT             34
#define   MNVIC_SPI1_INT                35
#define   MNVIC_SPI2_INT                36
#define   MNVIC_USART1_INT              37
#define   MNVIC_USART2_INT              38
#define   MNVIC_USART3_INT              39
#define   MNVIC_EXT15_10INT             40
#define   MNVIC_RTCALARM_INT            41
#define   MNVIC_USBWAKEUP_INT           42
#define   MNVIC_FSMC_INT                48
#define   MNVIC_SDIO_INT                49



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorState_t MNVIC_enEnableNVIC(void);
ErrorState_t MNVIC_enEnableInt(u8 copy_u8IRQnum);
ErrorState_t MNVIC_enDisableInt(u8 copy_u8IRQnum);
ErrorState_t MNVIC_enSetPendingFlag(u8 copy_u8IRQnum);
ErrorState_t MNVIC_enClrPendingFlag(u8 copy_u8IRQnum);
ErrorState_t MNVIC_enGetPendingFlag(u8 copy_u8IRQnum, u8 *PendingState);
ErrorState_t MNVIC_enGetActiveFlag(u8 copy_u8IRQnum, u8 *ActiveState);
ErrorState_t MNVIC_enSetPriority(u8 copy_u8IRQnum, u8 copy_u8Group, u8 copy_u8Sub);


#endif /* MNVIC_MNVIC_INT_H_ */
/**********************************************************************************************************************
 *  END OF FILE: MNVIC_int.h
 *********************************************************************************************************************/

