 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID          PORTB_ID

#define BUZZER_PIN_ID           PIN7_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Setup the direction of the required pin output.
 * Set initial value = LOGIC LOW
 */
void Buzzer_Init();
/*
 * Description :
 * Set pin value = LOGIC HIGH
 */
void Buzzer_On();
/*
 * Description :
 * Set pin value = LOGIC LOW
 */
void Buzzer_Off();


#endif /* BUZZER_H_ */
