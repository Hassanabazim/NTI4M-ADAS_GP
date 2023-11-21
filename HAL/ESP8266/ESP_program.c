
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MRCC_int.h"
#include "MGPIO_int.h"
#include "MUSART_int.h"
#include "MSYSTICK_int.h"
#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

ErrorState_t ESP_voidInit(void)
{
	ErrorState_t Local_xErrorStatus	=	FAILARE;

	u8 Local_charDataReceive1[6] = {0};
	u8 Local_charDataReceive2[6] = {0};

	/* Enable UART1 */
	MRCC_enEnablePeripheralCLK(MRCC_USART1);

	/*Set Pin Direction for UART2*/
	MGPIO_enSetPinDirection(MUSART1_TX_PIN,OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(MUSART1_RX_PIN,IN_FLOATING);
	/*      Configuration for  UART
	 * -->Baud rate =115200
	 * -->Data size=8 bit
	 * -->Parity mode=disable
	 * -->Stop bit= 1bit
	 * -->Wire mode=Full Duplex
	 */
	MUSART_INIT_t wifi = {0} ;
	wifi.MUSART_BAUDRATE = MUSART_BAUDRATE_115200_CLK_8M;
	wifi.MUSART_DATA_SIZE=MUSART_8BIT_DATA;
	wifi.MUSART_PARITY_MODE=MUSART_PARITY_DISABLE;
	wifi.MUSART_STOP_MODE=MUSART_STOPBIT1;
	wifi.MUSART_WIRE_MODE=MUSART_FULL_DUPLEX;

	/*UART INIT*/
	Local_xErrorStatus = MUSART_enInit(MUSART1, &wifi);

	/* stop ECHO */
	while(Local_xErrorStatus == FAILARE)
	{
		MUSART_enBusySendString(MUSART1,(u8*)"ATE0\r\n");
		MUSART_enBusyReceivestr(MUSART1, Local_charDataReceive1, 6);
		if((Local_charDataReceive1[0] == 'O') && (Local_charDataReceive1[1] == 'K'))
		{
			Local_xErrorStatus = SUCCESS;
			break;
		}
	}
	//MSTK_voidSetBusyWait(100);


	Local_xErrorStatus = FAILARE;

	/* Set station mode */
	while(Local_xErrorStatus == FAILARE)
	{
		MUSART_enBusySendString(MUSART1,(u8*)"AT+CWMODE=1\r\n");
		MUSART_enBusyReceivestr(MUSART1, Local_charDataReceive2, 6);
		if((Local_charDataReceive2[0] == 'O') && (Local_charDataReceive2[1] == 'K'))
		{
			Local_xErrorStatus = SUCCESS;
			break;
		}
	}
	//	MSTK_voidSetBusyWait(100);
	return Local_xErrorStatus;
}




ErrorState_t ESP_VoidConnectToWiFi(u8 *Copy_name , u8 *Copy_pass)
{
	ErrorState_t Local_xErrorStatus	=	FAILARE;
	u8 Local_charDataReceive[255] = {0};
	u8 Local_u8Counter = 0;

	/* connect to Wifi */
	while(Local_xErrorStatus ==	FAILARE)
	{
		MUSART_enBusySendString(MUSART1,(u8*)"AT+CWJAP_CUR=\"");
		MUSART_enBusySendString(MUSART1,(u8*)Copy_name);
		MUSART_enBusySendString(MUSART1,(u8*)"\",\"");
		MUSART_enBusySendString(MUSART1,(u8*)Copy_pass);
		MUSART_enBusySendString(MUSART1,(u8*)"\"\r\n");
		MUSART_enBusyReceivestr(MUSART1,Local_charDataReceive , 255);

		for(Local_u8Counter = 0; Local_u8Counter < 255; Local_u8Counter++)
		{
			if((Local_charDataReceive[Local_u8Counter] == 'O') && (Local_charDataReceive[Local_u8Counter+1] == 'K'))
			{
				Local_xErrorStatus	= SUCCESS;
				break;
			}
		}
		//MSTK_voidSetBusyWait(10);
	}
	return Local_xErrorStatus;

}


void ESP_VidConnectToSrvTcp (u8 *Copy_u8Domain , u8 *Copy_u8Port)
{
	u8  Local_charDataReceive[25] = {0};

	/* connect to server */
	MUSART_enBusySendString(MUSART1,(u8*)"AT+CIPSTART=\"TCP\",\"");
	MUSART_enBusySendString(MUSART1,(u8*)Copy_u8Domain);
	MUSART_enBusySendString(MUSART1,(u8*)"\",");
	MUSART_enBusySendString(MUSART1,(u8*)Copy_u8Port);
	MUSART_enBusySendString(MUSART1,(u8*)"\r\n");
	MUSART_enBusyReceivestr(MUSART1, Local_charDataReceive , 25);
}


ErrorState_t ESP_u8ReceiveHttpReq(u8 *Copy_u8ChannelID , u8 *Copy_u8Length, u8 *data)
{
	ErrorState_t Local_xErrorStatus = FAILARE;

	u8 Local_charDataReceive1[6] = {0};
	u8 Local_charDataReceive2[50] = {0};
	u8 Local_u8Counter = 0;

	while(Local_xErrorStatus == FAILARE)
	{
		MUSART_enBusySendString(MUSART1,(u8*)"AT+CIPSEND=");
		MUSART_enBusySendString(MUSART1,(u8*)Copy_u8Length);
		MUSART_enBusySendString(MUSART1,(u8*)"\r\n");
		MUSART_enBusyReceivestr(MUSART1, Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_xErrorStatus = SUCCESS;
				break;
			}
		}
		//		MSTK_voidSetBusyWait(10);
	}

	Local_xErrorStatus = FAILARE ;

	while(Local_xErrorStatus == FAILARE)
	{
		MUSART_enBusySendString(MUSART1,(u8*)Copy_u8ChannelID);
		MUSART_enBusyReceivestr(MUSART1, Local_charDataReceive2 , 50);

		for(Local_u8Counter = 0; Local_u8Counter < 50; Local_u8Counter++)
		{
			if((Local_charDataReceive2[Local_u8Counter] == '+') &&
					(Local_charDataReceive2[Local_u8Counter+1] == 'I') &&
					(Local_charDataReceive2[Local_u8Counter+2] == 'P')&&
					(Local_charDataReceive2[Local_u8Counter+3] == 'D') &&
					(Local_charDataReceive2[Local_u8Counter+4] == ',') &&
					(Local_charDataReceive2[Local_u8Counter+5] == '1') &&
					(Local_charDataReceive2[Local_u8Counter+6] == ':'))
			{
				*data = Local_charDataReceive2[Local_u8Counter+7];
				break;
			}
		}
		//		MSTK_voidSetBusyWait(500);
	}
	return Local_xErrorStatus;
}
