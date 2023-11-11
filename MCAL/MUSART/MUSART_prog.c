/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MUSART_prog.c
 *         @Module	:  USART
 *
 *  Description:  This file provide Module APIs code Implementation
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "REGISTERS.h"
#include "BIT_MATH.h"
#include "MUSART_int.h"
#include "MUSART_config.h"
#include "MUSART_priv.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u8  Receive_Flag = 0;

u8  uart_TxBufferIndex = 0;
u8  uart_RxBufferIndex = 0;

u8  uart_TxBUFFER[MUSART_TXBUFFER_SIZE] ;
u8  uart_RxBUFFER[MUSART_RXBUFFER_SIZE] ;

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
/* Initialize an array of three pointers of USART Channels to Registers */
static volatile USART_REG_DEF_t* USART_CH[MUSART_MAX_LINES] = {USART1, USART2, USART3};
static void(*MUSART_CALLBACK[MUSART_MAX_LINES])(void) = {0};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enInit(MUSART_t copy_u8USARTnum)
 *
 * \Description     : This Services for Initialize all <pre> configuration of the Frame
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/

ErrorState_t MUSART_enInit(MUSART_t copy_u8USARTnum, MUSART_INIT_t *ptr_u8cfg)
{

	/* @brief 	This API use to Initialize all <pre> configuration of USART Frame
	 *			Half Duplex or Full Duplex, Parity even or odd or Disabled
	 *		 	8bit or 9bit Data Frame, 1bit or 2bit Stop bit
	 *		 	Select the Required BaudRate,Enable TX,RX,USART */

	ErrorState_t local_state = SUCCESS;
	if (copy_u8USARTnum <= MUSART3)
	{
		if (ptr_u8cfg != NULL)
		{
			/* 1. Select USART FULL OR HALF DUPLEX */
			switch (ptr_u8cfg ->MUSART_WIRE_MODE)
			{
			case MUSART_HALF_DUPLEX:
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR3, HDSE);
				break;

			case MUSART_FULL_DUPLEX:
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR3, HDSE);
				break;

			default:
				local_state = OUT_OF_RANG_ERR;
			}


			/* 2. Select USART 8Bit or 9bit Data Size */
			switch (ptr_u8cfg ->MUSART_DATA_SIZE)
			{
			case MUSART_8BIT_DATA:
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, M);
				break;

			case MUSART_9BIT_DATA:
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, M);
				break;

			default:
				local_state = OUT_OF_RANG_ERR;
			}


			/* 	3.Select ODD OR EVEN OR DISABLED PARITY	*/
			switch (ptr_u8cfg ->MUSART_PARITY_MODE)
			{
			case MUSART_PARITY_EVEN:
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, PCE);
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, PS);
				break;

			case MUSART_PARITY_ODD:
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, PCE);
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, PS);
				break;

			case MUSART_PARITY_DISABLE:
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, PCE);
				break;
			default:
				local_state = OUT_OF_RANG_ERR;
			}


			/* 4. Select 1BIT OR 2BIT STOP BITS */
			switch (ptr_u8cfg ->MUSART_STOP_MODE)
			{
			case MUSART_STOPBIT1:
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR2, STOP1);
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR2, STOP2);
				break;

			case MUSART_STOPBIT2:
				CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR2, STOP1);
				SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR2, STOP2);
				break;

			default:
				local_state = OUT_OF_RANG_ERR;
			}

			/* 5. Select The Requirement Baud Rate */
			USART_CH[copy_u8USARTnum]->USART_BRR = ptr_u8cfg->MUSART_BAUDRATE;

			/* 6. Enable The Transmission Mode */
			SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, TE);

			/* 7. Enable The Receiver Mode */
			SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, RE);

			/* 8. Enable The USART Peripheral */
			SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, UE);

			/* 9. Clear the USART Flags Register */
			USART_CH[copy_u8USARTnum]->USART_SR = 0;
		}
		else
		{
			local_state = NULL_PTR_ERR;
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}


