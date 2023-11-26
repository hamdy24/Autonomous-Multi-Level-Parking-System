/*
 * UltraSonic_Program.c
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 7, 2023
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

#include "UltraSonic_Private.h"


ES_t HC_SR04_Init(HC_SR04_Config_t* Copy_pArrUltrasonicConfigs) {

	GPIO_PinConfig_t Trigger = {
			.GPIO_PinNumber = Copy_pArrUltrasonicConfigs->triggerPin,
			.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL,
			.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ,
	};

	MCAL_GPIO_Init(GPIOA, &Trigger);

	GPIO_PinConfig_t Echo = {
			.GPIO_PinNumber = Copy_pArrUltrasonicConfigs->echoPin,
			.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL,
			.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ,
	};

	MCAL_GPIO_Init(GPIOA, &Echo);

	Private_pConfigs = Copy_pArrUltrasonicConfigs;

    return ES_OK;
}

void HC_SR04_Trigger() {
    // Send a 10us pulse on the trigger pin to initiate measurement
	MCAL_GPIO_WritePin(GPIOA, Private_pConfigs->triggerPin, GPIO_PIN_HIGH);
    Delay_us(10); // Delay for 10us
	MCAL_GPIO_WritePin(GPIOA, Private_pConfigs->triggerPin, GPIO_PIN_LOW);
}

ES_t HC_SR04_ReadDistance(uint32_t* distance_cm) {
    // Send trigger signal to start measurement
    HC_SR04_Trigger();

    uint8_t echoValue;
    // Wait for the rising edge of the echo signal
    do{
    	echoValue = MCAL_GPIO_ReadPin(Private_pConfigs->port,Private_pConfigs->echoPin);
    }
    while ( echoValue == GPIO_PIN_LOW);

    uint32_t startTime = Get_TIMER2_Counter();
//    STK_enuGetElapsedTimeUs(&startTime);

    // Wait for the falling edge of the echo signal
    do{
    	echoValue = MCAL_GPIO_ReadPin(Private_pConfigs->port,Private_pConfigs->echoPin);
    }
    while (echoValue == GPIO_PIN_HIGH);

    uint32_t endTime = Get_TIMER2_Counter();
//    STK_enuGetElapsedTimeUs(&endTime);

    // Calculate distance in centimeters
    uint32_t pulseDuration = endTime - startTime;
    *distance_cm = (pulseDuration * 0.0343) / 2; // Speed of sound is approximately 343 m/s

    return ES_OK;
}
