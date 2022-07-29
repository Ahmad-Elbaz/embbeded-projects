 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for buzzer driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/
#include"buzzer.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Setup the direction of the required pin output.
 * Set initial value = 0
 */

void Buzzer_Init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW); /*set initial value = 0*/
}

/*
 * Description :
 * Set pin value = 1
 */
void Buzzer_On()
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * Set pin value = 0
 */
void Buzzer_Off()
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);

}
