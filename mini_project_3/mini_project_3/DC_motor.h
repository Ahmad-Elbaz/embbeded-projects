/*
 * DC_motor.h
 *
 *  Created on: Oct 8, 2021
 *      Author: Ahmed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define MotorCW_port PORTB_ID
#define MotorCW_pin PIN0_ID

#define MotorA_CW_port PORTB_ID
#define MotorCCW_pin PIN1_ID


typedef enum {
	stop ,CW,CCW
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State ,uint8 );

#endif /* DC_MOTOR_H_ */

