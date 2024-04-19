/*
 * LCD_Private.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Oct 1, 2023
 *	Brief		: This file contains all the
 */

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_
/************************************ Includes Start *************************************************/

#include "../../Stm32_F103C6_Drivers/inc/ErrorStates.h"
#include "../../Stm32_F103C6_Drivers/inc/stm32f103c6.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_RCC_driver.h"


#include "LCD_Config.h"

/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/
/************************************ Macros END  *************************************************/

/************************************ HelperEnums Declaration Start *************************************************/
/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ Private Declaration Start *************************************************/

static LCD_t * LCD_pstrConfigs;

/************************************ Private Declaration  END  *************************************************/


/************************************ Software Interfaces Start *************************************************/
static ES_t LCD_enuWriteAndLatch(uint8_t Copy_u8Data);
/************************************ Software Interfaces END  *************************************************/

#define PATTERN_SIZE					8


#define FOUR_BIT						44
#define EIGHT_BIT						88

#define FUNC_SET_FOUR_BIT				0x28
#define FUNC_SET_EIGHT_BIT				0x38

#ifndef MASK_BIT
#define MASK_BIT						1
#endif

#define SHIFT_PIN_7						7
#define SHIFT_PIN_6						6
#define SHIFT_PIN_5						5
#define SHIFT_PIN_4						4
#define SHIFT_PIN_3						3
#define SHIFT_PIN_2						2
#define SHIFT_PIN_1						1
#define SHIFT_PIN_0						0

#define RIGHT_INPUT						0x06
#define LEFT_INPUT						0x04
/****************	LCD COMMANDS	*******************/
#define DIS_ON__CURSOR_ON_BLINKING		0x0f
#define CLEAR_DISPLAY					0x01
#define ENTRY_MOOD						0x06
#define GO_HOME							0x02
#define ARABIC_CURSOR_MODE				0x04
#define ENGLISH_CURSOR_MODE				0x06
#define SHIFT_DISPLAY_LIFT				0x07
#define SHIFT_DISPLAY_RIGHT				0x05
#define ACTIVATE_2ND_LINE				0x3C
#define DISPLAY_ON_CURSOR_BLINKING		0x0E
#define DISPLAY_ON_CURSOR_OFF			0x0C
#define DISPLAY_OFF_CURSOR_OFF			0x08
#define START_OF_LINE1					0x80//can be used to display on other position at the same line
#define START_OF_LINE2					0xC0//same option
#define START_OF_LINE3					0x94//same option
#define START_OF_LINE4					0xD4//same option
#define START_OF_CGRAM					0x40//same option
//38	2 lines and 5×7 matrix



#endif /* HAL_LCD_LCD_PRIVATE_H_ */
