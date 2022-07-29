/******************************************************************************
 *
 * Module:  TIMER
 *
 * File Name: timer.h
 *
 * Description: header file for Timer driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum {
	overflow, compare = 2
}Timer_mode;
typedef enum {
	timer0_id,timer1_id,timer2_id
}Timer_ID;
typedef enum{
	no_clock,no_prescaler,clock8,clock64,clock256,clock1024,ex_falling,ex_rising
}Timer_prescaler;
typedef struct {
	Timer_mode mode;
	Timer_ID id;
	Timer_prescaler prescaler;
	uint16 compareValue;
	uint16 initialValue;
}Timer_config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer0_Init_Normal_Mode(const Timer_config * Config_Ptr);
void Timer1_Init_Normal_Mode(const Timer_config * Config_Ptr);
void Timer2_Init_Normal_Mode(const Timer_config * Config_Ptr);
void Timer0_Init_Compare_Mode(const Timer_config * Config_Ptr);
void Timer1_Init_Compare_Mode(const Timer_config * Config_Ptr);
void Timer2_Init_Compare_Mode(const Timer_config * Config_Ptr);


void Timer0_setCallPack(void (*ptr)(void));
void Timer1_A_setCallPack(void (*ptr)(void));
void Timer1_B_setCallPack(void (*ptr)(void));
void Timer1_OVF_setCallPack(void (*ptr)(void));
void Timer2_setCallPack(void (*ptr)(void));
void Timer1_delay_sec();
void Timer1_delay_10msec();
void Timer0_Deinit_Mode();
void Timer1_Deinit_Mode();
void Timer2_Deinit_Mode();

#endif /* TIMER_H_ */
