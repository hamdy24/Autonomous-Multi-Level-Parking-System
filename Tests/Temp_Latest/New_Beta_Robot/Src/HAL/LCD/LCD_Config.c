/*
 * LCD_Config.c
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Oct 1, 2023
 *	Brief		: This file contains all the
 */

/************************************ Includes Start *************************************************/
#include "LCD_Config.h"
/************************************ Includes END  *************************************************/

/************************************ Initialization Helper Start *************************************************/
LCD_t LCD_Configs = {
		.Mode = LCD_4Bit,

		.RS_Pin = GPIO_PIN_12,
//		.RW_Pin = GPIO_PB9,
		.En_Pin = GPIO_PIN_13,

		.D7_Pin = GPIO_PIN_0,
		.D6_Pin = GPIO_PIN_1,
		.D5_Pin = GPIO_PIN_10,
		.D4_Pin = GPIO_PIN_11,
};
