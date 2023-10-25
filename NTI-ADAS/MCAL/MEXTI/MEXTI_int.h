/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MEXTI_int.h
 *         @Module	:  EXTI
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MEXTI_EXTINT_INT_H_
#define MEXTI_EXTINT_INT_H_


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MEXTI0_LINE		        0
#define MEXTI1_LINE		        1
#define MEXTI2_LINE		        2
#define MEXTI3_LINE		        3
#define MEXTI4_LINE		        4
#define MEXTI5_LINE		        5
#define MEXTI6_LINE		        6
#define MEXTI7_LINE		        7
#define MEXTI8_LINE		        8
#define MEXTI9_LINE		        9
#define MEXTI10_LINE		    10
#define MEXTI11_LINE		    11
#define MEXTI12_LINE		    12
#define MEXTI13_LINE		    13
#define MEXTI14_LINE		    14
#define MEXTI15_LINE		    15

#define MEXTI_RISING_TRIG	    1
#define MEXTI_FAILING_TRIG	    2
#define MEXTI_LOGIC_CHANGE	    3


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorState_t MEXTI_enInit(void);
ErrorState_t MEXTI_enSetLatch(u8 Copy_u8LineId, u8 Copy_u8Mode);
ErrorState_t MEXTI_enDisable(u8 Copy_u8LineId);
ErrorState_t MEXTI_enCallBack(u8 Copy_u8LineId, void (*ptr) (void));
ErrorState_t MEXTI_enSWInterrupt(u8 Copy_u8LineId);
ErrorState_t MEXTI_enClearPendingBit(u8 Copy_u8LineId);


#endif /* MEXTI_EXTINT_INT_H_ */
/**********************************************************************************************************************
 *  END OF FILE: MEXTI_int.h
 *********************************************************************************************************************/

