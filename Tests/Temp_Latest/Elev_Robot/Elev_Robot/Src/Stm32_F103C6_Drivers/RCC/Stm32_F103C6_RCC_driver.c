/*
 * Stm32_F103C6_RCC_driver.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah
 */

#include "../inc/Stm32_F103C6_RCC_driver.h"

//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16

const uint8_t APBPrescTable[8U] = {0, 0, 0, 0, 1, 2, 3, 4};    // Shift 1 right === Division by 2^1


//Bits 7:4 HPRE: AHB prescaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512

const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


//Bits 3:2 SWS: System clock switch status
//Set and cleared by hardware to indicate which clock source is used as system clock.
//00: HSI oscillator used as system clock
//01: HSE oscillator used as system clock
//10: PLL used as system clock
//11: not applicable

uint32_t MCAL_RCC_GetSYSCLKFreq(void)
{
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK;
		break;
	case 1:
		// To do
		return HSE_RC_CLK;
		break;
	case 2:
		// To do
		return 16000000;
		break;
	}
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	//Bits 7:4 HPRE: AHB prescaler
	return ( MCAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[((RCC->CFGR >> 4) & 0xF)] );
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[((RCC->CFGR >> 8) & 0b111)] );
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	// Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[((RCC->CFGR >> 11) & 0b111)] );
}



/**================================================================
 * @Fn					- MCAL_RCC_CLK_Init
 * @brief 				- Initializes the clock speed based on the passed parameters
 * @param [in] 			- clock_source: Clock source to choose {HSI, HSE, or PLL}
 * @param [in] 			- clock_speed: Which speed you desire to work with, especially when working with PLL
 * @retval 				- CLK_STATUS: status that shows if the choosen source is ready to work with
 * Note					- clock_speed is useful when running with PLL as clock_source, meanwhile if you choose HSI as a source
 * 						this clock_speed value will be discarded, also HSE as a clock_source not supported yet
 *
 */


