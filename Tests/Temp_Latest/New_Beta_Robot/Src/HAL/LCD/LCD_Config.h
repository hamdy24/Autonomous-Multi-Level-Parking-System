/*
 * LCD_Config.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Oct 1, 2023
 *	Brief		: This file contains all the
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_
/************************************ Includes Start *************************************************/
#include "../../Stm32_F103C6_Drivers/inc/ErrorStates.h"
#include "../../Stm32_F103C6_Drivers/inc/stm32f103c6.h"

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_gpio_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"

/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/
/************************************ Macros END  *************************************************/

/************************************ HelperEnums Declaration Start *************************************************/
typedef enum{
	LCD_4Bit = 4,
	LCD_8Bit = 8,
}LCD_Mode_t;

/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ DataTypes Declaration Start *************************************************/

typedef struct{

	LCD_Mode_t Mode;
	uint8_t RowsNum ;
	uint8_t ColumnsNum;

	/** Control Pins  **/
	uint16_t RS_Pin;
	uint16_t RW_Pin;
	uint16_t En_Pin;

	/** Data Pins	**/
	uint16_t D7_Pin;
	uint16_t D6_Pin;
	uint16_t D5_Pin;
	uint16_t D4_Pin;
	uint16_t D3_Pin;
	uint16_t D2_Pin;
	uint16_t D1_Pin;
	uint16_t D0_Pin;

}LCD_t;


typedef struct{
	uint8_t D7_Pin;
	uint8_t D6_Pin;
	uint8_t D5_Pin;
	uint8_t D4_Pin;
}LCD_4Bit_Pins_t;

typedef struct{
	uint8_t D7_Pin;
	uint8_t D6_Pin;
	uint8_t D5_Pin;
	uint8_t D4_Pin;
	uint8_t D3_Pin;
	uint8_t D2_Pin;
	uint8_t D1_Pin;
	uint8_t D0_Pin;
}LCD_8Bit_Pins_t;

//typedef struct{
//
//	union {
//		LCD_4Bit_Pins_t Pins_4Bits;
//		LCD_8Bit_Pins_t Pins_8Bits;
//	};
//
//}LCD2_t;







/************************************ DataTypes Declaration  END  *************************************************/


#endif /* HAL_LCD_LCD_CONFIG_H_ */
