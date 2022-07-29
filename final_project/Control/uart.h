 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum {
	Asynchronous , Synchronous
}UART_mode;
typedef enum {
	disabled , reserved4 , even_parity, odd_parity
}UART_parityType;
typedef enum {
	defult = 9600
}UART_baudRate;
typedef enum {
	_1bit , _2bit
}UART_numberOfStopBits;
typedef enum {
	_5bit , _6bit , _7bit, _8bit , reserved1 , reserved2 , reserved3 , _9bit
}UART_numberOfBitsPerFrame;
typedef struct{
	UART_mode                  mode;
	UART_parityType            parityType;
	UART_baudRate               baudRate;
	UART_numberOfStopBits      numberOfStopBits;
	UART_numberOfBitsPerFrame  numberOfBitsPerFrame;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
