/********************************************************************************
 * 	@file        		:  MADC_int.h				 							*
 *	@Author 	 		:  HASSAN ABDELAZIM ABDELSALAM							*
 *	@Version 			:  1.0.0							 					*
 *	@Date				:  08/08/2023											*
 *********************************************************************************
 *  HEADER GAURD
 ********************************************************************************/
#ifndef MADC_MADC_INT_H_
#define MADC_MADC_INT_H_

/********************************************************************************
 * typedefs Enum
 ********************************************************************************/
typedef enum
{
	MADC_channel0,
	MADC_channel1,
	MADC_channel2,
	MADC_channel3,
	MADC_channel4,
	MADC_channel5,
	MADC_channel6,
	MADC_channel7,
	MADC_channel8,
	MADC_channel9,
	MADC_channel10,
	MADC_channel11,
	MADC_channel12,
	MADC_channel13,
	MADC_channel14,
	MADC_channel15,
	MADC_channel16,
	MADC_channel17
}MADC_CHANNELS_t;

typedef enum
{
	MADC_INDEX_0,
	MADC_INDEX_1,
	MADC_INDEX_2,
	MADC_INDEX_3,
	MADC_INDEX_4,
	MADC_INDEX_5,
	MADC_INDEX_6,
	MADC_INDEX_7,
	MADC_INDEX_8,
	MADC_INDEX_9,
	MADC_INDEX_10,
	MADC_INDEX_11,
	MADC_INDEX_12,
	MADC_INDEX_13,
	MADC_INDEX_14,
	MADC_INDEX_15,
	MADC_INDEX_16
}MADC_INDEX_t;
typedef enum
{
	MADC_SINGLE_CONV,
	MADC_CONTINUES_CONV,
	MADC_RIGHT_ALLIGN,
	MADC_LEFT_ALLIGN,
	MADC_DISABLE,
	MADC_ENABLE
}MADC_CONFIG_t;

typedef enum
{
	MADC_EOC_INT = 5,		  //Interrupt enable for EOC
	MADC_AWD_INT,			 // Analog watchdog interrupt enable
	MADC_JEOC_INT			//Interrupt enable for injected channels
}MADC_INT_t;

typedef enum
{
	MADC_SAMPLE_1_5CYCLE,
	MADC_SAMPLE_7_5CYCLE,
	MADC_SAMPLE_13_5CYCLE,
	MADC_SAMPLE_28_5CYCLE,
	MADC_SAMPLE_41_5CYCLE,
	MADC_SAMPLE_55_5CYCLE,
	MADC_SAMPLE_71_5CYCLE,
	MADC_SAMPLE_239_5CYCLE,
}MADC_SAMPLE_t;

typedef enum
{
	MADC_TIM1_CC1,
	MADC_TIM1_CC2,
	MADC_TIM1_CC3,
	MADC_TIM2_CC2,
	MADC_TIM3_TRGO,
	MADC_TIM4_CC4,
	MADC_EXTI_11,
	MADC_SWSTART
}MADC_REGTRIG_t;

typedef enum
{
	MADC_TIM1_TRGO,
	MADC_TIM1_CC4,
	MADC_TIM2_TRGO,
	MADC_TIM2_CC1,
	MADC_TIM3_CC4,
	MADC_TIM4_TRGO,
	MADC_EXTI_15,
	MADC_JSWSTART
}MADC_INJTRIG_t;

/********************************************************************************
 * typedefs Struct
 ********************************************************************************/

typedef struct
{
	MADC_CHANNELS_t channel;
	MADC_SAMPLE_t Sample;
	MADC_INDEX_t  Index;
}MADC_GROUP_t;


typedef struct
{
	MADC_CONFIG_t Conv_Mood;
	MADC_CONFIG_t Scan_Mood;
	MADC_CONFIG_t Data_Alignment;
	MADC_CHANNELS_t Reg_ChNum;
	MADC_REGTRIG_t	RegGP_trig;
	MADC_CHANNELS_t Inj_ChNum;
	MADC_INJTRIG_t	InjGP_trig;

}MADC_INIT_t;


/********************************************************************************
 * APIs Prototypes
 ********************************************************************************/
ErrorState_t MADC_enInit(MADC_INIT_t *ptr_u8config);
ErrorState_t MADC_enRegGroupChannel_Init(MADC_GROUP_t *ptr_u8RegConfig);
ErrorState_t MADC_enInjGroupChannel_Init(MADC_GROUP_t *ptr_u8Injconnfig);
ErrorState_t MADC_enRegChannel_Conv(u16 *ptr_u16data);
ErrorState_t MADC_enInjChannel_Conv(MADC_INDEX_t copy_u8Index, u16 *ptr_u16data);
ErrorState_t MADC_enEnableInt(MADC_INT_t copy_u8Interrupt);
ErrorState_t MADC_enDisableInt(MADC_INT_t copy_u8Interrupt);
ErrorState_t MADC_enIntCallBack(void(*CallBack_ptr)(void));



#endif /* MADC_MADC_INT_H_ */
