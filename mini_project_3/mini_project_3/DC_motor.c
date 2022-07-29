/*
 * DC_motor.c
 *
 *  Created on: Oct 8, 2021
 *      Author: Ahmed
 */

#include "gpio.h"
#include "DC_motor.h"
#include "PWM.h"

/*
#define MotorCW_port PORTC_ID
#define MotorCW_pin PIN0

#define MotorA_CW_port PORTC_ID
#define MotorCCW_pin PIN0*/
void DcMotor_Init(void){
	GPIO_setupPinDirection(MotorCW_port,MotorCW_pin,PIN_OUTPUT);
	GPIO_setupPinDirection(MotorA_CW_port,MotorCCW_pin,PIN_OUTPUT);
	GPIO_writePin(MotorCW_port,MotorCW_pin,LOGIC_LOW);
	GPIO_writePin(MotorA_CW_port,MotorCCW_pin,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	switch(state){
	case stop:
		GPIO_writePin(MotorCW_port,MotorCW_pin,LOGIC_HIGH);
		GPIO_writePin(MotorA_CW_port,MotorCCW_pin,LOGIC_HIGH);
		break;
	case CW:
		GPIO_writePin(MotorCW_port,MotorCW_pin,LOGIC_HIGH);
		GPIO_writePin(MotorA_CW_port,MotorCCW_pin,LOGIC_LOW);
		break;
	case CCW:
		GPIO_writePin(MotorCW_port,MotorCW_pin,LOGIC_LOW);
		GPIO_writePin(MotorA_CW_port,MotorCCW_pin,LOGIC_HIGH);
		break;

	 PWM_Timer0_Init(speed);


	}
}
