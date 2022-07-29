/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc.c
 *
 * Description: source file for DC motor driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

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
