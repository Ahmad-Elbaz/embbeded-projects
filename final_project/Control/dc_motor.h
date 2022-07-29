/******************************************************************************
 *
 * Module:  DC Motor
 *
 * File Name: DC.h
 *
 * Description: header file for DC motor driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/

#ifndef dc_MOTOR_H_
#define dc_MOTOR_H_
#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MotorCW_port PORTB_ID
#define MotorCW_pin PIN0_ID

#define MotorA_CW_port PORTB_ID
#define MotorCCW_pin PIN1_ID

typedef enum {
	stop ,CW,CCW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State ,uint8 speed );

#endif /* dc_MOTOR_H_ */

