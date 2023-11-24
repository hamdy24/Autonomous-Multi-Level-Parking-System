/*
 * Stepper.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Abdallah
 */


#include "Stepper.h"


/**================================================================
 * @Fn					- Stepper_Init
 * @brief 				- Initializes pins used when working with stepper (direction pin)
 * @param [in] 			- None
 * @retval 				- None
 * Note					- None
 *
 */


void Stepper_Init(void)
{

	// Initialize the pin that will be used to determine direction of stepper motor

	GPIO_PinConfig_t Pincfg;

	Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	Pincfg.GPIO_PinNumber =	Dir_Pin;
	MCAL_GPIO_Init(Stepper_Port, &Pincfg);


}








/**================================================================
 * @Fn					- Stepper_Move_Steps
 * @brief 				- Moves stepper motor No. of steps
 * @param [in] 			- TIMERx: Which timer to work with
 * @param [in] 			- ChannelX: Which channel in this timer to work with
 * @param [in] 			- dutyCycle: Duty cycle for your signal as a value(meaning 50% is passed as 50)
 * @param [in] 			- frequency: Which frequency you want for your signal
 * @param [in] 			- clock_speed: Which clock_speed is provided for SYSCLK
 * @param [in] 			- direction: CW or CCW
 * @param [in] 			- steps: No. of steps to move with stepper motor
 * @retval 				- None
 * Note					- This function utilize the interrupts in the timer to count the number of steps to move using stepper
 * 						This function is mostly used with stepper motors
 *
 */


void Stepper_Move_Steps(TIMER_Typedef *TIMERx, Timer_Channel ChannelX, uint16_t steps,uint8_t dutyCycle, uint32_t frequency,CLOCK_SPEED Clock_Speed_MHz, Stepper_Direction direction)
{
	// Could be changed according to which direction the driver accepting
	if(direction == StepperCCW)
	{
		MCAL_GPIO_WritePin(Stepper_Port, Step_Pin, GPIO_PIN_HIGH);
	}else{
		MCAL_GPIO_WritePin(Stepper_Port, Step_Pin, GPIO_PIN_LOW);
	}


	PWM_Move_Steps(TIMERx, ChannelX, steps, dutyCycle, frequency, Clock_Speed_MHz);
}