/******************************************************************************
 * \Syntax          : ErrorState_t  MUSART_enBusySendByte
 * 									(MUSART_t copy_u8USARTnum, u8 copy_u8Data)
 *
 * \Description     : This Services for transmitt byte by TX USART
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, copy_u8Data
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MUSART_enBusySendByte(MUSART_t copy_u8USARTnum, u8 copy_u8Data)
{
	/*
	 *	@brief 	This API use the Polling Technique to transmit the data
	 *	1. waiting of TX Empty Flag to be set
	 *	2. copy the Data into the USART Data Register
	 *	3. Clear the TX Complete flag by writing 0 into it		*/

	ErrorState_t local_state = SUCCESS;
	if (copy_u8USARTnum <= MUSART3)
	{
		while (!(GET_BIT(USART_CH[copy_u8USARTnum]->USART_SR, TXE)));
		USART_CH[copy_u8USARTnum]->USART_DR = copy_u8Data;

		while (!(GET_BIT(USART_CH[copy_u8USARTnum]->USART_SR, TC)));
		CLR_BIT(USART_CH[copy_u8USARTnum]->USART_SR, TC);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t  MUSART_enBusySendString
 * 								(MUSART_t copy_u8USARTnum, char *copy_u8Data)
 *
 * \Description     : This Services for transmitt string of bytes by TX USART
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, *copy_u8Data
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MUSART_enBusySendString(MUSART_t copy_u8USARTnum, u8 *copy_u8Data)
{
	/*@brief 	This API use the Polling Technique to transmit the string of Byte data
	 * 	 1. Initialize a local counter to iterate through the string
	 * 	 2. check the end of the string if has NULL CHR or Not, if Not iterate
	 * 	 3. Send Byte by Byte of string indexed by local Counter
	 * 	 4. count up the local counter
	 */
	ErrorState_t local_state = SUCCESS;

	u8 local_u8Counter = 0;
	if (copy_u8USARTnum <= MUSART3)
	{
		if (copy_u8Data != NULL)
			while (copy_u8Data[local_u8Counter] != '\0')
			{
				MUSART_enBusySendByte(copy_u8USARTnum, copy_u8Data[local_u8Counter]);
				local_u8Counter++;
			}
		else
		{
			local_state = NULL_PTR_ERR;
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enBusyReceiveByte
 * 									(MUSART_t copy_u8USARTnum, u8 *ptr_u8Data)
 *
 * \Description     : This Services for Receive byte by RX USART
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, *ptr_u8Data
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MUSART_enBusyReceiveByte(MUSART_t copy_u8USARTnum, u8 *ptr_u8Data)
{
	/* @brief 	This API use the Polling Technique to Receive the data
	 *	1. waiting of RX Not Empty Flag to be set
	 *	2. get the Data from Data Register AND with 1Byte
	 * 	3. Assign the value into the ptr_u8Data to be returned as ptr
	 * 	4. the flag is cleared by reading the Data from the register		*/
	ErrorState_t local_state = SUCCESS;
	if (copy_u8USARTnum <= MUSART3)
	{
		if (ptr_u8Data != NULL)
		{
			while (!(GET_BIT(USART_CH[copy_u8USARTnum]->USART_SR, RXNE)));
			*ptr_u8Data = USART_CH[copy_u8USARTnum]->USART_DR & MUSART_1BYTE;
		}
		else
		{
			local_state = NULL_PTR_ERR;
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enEnableInt
 * 							(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum)
 *
 * \Description     : This Services for Enable correspoinding USART Interrupt
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, copy_u8Intnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/

ErrorState_t MUSART_enEnableInt(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum)
{
	/*@brief 	This API use to Enable Interrupt of the Corresponding Event
	 *			Error, IDLE, RXNEmpty, TXCompelete, TXEmpty, ParityEror Interrupt
	 *
	 *			Set the Interrupt register pin based on the event
	 */
	ErrorState_t local_state = SUCCESS;
	if ((copy_u8Intnum >= IDLE_INT) && (copy_u8Intnum <= ParityEror_INT)&& copy_u8USARTnum <= MUSART3)
	{
		SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, copy_u8Intnum);
	}
	else if (copy_u8Intnum == Error_INT)
	{
		SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR3, copy_u8Intnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enDisableInt
 * 							(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum)
 *
 * \Description     : This Services for Disable correspoinding USART Interrupt
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, copy_u8Intnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MUSART_enDisableInt(MUSART_t copy_u8USARTnum, MUSART_INT_t copy_u8Intnum)
{
	/*@brief 	This API use to Disable Interrupt of the Corresponding Event
	 *			Error, IDLE, RXNEmpty, TXCompelete, TXEmpty, ParityError Interrupt
	 *
	 *			clear the Interrupt register pin based on the event
	 */
	ErrorState_t local_state = SUCCESS;
	if ((copy_u8Intnum >= IDLE_INT) && (copy_u8Intnum <= ParityEror_INT)&& copy_u8USARTnum <= MUSART3)
	{
		CLR_BIT(USART_CH[copy_u8USARTnum]->USART_CR1, copy_u8Intnum);
	}
	else if (copy_u8Intnum == Error_INT)
	{
		SET_BIT(USART_CH[copy_u8USARTnum]->USART_CR3, copy_u8Intnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enSendMessage
 * 							(MUSART_t copy_u8USARTnum, u8 *copy_u8msg)
 * \Description     : This Services for store the Tx buffer to transmit
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, *copy_u8msg
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MUSART_enSendMessage(MUSART_t copy_u8USARTnum, u8 *copy_u8msg)
{
	/*@ brief This API use to store the TX_buffer to send by interrupt ASynchronous
	 * 1. copy string of bytes or byte from user to Tx buffer
	 * 2. if the buffer element was NULL break it
	 * 3.  send the first byte
	 * */
	ErrorState_t local_state = SUCCESS;
	if (copy_u8USARTnum <= MUSART3)
	{
		for (u8 i = 0; i < MUSART_TXBUFFER_SIZE; i++)
		{
			uart_TxBUFFER[i] = copy_u8msg[i];

			if (uart_TxBUFFER[i] == MUSART_NULL_CHR)
				break;
		}
		USART_CH[MUSART1]->USART_DR =  uart_TxBUFFER[uart_TxBufferIndex];
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enReceieveMessage
 * 							(MUSART_t copy_u8USARTnum, u8 *copy_u8msg)
 *
 * \Description     : This Services for store the msg from RX buffer
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, copy_u8msg[]
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/

ErrorState_t MUSART_enReceieveMessage(MUSART_t copy_u8USARTnum, u8 *copy_u8msg)
{

	/*@ brief This API use to store the msg from RX buffer with interrupt ASynchronous
	 * 1. copy string of bytes or byte from Rx buffer to App buffer to return it
	 * 2. if the buffer element was ENDline char break it
	 * 3.  exchange the EndLine char with the NUll char
	 * 4. clear the receieve flag to receieve data again
	 * */
	ErrorState_t local_state = SUCCESS;
	if (copy_u8USARTnum <= MUSART3)
	{
		for (u8 i = 0; i <MUSART_RXBUFFER_SIZE; i++ )
		{
			copy_u8msg[i] = uart_RxBUFFER[i];

			if (copy_u8msg[i] == MUSART_END_LINE)
			{
				copy_u8msg[i] = MUSART_NULL_CHR;
				Receive_Flag = 0;
				break;
			}
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MUSART_enIntCallBack
 * 							(MUSART_t copy_u8USARTnum, void (*ptr)(void))
 *
 * \Description     : This Services for callback APP fun based on USART Interrupt
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8USARTnum, ptr
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/

ErrorState_t MUSART_enIntCallBack(MUSART_t copy_u8USARTnum, void (*ptr)(void))
{
	/*
	 *@brief 	MUSART Interrupt callBack of the Corresponding Event
	 *			Error, IDLE, RXNEmpty, TXCompelete, TXEmpty, ParityEror Interrupt
	 *
	 *			Assign the callback fun with pointer to function
	 */

	ErrorState_t local_state = SUCCESS;
	if (ptr != NULL)
	{
		MUSART_CALLBACK[copy_u8USARTnum] = ptr;
	}
	else
	{
		local_state = NULL_PTR_ERR;
	}

	return local_state;
}



/**********************************************************************************************************************
 *  HANDLER REQUEST
 *********************************************************************************************************************/
/*	@breif 	when tranmitt the data by Interrupt,1.check if the TxEmpty is set
 * 			2. update the tx buffer every time interrupt firing
 * 			3, check if that byte transmitted Null charcter, then reset the index
 * 			4. if was not send the next byte which stored in the TX buffer
 * 			---------------------------------------------------------------------------------------------------------
 * 			when receiving data by interrupt, 1. get the first byte from the data register
 * 			2. check if that byte the ENDline byte, if so then reset the index and set the Rec_flag
 * 			3. if was not update the index to receieve the next byte */

void USART1_IRQHandler (void)
{
	if ((GET_BIT(USART_CH[MUSART1]->USART_SR, TXE)))
	{
		uart_TxBufferIndex++;
		if (uart_TxBUFFER[uart_TxBufferIndex] == MUSART_NULL_CHR)
		{
			uart_TxBufferIndex = 0;
		}
		else
		{
			USART_CH[MUSART1]->USART_DR =  uart_TxBUFFER[uart_TxBufferIndex];

		}
	}

	if (GET_BIT(USART_CH[MUSART1]->USART_SR, RXNE))
	{
		uart_RxBUFFER[uart_RxBufferIndex] = USART_CH[MUSART1]->USART_DR ;

		if (uart_RxBUFFER[uart_RxBufferIndex] == MUSART_END_LINE)
		{
			uart_RxBufferIndex = 0;
			Receive_Flag = 1;
		}
		else
		{
			uart_RxBufferIndex++;
		}
	}
}

void USART2_IRQHandler (void)
{

	if ((GET_BIT(USART_CH[MUSART2]->USART_SR, TXE)))
	{
		uart_TxBufferIndex++;
		if (uart_TxBUFFER[uart_TxBufferIndex] == MUSART_NULL_CHR)
		{
			uart_TxBufferIndex = 0;
		}
		else
		{
			USART_CH[MUSART2]->USART_DR =  uart_TxBUFFER[uart_TxBufferIndex];

		}
	}

	if (GET_BIT(USART_CH[MUSART2]->USART_SR, RXNE))
	{
		uart_RxBUFFER[uart_RxBufferIndex] = USART_CH[MUSART1]->USART_DR ;

		if (uart_RxBUFFER[uart_RxBufferIndex] == MUSART_END_LINE)
		{
			uart_RxBufferIndex = 0;
			Receive_Flag = 1;
		}
		else
		{
			uart_RxBufferIndex++;
		}
	}
}

void USART3_IRQHandler (void)
{
	if ((GET_BIT(USART_CH[MUSART3]->USART_SR, TXE)))
	{
		uart_TxBufferIndex++;
		if (uart_TxBUFFER[uart_TxBufferIndex] == MUSART_NULL_CHR)
		{
			uart_TxBufferIndex = 0;
		}
		else
		{
			USART_CH[MUSART3]->USART_DR =  uart_TxBUFFER[uart_TxBufferIndex];
		}
	}

	if (GET_BIT(USART_CH[MUSART3]->USART_SR, RXNE))
	{
		uart_RxBUFFER[uart_RxBufferIndex] = USART_CH[MUSART3]->USART_DR ;

		if (uart_RxBUFFER[uart_RxBufferIndex] == MUSART_END_LINE)
		{
			uart_RxBufferIndex = 0;
			Receive_Flag = 1;
		}
		else
		{
			uart_RxBufferIndex++;
		}
	}
}
/**********************************************************************************************************************
 *  END OF FILE:  MUSART_prog.c
 *********************************************************************************************************************/

