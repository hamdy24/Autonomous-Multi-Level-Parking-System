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
	TIMER1_Init(RCC_CLK_8M);

	uint8_t Local_Iterator = 0;
	for(Local_Iterator = 0;Local_Iterator<HC_Num;Local_Iterator++){

		GPIO_PinConfig_t Trigger = {
				.GPIO_PinNumber = Copy_pArrUltrasonicConfigs[Local_Iterator].triggerPin,
				.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL,
				.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ,
		};

		MCAL_GPIO_Init(Copy_pArrUltrasonicConfigs[Local_Iterator].trigPort, &Trigger);

		GPIO_PinConfig_t Echo = {
				.GPIO_PinNumber = Copy_pArrUltrasonicConfigs[Local_Iterator].echoPin,
				.GPIO_MODE = GPIO_MODE_INPUT_FLOATING,
		};

		MCAL_GPIO_Init(Copy_pArrUltrasonicConfigs[Local_Iterator].echoPort, &Echo);
	}


	Private_pConfigs = Copy_pArrUltrasonicConfigs;

    return ES_OK;
}

void HC_SR04_Trigger(uint8_t Sensor_Num) {
    // Send a 10us pulse on the trigger pin to initiate measurement
	MCAL_GPIO_WritePin(GPIOA, Private_pConfigs[Sensor_Num].triggerPin, GPIO_PIN_HIGH);
    Delay_Timer1_ms(10); // Delay for 10us
	MCAL_GPIO_WritePin(GPIOA, Private_pConfigs[Sensor_Num].triggerPin, GPIO_PIN_LOW);
}

ES_t HC_SR04_ReadDistance(uint8_t Sensor_Num,uint32_t* distance_cm) {
    // Send trigger signal to start measurement
    HC_SR04_Trigger(Sensor_Num);

    uint8_t echoValue;
    // Wait for the rising edge of the echo signal
    do{
    	echoValue = MCAL_GPIO_ReadPin(Private_pConfigs[Sensor_Num].echoPort,Private_pConfigs[Sensor_Num].echoPin);
    }
    while ( echoValue == GPIO_PIN_LOW);

    uint32_t startTime = Get_TIMER1_Counter();
//    STK_enuGetElapsedTimeUs(&startTime);

    // Wait for the falling edge of the echo signal
    do{
    	echoValue = MCAL_GPIO_ReadPin(Private_pConfigs[Sensor_Num].echoPort,Private_pConfigs[Sensor_Num].echoPin);
    }
    while (echoValue == GPIO_PIN_HIGH);

    uint32_t endTime = Get_TIMER1_Counter();
//    STK_enuGetElapsedTimeUs(&endTime);

    // Calculate distance in centimeters
    uint32_t pulseDuration = endTime - startTime;
    *distance_cm = (pulseDuration * 0.0343) / 2; // Speed of sound is approximately 343 m/s

    return ES_OK;
}
