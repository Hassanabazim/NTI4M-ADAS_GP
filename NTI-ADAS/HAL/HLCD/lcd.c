/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MGPIO_int.h"
#include "MSYSTICK_int.h"
#include "lcd_cfg.h"
#include "lcd.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u8 customChar[NO_CSTOM_CHAR][NO_CSTOM_CHAR_BYTES]=
{
	{0x0A,0x1F,0x1F,0x1F,0x1F,0x0E,0x04,0x00},	/* Heart symbol	 */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},	/* Empty battery */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},	/*	20% battery  */
	{0x04,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},  /*	40% battery  */
	{0x04,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},	/*	60% battery  */
	{0x04,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	80% battery  */
	{0x04,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	100% battery */
	{0x00,0x00,0x01,0x01,0x05,0x05,0x15,0x15},	/*	Mobile Signal*/
};
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
//extern u8 customChar[NO_CSTOM_CHAR][NO_CSTOM_CHAR_BYTES];
static void enablePulse(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void enablePulse(void)        
* \Description     : send enable pulse to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                        
* \Return value:   : None                                 
*******************************************************************************/

static void enablePulse(void)
{
	MGPIO_enSetPinValue(LCD_EN_PORT, LCD_EN_CHANNEL, HIGH);
	MSYSTICK_enDelayMS(1);
	MGPIO_enSetPinValue(LCD_EN_PORT, LCD_EN_CHANNEL, LOW);
	MSYSTICK_enDelayMS(30);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void lcd_init(void)        
* \Description     : initialize LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                        
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidInit(void)
{
	MGPIO_enSetPinDirection(LCD_RS_PORT, LCD_RS_CHANNEL, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(LCD_EN_PORT, LCD_EN_CHANNEL, OUT_2MHZ_PUSH_PULL);

	MGPIO_enSetPinDirection(LCD_D4_PORT, LCD_D4_CHANNEL, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(LCD_D5_PORT, LCD_D5_CHANNEL, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(LCD_D6_PORT, LCD_D6_CHANNEL, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(LCD_D7_PORT, LCD_D7_CHANNEL, OUT_2MHZ_PUSH_PULL);

	MSYSTICK_enDelayMS(30);

	lcd_vidSendCmd(0x03);
	MSYSTICK_enDelayMS(5);
	lcd_vidSendCmd(0x03);
	MSYSTICK_enSetBusyWait(100);
	lcd_vidSendCmd(0x03);
	lcd_vidSendCmd(0x02);

	lcd_vidSendCmd(_LCD_4BIT_MODE);
	lcd_vidSendCmd(_LCD_CURSOR_OFF);
	lcd_vidCustomWrite();
	lcd_vidClrDislay();
	lcd_vidGotoRowColumn(0, 0);
}

/******************************************************************************
* \Syntax          : void lcd_vidSendCmd(lcd_Cmd_Type cmd)        
* \Description     : send command to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : cmd	-> LCD command ID                                                                        
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidSendCmd(lcd_cmd_t cmd)
{
	/*	RS -> Command Mode	*/
	MSYSTICK_enDelayMS(1);
	MGPIO_enSetPinValue(LCD_RS_PORT,LCD_RS_CHANNEL,LOW);

	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D4_CHANNEL,GET_BIT(cmd,4));
	MGPIO_enSetPinValue(LCD_D5_PORT,LCD_D5_CHANNEL,GET_BIT(cmd,5));
	MGPIO_enSetPinValue(LCD_D6_PORT,LCD_D6_CHANNEL,GET_BIT(cmd,6));
	MGPIO_enSetPinValue(LCD_D7_PORT,LCD_D7_CHANNEL,GET_BIT(cmd,7));
	
	enablePulse();
	
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D4_CHANNEL,GET_BIT(cmd,0));
	MGPIO_enSetPinValue(LCD_D5_PORT,LCD_D5_CHANNEL,GET_BIT(cmd,1));
	MGPIO_enSetPinValue(LCD_D6_PORT,LCD_D6_CHANNEL,GET_BIT(cmd,2));
	MGPIO_enSetPinValue(LCD_D7_PORT,LCD_D7_CHANNEL,GET_BIT(cmd,3));
	
	enablePulse();
}

/******************************************************************************
* \Syntax          : void lcd_vidSendData(u8 data)        
* \Description     : send data to LCD HW                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : data	-> LCD data input                                                                       
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidSendData(u8 data)
{
	/*	RS -> Data Mode	*/
	MGPIO_enSetPinValue(LCD_RS_PORT,LCD_RS_CHANNEL,HIGH);

	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D4_CHANNEL,GET_BIT(data,4));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D5_CHANNEL,GET_BIT(data,5));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D6_CHANNEL,GET_BIT(data,6));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D7_CHANNEL,GET_BIT(data,7));
	
	enablePulse();
	
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D4_CHANNEL,GET_BIT(data,0));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D5_CHANNEL,GET_BIT(data,1));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D6_CHANNEL,GET_BIT(data,2));
	MGPIO_enSetPinValue(LCD_D4_PORT,LCD_D7_CHANNEL,GET_BIT(data,3));
	
	enablePulse();
	
}

