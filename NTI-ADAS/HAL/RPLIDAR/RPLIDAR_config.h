

#ifndef RPLIDAR_CONFIG_H_
#define RPLIDAR_CONFIG_H_

/* Macros for command (CMD) operations */
#define START_BIT				0xA5
#define CMD_STOP				0x25
#define CMD_RESET				0x40
#define CMD_SCAN				0x20
#define CMD_FORCE_SCAN			0x21
#define CMD_HQ_SCAN				0x83
#define CMD_GET_HEALTH			0x52
#define CMD_GET_SAMPLERATE		0x59
#define CMD_HQ_MOTOR_SPEED_CTR	0xA8
#define CMD_GET_INFO			0x50

/*Select UART number FROM UART0
 *                        UART1
 *                        UART2
 *                        UART3
						        */
#define RPLIDAR_UART    MUSART2



#endif
