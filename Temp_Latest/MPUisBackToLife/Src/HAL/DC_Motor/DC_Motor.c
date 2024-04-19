/*
 * DC_Motor.c
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 26, 2023
 *	Brief		: This file contains all the
 */


/************************************ Includes Start *************************************************/
/************************************ Includes END  *************************************************/


/********************************************************************/
/*	Description:	This Function sets  		*/
/*	Parameters:							                       		*/
/*		@param1: 						               		*/
/*		&param2:			       		*/
/*	Return:			Returns Error State 	                       	*/
/*	Notes:			None  	*/
/********************************************************************/



#include "../includes/DC_Motor.h"


void  Motor_intialize(Motor_Config_t *Motor){
	GPIO_PinConfig_t Motor_IN1={
			.GPIO_MODE=GPIO_MODE_OUTPUT_PUSHPULL,
			.GPIO_PinNumber=Motor->DC_Pin1Number,
			.GPIO_OUTPUT_SPEED=GPIO_SPEED_2MHZ
	};
	MCAL_GPIO_Init(Motor->DC_PortNumber1, &Motor_IN1);

	GPIO_PinConfig_t Motor_IN2={
			.GPIO_MODE=GPIO_MODE_OUTPUT_PUSHPULL,
			.GPIO_PinNumber=Motor->DC_Pin2Number,
			.GPIO_OUTPUT_SPEED=GPIO_SPEED_2MHZ
	};
	MCAL_GPIO_Init(Motor->DC_PortNumber2, &Motor_IN2);

}





void Motor_TurnOff(Motor_Config_t *Motor){
	MCAL_GPIO_WritePin(Motor->DC_PortNumber1, Motor->DC_Pin1Number, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(Motor->DC_PortNumber2, Motor->DC_Pin2Number, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_LOW);

	TIMER3_Stop();
}




void Motor_Move_ForWard(Motor_Config_t *Motor, uint8_t speed){
	PWM(Motor->PWM_Timer, Motor->PWM_Channel, speed, 1000, RCC_CLK_36M);

	MCAL_GPIO_WritePin(Motor->DC_PortNumber1, Motor->DC_Pin1Number,GPIO_PIN_HIGH);
	MCAL_GPIO_WritePin(Motor->DC_PortNumber2, Motor->DC_Pin2Number,GPIO_PIN_LOW);

}






void Motor_Move_BackWard(Motor_Config_t *Motor, uint8_t speed){
	PWM(Motor->PWM_Timer, Motor->PWM_Channel, speed, 1000, RCC_CLK_36M);
	MCAL_GPIO_WritePin(Motor->DC_PortNumber1, Motor->DC_Pin1Number,GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(Motor->DC_PortNumber2, Motor->DC_Pin2Number,GPIO_PIN_HIGH);
}


