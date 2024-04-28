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
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"







/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/


/************************************ Macros END  *************************************************/




/************************************ HelperEnums Declaration Start *************************************************/

/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ DataTypes Declaration Start *************************************************/

typedef struct{
	uint16_t DC_Pin1Number;
	uint16_t DC_Pin2Number;
	GPIO_TypeDef* DC_PortNumber1;
	GPIO_TypeDef* DC_PortNumber2;
	TIMER_Typedef* PWM_Timer;
	Timer_Channel PWM_Channel;
}Motor_Config_t;




/************************************ DataTypes Declaration  END  *************************************************/




/************************************ Initialization Helper Start *************************************************/
void Motor_intialize(Motor_Config_t *Motor);
void Motor_TurnOff(Motor_Config_t *Motor);
void Motor_Move_ForWard(Motor_Config_t *Motor, uint8_t speed);
void Motor_Move_BackWard(Motor_Config_t *Motor, uint8_t speed);
void Motor_Move_Left(Motor_Config_t *Motor1, Motor_Config_t *Motor2);
void Motor_Move_Right(Motor_Config_t *Motor1, Motor_Config_t *Motor2);



/************************************ Initialization Helper END  *************************************************/


/************************************ Software Interfaces Start *************************************************/
/************************************ Software Interfaces END  *************************************************/



#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
