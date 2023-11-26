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

		.RS_Pin = 12,
//		.RW_Pin = GPIO_PB9,
		.En_Pin = 13,

		.D7_Pin = 0,
		.D6_Pin = 1,
		.D5_Pin = 10,
		.D4_Pin = 11,
};
