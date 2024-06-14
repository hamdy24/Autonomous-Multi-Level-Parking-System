/*
 * UltraSonic_Private.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Nov 7, 2023
 *	Brief		: This file contains all the
 */

#ifndef STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_PRIVATE_H_
#define STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_PRIVATE_H_
/************************************ Includes Start *************************************************/

#include "../../Stm32_F103C6_Drivers/inc/ErrorStates.h"
#include "../../Stm32_F103C6_Drivers/inc/stm32f103c6.h"


#include "UltraSonic_Config.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_RCC_driver.h"


/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/
/************************************ Macros END  *************************************************/

/************************************ Private Declaration Start *************************************************/

static HC_SR04_Config_t * Private_pConfigs;

/************************************ Private Declaration  END  *************************************************/

/************************************ Private Software Interfaces Start *************************************************/

// Send a trigger signal to start distance measurement
static void HC_SR04_Trigger();

/************************************ Private Software Interfaces END  *************************************************/



#endif /* STM32F401_DRIVERS_HAL_ULTRASONIC_HC_SR04_ULTRASONIC_PRIVATE_H_ */
