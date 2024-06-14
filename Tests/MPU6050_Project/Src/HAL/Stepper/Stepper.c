/*
 * Stepper.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Abdallah
 */


#include "Stepper.h"


static uint16_t Global_Stepper_Pin;

void Stepper_Init(GPIO_PinConfig_t* DirPin)
{
	GPIO_PinConfig_t StepperDir =
	{
			.GPIO_MODE = DirPin->GPIO_MODE,
			.GPIO_OUTPUT_SPEED = DirPin->GPIO_OUTPUT_SPEED,
			.GPIO_PinNumber = DirPin->GPIO_PinNumber
	};
	Global_Stepper_Pin = DirPin->GPIO_PinNumber;
	MCAL_GPIO_Init(StepperDir_Port, &StepperDir);

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_LOW);

}


void Stepper_Move_Steps(TIMER_Typedef *TIMERx, Timer_Channel ChannelX, uint16_t steps,uint8_t dutyCycle, uint32_t frequency, Stepper_Direction Direction)
{
	switch(Direction)
	{
	case Stepper_Down:
		MCAL_GPIO_WritePin(StepperDir_Port, Global_Stepper_Pin, GPIO_PIN_LOW);
		break;
	case Stepper_UP:
		MCAL_GPIO_WritePin(StepperDir_Port, Global_Stepper_Pin, GPIO_PIN_HIGH);
		break;
	}
	PWM_Move_Steps(TIMERx, ChannelX, steps, dutyCycle, frequency, RCC_CLK_8M);
}
