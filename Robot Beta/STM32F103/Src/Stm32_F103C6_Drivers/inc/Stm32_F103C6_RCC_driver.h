/*
 * Stm32_F103C6_RCC_driver.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

// Includes
#include "stm32f103c6.h"


// This driver is mainly implemented to get PCLCK1,PCLCK2
// for the calculations of baud rate in UART driver
// These calculations are based on the assumption that our clock
// comes from HSI only



#define HSI_RC_CLK				(uint32_t)8000000
#define HSE_RC_CLK				(uint32_t)16000000


typedef enum{
	HSI_CLK,
	HSE_CLK,
	PLL_CLK
}RCC_CLK_SRC;

typedef enum{
	PLL_MUL4=2,
	PLL_MUL5,
	PLL_MUL6,
	PLL_MUL7,
	PLL_MUL8,
	PLL_MUL9,
	PULL_MUL6_5=13
}PLL_MULTIPLIER;


typedef enum{
	RCC_CLK_16M=16,
	RCC_CLK_20M=20,
	RCC_CLK_24M=24,
	RCC_CLK_26M=26,
	RCC_CLK_28M=28,
	RCC_CLK_32M=32,
	RCC_CLK_36M=36,
	RCC_CLK_8M=8
}CLOCK_SPEED;


typedef enum{
	CLK_NOT_READY,
	CLK_READY
}CLK_STATUS;


CLK_STATUS MCAL_RCC_CLK_Init(RCC_CLK_SRC clock_source, CLOCK_SPEED clock_speed);

uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
