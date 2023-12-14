/*
 * MPU6050_Program.c
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Dec 2, 2023
 *	Brief		: This file contains all the
 */


/************************************ Includes Start *************************************************/

#include "MPU6050_Private.h"

/************************************ Includes END  *************************************************/


/********************************************************************/
/*	Description:	This Function sets  		*/
/*	Parameters:							                       		*/
/*		@param1: 						               		*/
/*		&param2:			       		*/
/*	Return:			Returns Error State 	                       	*/
/*	Notes:			None  	*/
/********************************************************************/


ES_t MPU6050_Init(const MPU6050_Config *config){

	MCAL_I2C_Init(config->i2c,config->i2cConfigs);
	PrivConfig = config;
	return ES_OK;
}
ES_t MPU6050_ReadData(MPU6050_Data *data){

    uint8_t buffer[14];


    I2C_Generate_START(PrivConfig->i2c, ENABLE, Start);
    I2C_SendAddress(PrivConfig->i2c, MPU6050_ADDR, I2C_Direction_Transmitter);

    // Send the register address to read from
    MCAL_I2C_Slave_Transmit(PrivConfig->i2c, MPU6050_REG_ACCEL_X);


    I2C_Generate_START(PrivConfig->i2c, ENABLE, RepeatedStart);
    I2C_SendAddress(PrivConfig->i2c, MPU6050_ADDR, I2C_Direction_Reciever);

    // Read the data bytes
    for (int i = 0; i < 13; ++i) {
        buffer[i] = MCAL_I2C_Slave_Recieve(PrivConfig->i2c);
    }


    I2C_Generate_STOP(PrivConfig->i2c, ENABLE);


    data->accelerometer_x = (int16_t)((buffer[0] << 8) | buffer[1]);
    data->accelerometer_y = (int16_t)((buffer[2] << 8) | buffer[3]);
    data->accelerometer_z = (int16_t)((buffer[4] << 8) | buffer[5]);
    data->gyroscope_x = (int16_t)((buffer[8] << 8) | buffer[9]);
    data->gyroscope_y = (int16_t)((buffer[10] << 8) | buffer[11]);
    data->gyroscope_z = (int16_t)((buffer[12] << 8) | buffer[13]);

	return ES_OK;

}
