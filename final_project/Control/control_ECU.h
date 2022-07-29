/*
 * control_ECU.h
 *
 *  Created on: Nov 6, 2021
 *      Author: Ahmed
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

//#define F_CPU 8000000UL
#include "uart.h"
#include "gpio.h"
#include "lcd.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include"util/delay.h"
#include "twi.h"
#include"timer.h"
#include <avr/io.h>
#include <string.h>

#define HMI_READY 0x10
#define CONTROL_READY 0x11

#define ENTER_NEW_PASS   'n'
#define CONFIRM_PASS     'c'
#define NO_MATCH         'o'
#define PASS_SAVED       's'
#define ENTER_PASS       'P'
#define MAIN_MENU        'M'
#define WRONG_CHOICE     'W'
#define ENTER_OLD_PASS   'D'
#define YOU_HAVE_1_TRIES '1'
#define YOU_HAVE_2_TRIES '2'
#define LOCKING 	     'T'
#define OPEN_DOOR        'O'

void firstTimeMenu(void);
void sendByte(uint8 data);
uint8 receiveByte(void);
void receiveString( uint8 * a_string);
/*====================================*/
void mainMenu(void);
void askOldPass(uint8 message);
void openDoor();
boolean isCorrectPass();
void locking(void);
void freeStr(uint8 * str,uint8 str_size);
void eepromReadStr(uint8 * str);
void eepromWriteStr(uint8 * str);

#endif /* CONTROL_ECU_H_ */
