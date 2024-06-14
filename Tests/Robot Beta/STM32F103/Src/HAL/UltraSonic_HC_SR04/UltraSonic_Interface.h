/*
 * UltraSonic_Interface.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 7, 2023
 *	Brief		: This file contains all the
 */

#ifndef STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_INTERFACE_H_
#define STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_INTERFACE_H_
/************************************ Includes Start *************************************************/

#include "UltraSonic_Config.h"

/************************************ Includes END  *************************************************/

/************************************ Initialization Helper Start *************************************************/

extern HC_SR04_Config_t UltraSonic_Configs[2];

/************************************ Initialization Helper END  *************************************************/


/************************************ Software Interfaces Start *************************************************/
// Initialize HC-SR04
ES_t HC_SR04_Init(HC_SR04_Config_t* Copy_pArrUltrasonicConfigs);
// Read the distance measured by HC-SR04 in centimeters
ES_t HC_SR04_ReadDistance(uint8_t Sensor_Num,uint32_t* distance_cm);


/************************************ Software Interfaces END  *************************************************/



#endif /* STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_INTERFACE_H_ */
