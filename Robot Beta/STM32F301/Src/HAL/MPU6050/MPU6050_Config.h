/*
 * MPU6050_Config.h
 *
 *  Author		: Hamdy Aouf
 *  Created on	: Dec 2, 2023
 *	Brief		: This file contains all the
 */

#ifndef HAL_MPU6050_MPU6050_CONFIG_H_
#define HAL_MPU6050_MPU6050_CONFIG_H_
/************************************ Includes Start *************************************************/

#include "../../Stm32_F103C6_Drivers/inc/ErrorStates.h"
#include "../../Stm32_F103C6_Drivers/inc/stm32f103c6.h"

#include "../../Stm32_F103C6_Drivers/inc/stm32_f103c6_i2c_driver.h"

/************************************ Includes END  *************************************************/

/************************************ Macros Start *************************************************/

// Define MPU6050 register addresses
#define MPU6050_ADDR         0xD0
#define MPU6050_REG_ACCEL_X  0x3B
#define MPU6050_REG_ACCEL_Y  0x3D
#define MPU6050_REG_ACCEL_Z  0x3F
#define MPU6050_REG_GYRO_X   0x43
#define MPU6050_REG_GYRO_Y   0x45
#define MPU6050_REG_GYRO_Z   0x47

/************************************ Macros END  *************************************************/

/************************************ HelperEnums Declaration Start *************************************************/
/************************************ HelperEnums Declaration  END  *************************************************/

/************************************ DataTypes Declaration Start *************************************************/


typedef struct {
    I2C_Typedef *i2c;
    I2C_Config_t* i2cConfigs;
} MPU6050_Config;

typedef struct {
    int16_t accelerometer_x;
    int16_t accelerometer_y;
    int16_t accelerometer_z;
    int16_t gyroscope_x;
    int16_t gyroscope_y;
    int16_t gyroscope_z;
} MPU6050_Data;

/************************************ DataTypes Declaration  END  *************************************************/

/************************************ Initialization Helper Start *************************************************/
/************************************ Initialization Helper END  *************************************************/


/************************************ Software Interfaces Start *************************************************/
/************************************ Software Interfaces END  *************************************************/



#endif /* HAL_MPU6050_MPU6050_CONFIG_H_ */
