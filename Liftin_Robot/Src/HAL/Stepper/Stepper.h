/*
 * Stepper.h
 *
 *  Created on: Dec 7, 2023
 *      Author: Abdallah
 */

#ifndef HAL_STEPPER_STEPPER_H_
#define HAL_STEPPER_STEPPER_H_

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"


#define StepperDir_Port		GPIOB

typedef enum
{
	Stepper_Down,
	Stepper_UP
}Stepper_Direction;

void Stepper_Init(GPIO_PinConfig_t* DirPin);
void Stepper_Move_Steps(TIMER_Typedef *TIMERx, Timer_Channel ChannelX, uint16_t steps,uint8_t dutyCycle, uint32_t frequency, Stepper_Direction Direction);
#endif /* HAL_STEPPER_STEPPER_H_ */
