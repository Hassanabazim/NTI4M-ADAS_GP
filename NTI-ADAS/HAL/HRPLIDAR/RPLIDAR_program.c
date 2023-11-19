
#include "STD_TYPES.h"
#include "MGPIO_int.h"
#include "MRCC_int.h"
#include "MSYSTICK_int.h"
#include "MUSART_int.h"
#include "RPLIDAR_interface.h"
#include "RPLIDAR_config.h"
#include "RPLIDAR_private.h"


         /*      Initialization Parameters     */
float Copy_floatAngle=0,Copy_floatDistance=0;
Check_error_t flag_s=OK;

/*                      ***GET_HEALTH***
 * --> This command is a single request and a single response
 * --> It has 7 bytes for the request descriptor and 3 bytes for the data response
 * */

static Check_error_t RPLIDAR_Check_error_tGetHealth(void)
{
	Check_error_t Copy_Check_error_tCheckValue=OK;
	u8 Copy_uint8ARRGetHealtCheck[10];
	u8 i=0,Copy_uint8Flag=0;
	MUSART_enBusySendByte(RPLIDAR_UART,START_BIT);
	MUSART_enBusySendByte(RPLIDAR_UART,CMD_GET_HEALTH);
	for(i=0;i<10;i++)
	{
		Copy_uint8ARRGetHealtCheck[i]=MUSART_enBusyReceiveByte(RPLIDAR_UART);
		if(Copy_uint8ARRGetHealtCheck[i]!=Copy_uint8ARRGetHealt[i])
		{
			Copy_uint8Flag=1;
		}
	}
	if(Copy_uint8Flag==1)
	{
		MUSART_enBusySendByte(RPLIDAR_UART,START_BIT);
		MUSART_enBusySendByte(RPLIDAR_UART,CMD_RESET);
		MSYSTICK_enDelayMS(2);
		Copy_Check_error_tCheckValue= NOK;
	}
	return Copy_Check_error_tCheckValue;
}
/*                ***Start Scan***
 * -->This command is a single request and a multiple response
 * -->This function checks the response descriptor for a scan request
 *     and returns whether this response descriptor is true or not
 * */
static Check_error_t RPLIDAR_GetDescriptor(void)
{
	u8 Copy_uint8DescriptorCheck[7];
	u8 i;
	Check_error_t Copy_Check_error_tCheckValue=OK;
	MUSART_enBusySendByte(RPLIDAR_UART,START_BIT);
	MUSART_enBusySendByte(RPLIDAR_UART,CMD_SCAN);
	for(i=0;i<7;i++)
	{
		Copy_uint8DescriptorCheck[i]=MUSART_enBusyReceiveByte(RPLIDAR_UART);
	}
	for(i=0;i<7;i++)
	{
		if(Copy_uint8DescriptorCheck[i]!=Copy_uint8ARRScanResponse[i])
		{
			Copy_Check_error_tCheckValue=NOK;
			break;
		}
	}
	return Copy_Check_error_tCheckValue;
	
}

/*             ***Start Scan***
 * -->This function gets the status of the response descriptor, which is true or false
 * */
Check_error_t RPLIDAR_DescriptorCheck(void)
{
	Check_error_t Copy_u8CheckStatus;
	Copy_u8CheckStatus=RPLIDAR_Check_error_tGetHealth();
	while(Copy_u8CheckStatus!=OK)
	{
		Copy_u8CheckStatus=RPLIDAR_Check_error_tGetHealth();
	}
	flag_s=RPLIDAR_GetDescriptor();
	MSYSTICK_enDelayMS(1000);
	MGPIO_enSetPinValue(PORTB, PIN10,LOW);
	MSYSTICK_enDelayMS(1000);
	if(flag_s==OK)
	{
		MGPIO_enSetPinValue(PORTB, PIN10,HIGH);
	}
	return flag_s;
}

/*               ***Start Scan***
 * -->In this function, you must determine the angle you want, and it will return the distance for you
 * */
void RPLIDAR_voidScanResponse(float angle1, float angle2)
{
	u8 Copy_uint8Quality=0,Copy_uint8AngleH=0,Copy_uint8AngleL=0,Copy_uint8DistanceH=0,Copy_uint8DistanceL=0;
	if(flag_s==OK)
	{
		while(1)
		{
			Copy_uint8Quality=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			while(Copy_uint8Quality!=0X3E)
			{
				Copy_uint8Quality=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			}
			Copy_uint8AngleL=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			Copy_uint8AngleH=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			Copy_uint8DistanceL=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			Copy_uint8DistanceH=MUSART_enBusyReceiveByte(RPLIDAR_UART);
			if((Copy_uint8Quality== 0x3E && (Copy_uint8DistanceL!=0x00 && Copy_uint8DistanceH!=0x00)))
			{
				if((Copy_uint8Quality== 0x3E) && ((Copy_uint8DistanceH!=0x3E)|| (Copy_uint8DistanceL!=0x3E) || (Copy_uint8AngleH!=0x3E) || (Copy_uint8AngleL!=0x3E)))
				{
					Copy_floatAngle=(float)((((u16)Copy_uint8AngleH<<7)|(Copy_uint8AngleL>>1))/64.0);
					Copy_floatDistance=(float)((((u16)Copy_uint8DistanceH<<8)|(Copy_uint8DistanceL))/4.0);
					if(angle1 >= 0 && angle2<=45)
					{
						if((Copy_floatAngle >= angle1 && Copy_floatAngle <= angle2) || (Copy_floatAngle >= 315.0 && Copy_floatAngle < 360.0))
						{
							//DIO_WritePin(PINA0,HIGH);
							break;
						}
					}
					if((Copy_floatAngle >= angle1 && Copy_floatAngle <= angle2))
					{
						break;
					}
				}
			}
			
		}
		
	}
}
/*    RPLIDAR Initialization
 * */
void RPLIDAR_voidINT(void)
{
	/* Enable UART2*/
	MRCC_enEnablePeripheralCLK(MRCC_USART2);
	/*Set Pin Direction for LED*/
	MGPIO_enSetPinDirection(PORTB, PIN10,OUT_2MHZ_PUSH_PULL);
	/*Set Pin Direction for UART2*/
	MGPIO_enSetPinDirection(MUSART2_TX_PIN,OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(MUSART2_RX_PIN,IN_FLOATING);
	/*      Configuration for  UART
	 * -->Baud rate =115200
	 * -->Data size=8 bit
	 * -->Parity mode=disable
	 * -->Stop bit= 1bit
	 * -->Wire mode=Full Duplex
	 */
	MUSART_INIT_t lidar ;
	lidar.MUSART_BAUDRATE = MUSART_BAUDRATE_115200_CLK_8M;
	lidar.MUSART_DATA_SIZE=MUSART_8BIT_DATA;
	lidar.MUSART_PARITY_MODE=MUSART_PARITY_DISABLE;
	lidar.MUSART_STOP_MODE=MUSART_STOPBIT1;
	lidar.MUSART_WIRE_MODE=MUSART_FULL_DUPLEX;
	/*UART INIT*/
	MUSART_enInit(MUSART2, &lidar);
}
/*            ***Check Function***
 * */

/*The aim of the function getter is to return a global variable
 * return the distance value by mm
 * */

float RPLIDAR_GetDistanceValue(float angle1, float angle2)
{
	RPLIDAR_voidScanResponse(angle1,angle2);
	return Copy_floatDistance;
}



