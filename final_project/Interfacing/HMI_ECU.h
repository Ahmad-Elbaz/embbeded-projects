/*
 * HMI_ECU.h
 *
 *  Created on: Nov 6, 2021
 *      Author: Ahmed
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

//#define F_CPU 8000000UL

#include "uart.h"
#include "lcd.h"
#include "gpio.h"
#include "keypad.h"
#include"util/delay.h"
#include"timer.h"


#define HMI_READY 0x10
#define CONTROL_READY 0x11

#define ENTER_NEW_PASS   'n'
#define CONFIRM_PASS     'c'
#define NO_MATCH         'o'
#define PASS_SAVED       's'
#define MAIN_MENU        'M'
#define ENTER_PASS       'P'
#define WRONG_CHOICE     'W'
#define ENTER_OLD_PASS   'D'
#define YOU_HAVE_1_TRIES '1'
#define YOU_HAVE_2_TRIES '2'
#define LOCKING		      'T'
#define OPEN_DOOR         'O'
#define FREE              'd'


uint8 receiveByte(void);
void sendByte(uint8 a_data);
void sendString(const uint8 *str);
void enterPass(uint8 * a_lcdMessage,uint8 * a_returnPass);
void getPass(uint8 *const a_str);
/*=================================*/
void mainMenu(void);
void freeStr(uint8 * str,uint8 str_size);
void locking(void);

#endif /* HMI_ECU_H_ */
