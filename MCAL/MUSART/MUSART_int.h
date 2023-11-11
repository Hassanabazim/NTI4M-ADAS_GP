/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MUSART_int.h
 *         @Module	:  USART
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MUSART_MUSART_INT_H_
#define MUSART_MUSART_INT_H_

/**********************************************************************************************************************
*	INTERFACING MACROS
 *********************************************************************************************************************/
#define MUSART1_TX_PIN		PORTA, PIN9
#define MUSART1_RX_PIN		PORTA, PIN10

#define MUSART2_TX_PIN		PORTA, PIN2
#define MUSART2_RX_PIN		PORTA, PIN3

#define MUSART3_TX_PIN		PORTB, PIN10
#define MUSART3_RX_PIN		PORTB, PIN11

/**********************************************************************************************************************
*	GLOBAL MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//USART CHANNELS (USART1 .. 3)
typedef enum
{
	MUSART1, MUSART2, MUSART3
}MUSART_t;

typedef enum
{
	MUSART_HALF_DUPLEX, MUSART_FULL_DUPLEX,
	MUSART_8BIT_DATA, MUSART_9BIT_DATA,
	MUSART_PARITY_EVEN, MUSART_PARITY_ODD,MUSART_PARITY_DISABLE,
	MUSART_STOPBIT1,MUSART_STOPBIT2,

}MUSART_CFG_t;

typedef struct
{
	MUSART_CFG_t MUSART_WIRE_MODE;
	MUSART_CFG_t MUSART_DATA_SIZE;
	MUSART_CFG_t MUSART_PARITY_MODE;
	MUSART_CFG_t MUSART_STOP_MODE;
	u32 		MUSART_BAUDRATE;

}MUSART_INIT_t;

//USART INTRRUPTS
typedef enum
{
	Error_INT,
	IDLE_INT = 4,
	RXNEmpty_INT,
	TXCompelete_INT,
	TXEmpty_INT,
	ParityEror_INT,
}MUSART_INT_t;

/**********************************************************************************************************************
 *  GLOBAL MACROS
 *********************************************************************************************************************/
// BAUDRATE CONFIGURATION
#define MUSART_BAUDRATE_1200_CLK_8M       0X1A0B
#define MUSART_BAUDRATE_2400_CLK_8M       0X0D05
#define MUSART_BAUDRATE_4800_CLK_8M       0X0683
#define MUSART_BAUDRATE_9600_CLK_8M       0X0341
#define MUSART_BAUDRATE_19200_CLK_8M      0X01A1

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

ErrorState_t MUSART_enInit(MUSART_t copy_u8USARTnum, MUSART_INIT_t *ptr_u8cfg);
ErrorState_t MUSART_enBusySendByte(MUSART_t copy_u8USARTnum, u8 copy_u8Data);
ErrorState_t MUSART_enSendMessage(MUSART_t copy_u8USARTnum, u8 *copy_u8msg);
ErrorState_t MUSART_enBusyReceiveByte(MUSART_t copy_u8USARTnum, u8 *ptr_u8Data);
ErrorState_t MUSART_enEnableInt(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum);
ErrorState_t MUSART_enDisableInt(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum);
ErrorState_t MUSART_enSendMessage(MUSART_t copy_u8USARTnum, u8 *copy_u8msg);
ErrorState_t MUSART_enReceieveMessage(MUSART_t copy_u8USARTnum, u8 *copy_u8msg);
ErrorState_t MUSART_enIntCallBack(MUSART_t copy_u8USARTnum, void (*ptr)(void));



#endif /* MUSART_MUSART_INT_H_ */
/**********************************************************************************************************************
 *  END OF FILE:   MUSART_int.h
 *********************************************************************************************************************/
