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
		.trigPort = GPIOA,
		.echoPort = GPIOB,
		.triggerPin = GPIO_PIN_8,
		.echoPin = GPIO_PIN_15,
		},
		{
		.trigPort = GPIOB,
		.echoPort = GPIOA,
		.triggerPin = GPIO_PIN_12,
		.echoPin = GPIO_PIN_9,
		}
};
