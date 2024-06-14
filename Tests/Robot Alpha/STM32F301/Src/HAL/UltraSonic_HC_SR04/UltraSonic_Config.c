/*
 * UltraSonic_Config.c
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 7, 2023
 *	Brief		: This file contains all the
 */


/************************************ Includes Start *************************************************/

#include "UltraSonic_Config.h"

/************************************ Includes END  *************************************************/



HC_SR04_Config_t UltraSonic_Configs = {
		.port = GPIOA,
		.triggerPin = GPIO_PIN_2,
		.echoPin = GPIO_PIN_3,
};
