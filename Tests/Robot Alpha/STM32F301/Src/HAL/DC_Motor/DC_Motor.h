/*
 * DC_Motor.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 26, 2023
 *	Brief		: This file contains all the
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_H_
#define HAL_DC_MOTOR_DC_MOTOR_H_
/************************************ Includes Start *************************************************/
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"

/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/


/************************************ Macros END  *************************************************/




/************************************ HelperEnums Declaration Start *************************************************/

/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ DataTypes Declaration Start *************************************************/

typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PortNumber;
	uint8_t GPIO_MODE;
	uint8_t GPIO_OUTPUT_SPEED;
}motor_PinConfig_t;

typedef struct{
	motor_PinConfig_t Dc_motor [2];
}Motor_t;


/************************************ DataTypes Declaration  END  *************************************************/




/************************************ Initialization Helper Start *************************************************/
void Motor_intialize(const Motor_t *Motor);
void Motor_TurnOff(const Motor_t *Motor);
void Motor_Move_ForWard(const Motor_t *Motor);
void Motor_Move_BackWard(const Motor_t *Motor);



/************************************ Initialization Helper END  *************************************************/


/************************************ Software Interfaces Start *************************************************/
/************************************ Software Interfaces END  *************************************************/



#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
