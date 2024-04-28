/*
 * UltraSonic_Config.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 7, 2023
 *	Brief		: This file contains all the
 */

#ifndef STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_CONFIG_H_
#define STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_CONFIG_H_
/************************************ Includes Start *************************************************/

#include "../../Stm32_F103C6_Drivers/inc/ErrorStates.h"
#include "../../Stm32_F103C6_Drivers/inc/stm32f103c6.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_RCC_driver.h"


/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/
/************************************ Macros END  *************************************************/

/************************************ HelperEnums Declaration Start *************************************************/
/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ DataTypes Declaration Start *************************************************/





// Configuration structure for HC-SR04
typedef struct {
	GPIO_TypeDef* port;
    uint8_t triggerPin;  // Pin connected to the trigger
    uint8_t echoPin;     // Pin connected to the echo
} HC_SR04_Config_t;


/************************************ DataTypes Declaration  END  *************************************************/


#endif /* STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_CONFIG_H_ */
