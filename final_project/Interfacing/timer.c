/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: source file for Timer driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"



void (*timer0_callback_ptr)(void) = NULL_PTR;
void (*timer1A_callback_ptr)(void)= NULL_PTR;
void (*timer1B_callback_ptr)(void)= NULL_PTR;
void (*timer2_callback_ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer0_Init_Normal_Mode(const Timer_config * Config_Ptr)
{
	TCNT0 = Config_Ptr->initialValue; //Set Timer initial value to 0
	TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0);
	TCCR0 = (TCCR0 & 0xf8) | (Config_Ptr->prescaler);
}
void Timer1_Init_Normal_Mode(const Timer_config * Config_Ptr){
	TCNT1 = Config_Ptr->initialValue; //Set Timer initial value to 0
	TIMSK |= (1<<TOIE1); // Enable Timer1 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR1A |= (1<<FOC1A) ;  //not PMW
	TCCR1A = (TCCR1A & 0xf8) | (Config_Ptr->prescaler);
}
void Timer2_Init_Normal_Mode(const Timer_config * Config_Ptr){
	TCNT2 = Config_Ptr->initialValue; //Set Timer initial value to 0
	TIMSK |= (1<<TOIE2); // Enable Timer0 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR2 = (1<<FOC2);
	TCCR2 = (TCCR2 & 0xf8) | (Config_Ptr->prescaler);
}

void Timer0_Init_Compare_Mode(const Timer_config * Config_Ptr){
	TCNT0 = Config_Ptr->initialValue;    // Set Timer initial value to 0
	OCR0  = Config_Ptr->compareValue; // Set Compare Value
	TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01);
	TCCR0 = (TCCR0 & 0xf8)| (Config_Ptr->prescaler);
}
void Timer1A_Init_Compare_Mode(const Timer_config * Config_Ptr){
	TCNT1 =Config_Ptr->initialValue;
	OCR1A = Config_Ptr->compareValue;            //capture value
	TIMSK |= (1<<OCIE1A);    //INT enable
	TCCR1B |= (1<<WGM12); // Compare mode
	TCCR1B = (TCCR1B & 0xf8)| (Config_Ptr->prescaler);
	TCCR1A|=(1<<FOC1A) ;  //not PMW
}
void Timer2_Init_Compare_Mode(const Timer_config * Config_Ptr){
	TCNT2 = Config_Ptr->initialValue;    // Set Timer initial value to 0
	OCR2  = Config_Ptr->compareValue; // Set Compare Value
	TIMSK |= (1<<OCIE2); // Enable Timer0 Compare Interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR2 = (1<<FOC2) | (1<<WGM21);
	TCCR2 = (TCCR2 & 0xf8)| (Config_Ptr->prescaler);
}

ISR(TIMER0_OVF_vect)
{
	(*timer0_callback_ptr)();
}
ISR(TIMER1_OVF_vect)
{
	timer1A_callback_ptr();
}
ISR(TIMER2_OVF_vect)
{
	timer2_callback_ptr();
}
ISR(TIMER0_COMP_vect)
{
	timer0_callback_ptr();
}
ISR(TIMER1_COMPA_vect)
{
	timer1A_callback_ptr();
}
ISR(TIMER1_COMPB_vect)
{
	(*timer1B_callback_ptr)();
}
ISR(TIMER2_COMP_vect)
{
	timer2_callback_ptr();
}
/*******************************************************************************
 *                 Set Callback Functions Definitions                          *
 *******************************************************************************/
void Timer0_setCallPack(void (*ptr)(void)){
	timer0_callback_ptr = ptr;
}
void Timer1_OVF_setCallPack(void (*ptr)(void)){
	timer1A_callback_ptr = ptr;
}
void Timer1_A_setCallPack(void (*ptr)(void)){
	timer1A_callback_ptr = ptr;
}
void Timer1_B_setCallPack(void (*ptr)(void)){
	timer1B_callback_ptr = ptr;
}
void Timer2_setCallPack(void (*ptr)(void)){
	timer2_callback_ptr = ptr;
}


void Timer1_delay_sec() /* count 1 sec*/
{
	TCNT1 =0 ;
	OCR1A = 7812 ;            //capture value
	TCCR1B |= (1<<WGM12); // Compare mode
	TCCR1B = (TCCR1B & 0xf8)| (clock1024);
	TCCR1A|=(1<<FOC1A) ;  //not PMW
	while(!(TIFR & (1<<OCF1A))); // Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)
	TCCR1B = 0;
	TIFR |= (1<<OCF1A); // Clear TOV0 bit by set its value

}
void Timer1_delay_10msec() /* count 10 msec*/
{
	TCNT1 =0 ;
	OCR1A = 312 ;            //capture value
	TCCR1B |= (1<<WGM12); // Compare mode
	TCCR1B = (TCCR1B & 0xf8)| (clock256);
	TCCR1A|=(1<<FOC1A) ;  //not PMW
	while(!(TIFR & (1<<OCF1A))); // Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)
	TCCR1B = 0;
	TIFR |= (1<<OCF1A); // Clear TOV0 bit by set its value

}


void Timer0_Deinit_Mode(){
	TCCR0 = 0;
}
void Timer1_Deinit_Mode(){
	TCCR1B=0;
	TCCR1A=0;
}
void Timer2_Deinit_Mode(){
	TCCR2 = 0;
}


