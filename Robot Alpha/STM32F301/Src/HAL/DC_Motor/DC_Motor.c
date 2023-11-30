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



#include "DC_Motor.h"


void  Motor_intialize(const Motor_t *Motor){
	GPIO_PinConfig_t Motor_pin1={
		.GPIO_PortNumber=Motor->Dc_motor[0].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[0].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[0].GPIO_OUTPUT_SPEED

	};
	GPIO_PinConfig_t Motor_pin2={
		.GPIO_PortNumber=Motor->Dc_motor[1].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[1].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[1].GPIO_OUTPUT_SPEED

	};
	   MCAL_GPIO_Init(&(Motor->Dc_motor[0].GPIO_PortNumber), &Motor_1);
		MCAL_GPIO_Init(&(Motor->Dc_motor[1].GPIO_PortNumber), &Motor_2);
}

void Motor_TurnOff(const Motor_t *Motor){
	GPIO_PinConfig_t Motor_pin1={
		.GPIO_PortNumber=Motor->Dc_motor[0].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[0].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[0].GPIO_OUTPUT_SPEED

	};
	GPIO_PinConfig_t Motor_pin2={
		.GPIO_PortNumber=Motor->Dc_motor[1].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[1].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[1].GPIO_OUTPUT_SPEED

	};
		MCAL_GPIO_WritePin(&(Motor->Dc_motor[0].GPIO_PortNumber),Motor->Dc_motor[0].GPIO_PinNumber,GPIO_PIN_LOW);
		MCAL_GPIO_WritePin(&(Motor->Dc_motor[1].GPIO_PortNumber),Motor->Dc_motor[1].GPIO_PinNumber,GPIO_PIN_LOW);


}




void Motor_Move_ForWard(const Motor_t *Motor){

	GPIO_PinConfig_t Motor_pin1={
		.GPIO_PortNumber=Motor->Dc_motor[0].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[0].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[0].GPIO_OUTPUT_SPEED

	};
	GPIO_PinConfig_t Motor_pin2={
		.GPIO_PortNumber=Motor->Dc_motor[1].GPIO_PortNumber,
		.GPIO_PinNumber=Motor->Dc_motor[1].GPIO_PinNumber,
		.GPIO_OUTPUT_SPEED=Motor->Dc_motor[1].GPIO_OUTPUT_SPEED

	};
	MCAL_GPIO_WritePin(&(Motor->Dc_motor[0].GPIO_PortNumber),Motor->Dc_motor[0].GPIO_PinNumber,GPIO_PIN_HIGH);
	MCAL_GPIO_WritePin(&(Motor->Dc_motor[1].GPIO_PortNumber),Motor->Dc_motor[1].GPIO_PinNumber,GPIO_PIN_LOW);

}




void Motor_Move_BackWard(const Motor_t *Motor){

	GPIO_PinConfig_t Motor_pin1={
			.GPIO_PortNumber=Motor->Dc_motor[0].GPIO_PortNumber,
			.GPIO_PinNumber=Motor->Dc_motor[0].GPIO_PinNumber,
			.GPIO_OUTPUT_SPEED=Motor->Dc_motor[0].GPIO_OUTPUT_SPEED

		};
		GPIO_PinConfig_t Motor_pin2={
			.GPIO_PortNumber=Motor->Dc_motor[1].GPIO_PortNumber,
			.GPIO_PinNumber=Motor->Dc_motor[1].GPIO_PinNumber,
			.GPIO_OUTPUT_SPEED=Motor->Dc_motor[1].GPIO_OUTPUT_SPEED

		};
	MCAL_GPIO_WritePin(&(Motor->Dc_motor[0].GPIO_PortNumber),Motor->Dc_motor[0].GPIO_PinNumber,GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(&(Motor->Dc_motor[1].GPIO_PortNumber),Motor->Dc_motor[1].GPIO_PinNumber,GPIO_PIN_HIGH);

}


