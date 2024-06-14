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
#define HC_SR04_NUM		2

uint8_t HC_Num = HC_SR04_NUM;


HC_SR04_Config_t UltraSonic_Configs[2] = {
		{
		.port = GPIOA,
		.triggerPin = GPIO_PIN_2,
		.echoPin = GPIO_PIN_3,
		},
		{
		.port = GPIOA,
		.triggerPin = GPIO_PIN_4,
		.echoPin = GPIO_PIN_5,
		}
};