/******************************************************************************
* \Syntax          : void lcd_vidGotoRowColumn(u8 row, u8 column)        
* \Description     : set LCD DDRAM pointer                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : row	-> LCD row ID
					 column -> LCD column ID															
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidGotoRowColumn(u8 row, u8 column)
{
	switch (row)
	{
	case 0:
		/*	Row 0	*/
		lcd_vidSendCmd(0x80+column);
		break;
	case 1:
		/* Row 1 */
		lcd_vidSendCmd(0xC0+column);
		break;
	case 2:
	/* Row 1 */
	lcd_vidSendCmd(0x94+column);
	break;
	
	case 3:
	/* Row 1 */
	lcd_vidSendCmd(0xD4+column);
	break;	
		
	}	
}

/******************************************************************************
* \Syntax          : void lcd_vidDisplyChar(u8 chr)       
* \Description     : sent character to be displayed                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : chr	-> ASCI value of character															
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidDisplyChar(u8 chr)
{
	lcd_vidSendData(chr);
}

/******************************************************************************
* \Syntax          : void lcd_vidDisplyStr(u8* str)       
* \Description     : display string on LCD                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : str	-> string to be displayed														
* \Return value:   : None                                 
*******************************************************************************/
void lcd_vidDisplyStr(u8* str)
{
	while (*str != '\0')
	{
		lcd_vidDisplyChar(*str);
		str++;
	}
}

/******************************************************************************
* \Syntax          : void lcd_vidCustomWrite(void)
* \Description     : load LCD CGRAM with configured custom characters
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Return value:   : None
*******************************************************************************/
void lcd_vidCustomWrite(void)
{
	u8 loc_ByteIndex=0;
	u8 loc_CharIndx=0;
	
	for (loc_CharIndx=0;loc_CharIndx<NO_CSTOM_CHAR;loc_CharIndx++)
	{
		lcd_vidSendCmd(_LCD_CGRAM_START_ADDRESS +(loc_CharIndx*8));
		for (loc_ByteIndex =0; loc_ByteIndex<NO_CSTOM_CHAR_BYTES;loc_ByteIndex++)
		{
			lcd_vidDisplyChar(customChar[loc_CharIndx][loc_ByteIndex]);
		}
	}	
}

void lcd_vidDisplayNum(s32 copy_s32Num)
{
	u8 temp_arr[10] = {0} ;
	u8 counter = 0 ;

	if (copy_s32Num == 0 )
	{
		lcd_vidSendData('0');
	}
	else
	{
		if (copy_s32Num < 0)
		{
			lcd_vidSendData('-');
			copy_s32Num *= -1 ;
		}
		while (copy_s32Num > 0)
		{
			temp_arr[counter] = copy_s32Num % 10;
			copy_s32Num = copy_s32Num / 10;
			counter ++;
		}

		while (counter > 0)
		{
			lcd_vidSendData(temp_arr[counter-1] + '0');
			counter --;
		}
	}
}

/******************************************************************************
* \Syntax          : void lcd_vidClrDislay(void);
* \Description     : clear display
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Return value:   : None
*******************************************************************************/
void lcd_vidClrDislay(void)
{
	lcd_vidSendCmd(_LCD_CLEAR);
	MSYSTICK_enDelayMS(5);
}
/**********************************************************************************************************************
 *  END OF FILE: lcd.c
 *********************************************************************************************************************/