CLK_STATUS MCAL_RCC_CLK_Init(RCC_CLK_SRC clock_source, CLOCK_SPEED clock_speed)
{
	CLK_STATUS status = CLK_NOT_READY;


	switch(clock_source)
	{
	case HSI_CLK:
	{
		// Set 8MHz to be the clock which is set by default

		break;
	}

	case HSE_CLK:
	{
		// HSE not bypassed
		RCC->CR &= ~(1<<18);
		// Enable HSE
		RCC->CR |= (1<<16);
		// Make HSE to be input to PLL, to multiply it by some value
		RCC->CFGR |= (1<<16); // 1: HSE oscillator clock selected as PLL input clock


		switch(clock_speed)
		{
		case RCC_CLK_72M:
			RCC->CFGR |= (PLL_MUL9<<18);  // Multiply by 9 --> 8*9 = 72MHz
			break;
		}

		// Enabling the PLL

		/**	Bit 24 PLLON: PLL enable
					Set and cleared by software to enable PLL.
					Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
					PLL clock is used as system clock or is selected to become the system clock. Software
					must disable the USB OTG FS clock before clearing this bit.
					0: PLL OFF
					1: PLL ON
		 *
		 */

		RCC->CR |= (1<<24);

		// Select PLL as clock source
		RCC->CFGR &= ~(0b11<<0);
		RCC->CFGR |= (0b10<<0);


		// Prescalling Buses


//		Bits 7:4 HPRE: AHB prescaler
//		Set and cleared by software to control the division factor of the AHB clock.
//		0xxx: SYSCLK not divided
//		1000: SYSCLK divided by 2
//		1001: SYSCLK divided by 4
//		1010: SYSCLK divided by 8
//		1011: SYSCLK divided by 16
//		1100: SYSCLK divided by 64
//		1101: SYSCLK divided by 128
//		1110: SYSCLK divided by 256
//		1111: SYSCLK divided by

		RCC->CFGR |= (0b1000 << 4);   // SYSCLK Divided by 2

		// Using HCLK as it is for both APB1 and APB2

//		Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
//		Set and cleared by software to control the division factor of the APB low-speed clock
//		(PCLK1).
//		Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//		0xx: HCLK not divided
//		100: HCLK divided by 2
//		101: HCLK divided by 4
//		110: HCLK divided by 8
//		111: HCLK divided by 16



		// RCC->CFGR |= (0b100<<8); // HCLK Divided by 2

//		Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
//		Set and cleared by software to control the division factor of the APB high-speed clock
//		(PCLK2).
//		0xx: HCLK not divided
//		100: HCLK divided by 2
//		101: HCLK divided by 4
//		110: HCLK divided by 8
//		111: HCLK divided by 16


		// RCC->CFGR |= (0b100 << 11);
		RCC->CFGR &=~(0b111<<11);

		RCC->CFGR &=~(0b111<<8);




		break;
	}

	case PLL_CLK:
	{
		// Disable HSI Clock (Which is set by default)
		/*
		 * Bit 0 HSION: Internal high-speed clock enable
			Set and cleared by software.
			Set by hardware to force the internal 8 MHz RC oscillator ON when leaving Stop or Standby
			mode or in case of failure of the external 3-25 MHz oscillator used directly or indirectly as
			system clock. This bit can not be cleared if the internal 8 MHz RC is used directly or
			indirectly as system clock or is selected to become the system clock.
			0: Internal 8 MHz RC oscillator OFF
			1: Internal 8 MHz RC oscillator ON
		 */

		RCC->CR &= ~(1<<0);


		// PLL entry clock source

		/***
		 * Bit 16 PLLSRC: PLL entry clock source
			Set and cleared by software to select PLL clock source. This bit can be written only when PLL is
			disabled.
			0: HSI oscillator clock / 2 selected as PLL input clock
			1: Clock from PREDIV1 selected as PLL input clock
		 */
		RCC->CFGR &= ~(1<<16);


		// Choose the suitable PLL Multiplier based on the desired clock

		/**
		 * Bits 21:18 PLLMUL[3:0]: PLL multiplication factor
			These bits are written by software to define the PLL multiplication factor. They can be written only
			when PLL is disabled.
			000x: Reserved
			0010: PLL input clock x 4
			0011: PLL input clock x 5
			0100: PLL input clock x 6
			0101: PLL input clock x 7
			0110: PLL input clock x 8
			0111: PLL input clock x 9
			10xx: Reserved
			1100: Reserved
			1101: PLL input clock x 6.5
			111x: Reserved
		 *
		 */

		switch(clock_speed)
		{
		case RCC_CLK_16M:
			RCC->CFGR |= (PLL_MUL4<<18);
			break;
		case RCC_CLK_20M:
			RCC->CFGR |= (PLL_MUL5<<18);
			break;
		case RCC_CLK_24M:
			RCC->CFGR |= (PLL_MUL6<<18);
			break;
		case RCC_CLK_26M:
			RCC->CFGR |= (PULL_MUL6_5<<18);
			break;
		case RCC_CLK_28M:
			RCC->CFGR |= (PLL_MUL7<<18);
			break;
		case RCC_CLK_32M:
			RCC->CFGR |= (PLL_MUL8<<18);
			break;
		case RCC_CLK_36M:
			RCC->CFGR |= (PLL_MUL9<<18);
			break;
		}


		// Enabling the PLL

		/**	Bit 24 PLLON: PLL enable
			Set and cleared by software to enable PLL.
			Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
			PLL clock is used as system clock or is selected to become the system clock. Software
			must disable the USB OTG FS clock before clearing this bit.
			0: PLL OFF
			1: PLL ON
		 *
		 */

		RCC->CR |= (1<<24);

		// Wait for the PLL to lock ensures that the PLL is stable before it's used as a clock source

		/**
		 * Bit 25 PLLRDY: PLL clock ready flag
			Set by hardware to indicate that the PLL is locked.
			0: PLL unlocked
			1: PLL locked
		 */

		while(!(RCC->CR & (1<<25)));





		// Choose the PLL as a source to the SYSCLK

		/* 	Bits 1:0 SW[1:0]: System clock Switch
			Set and cleared by software to select SYSCLK source.
			Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of
			the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is
			enabled).
			00: HSI selected as system clock
			01: HSE selected as system clock
			10: PLL selected as system clock
			11: Not allowed
		 *
		 */

		RCC->CFGR |= (0b10 <<0);


		status = CLK_READY;



		break;
	}
	}
	return status;
}



