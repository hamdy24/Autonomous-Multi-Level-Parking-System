/*
 * LCD_Interface.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Oct 1, 2023
 *	Brief		: This file contains all the
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_
/************************************ Includes Start *************************************************/
#include "LCD_Config.h"
/************************************ Includes END  *************************************************/

/************************************ Initialization Helper Start *************************************************/
extern LCD_t LCD_Configs ;

/************************************ Initialization Helper END  *************************************************/


/************************************ Software Interfaces Start *************************************************/


ES_t LCD_enuInit(LCD_t * Copy_pstrConfigs);

ES_t LCD_enuSendData(uint8_t Copy_u8Data);

ES_t LCD_enuSendCommand(uint8_t Copy_u8Command);

ES_t LCD_enuSendString(char * Copy_pcString);

ES_t LCD_enuJumpCursorTo( uint8_t Copy_u8StartX_Position , uint8_t Copy_u8StartY_Position);

ES_t LCD_enuClearDisplay(void);

ES_t LCD_enuDisplayIntNum(int Copy_s32IntNumber);

ES_t LCD_enuDisplayCustomArrCharachter(uint8_t * Copy_u8pAu8CharHEXA , uint8_t Copy_u8NumOfPattern , uint8_t Copy_u8InputDirection);

ES_t LCD_enuDisplayCustomSingleCharachter(uint8_t * Copy_u8pAu8CharHEXA ,uint8_t Copy_u8PatternPosition,uint8_t Copy_u8DisplayPosition );

ES_t LCD_enuDisplayFloatNum(float Copy_f32FloatNumber, uint8_t Copy_u8FractionDigits);

ES_t LCD_enuSavePattern(uint8_t *Copy_u8pAu8CharHEXA,uint8_t Copy_u8PatternPosition);

ES_t LCD_enuPrintPattern(uint8_t Copy_u8PatternNum,uint8_t Copy_u8PositionX,uint8_t Copy_u8PositionY);

//ES_t LCD_enuShiftDisplay(u8 Copy_u8StartX_Position,u8 Copy_u8StartY_Position, u8 Copy_u8Num_ofShifts)



/************************************ Software Interfaces END  *************************************************/



#endif /* HAL_LCD_LCD_INTERFACE_H_ */
