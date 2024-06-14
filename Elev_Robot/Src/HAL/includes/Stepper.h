/*
 * Stepper.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Abdallah
 */

#ifndef INCLUDES_STEPPER_H_
#define INCLUDES_STEPPER_H_

#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_TIMER_driver.h"

#define Stepper_Port	GPIOA

#define Step_Pin	GPIO_PIN_8
#define Dir_Pin		GPIO_PIN_9

#define Steps_Per_Revolution	200   // 360 / 1.8(step angle)  // From datasheet of NEMA17


//typedef enum{
//	Stepper_CCW,
//	Stepper_CW
//}Stepper_Dir;

typedef enum{
	Stepper_Half_Speed,
	Stepper_Full_Speed
}Stepper_Speed;

void Stepper_Init(void);

// void Stepper_Move(int rotations_number, Stepper_Dir dir, Stepper_Speed speed);


void Stepper_Move_Steps(TIMER_Typedef *TIMERx, Timer_Channel ChannelX, uint16_t steps,uint8_t dutyCycle, uint32_t frequency,CLOCK_SPEED Clock_Speed_MHz, Stepper_Direction direction);


#endif /* INCLUDES_STEPPER_H_ */
