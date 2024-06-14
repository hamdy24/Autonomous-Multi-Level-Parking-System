/*
 * MPU6050.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Abdallah
 */

#ifndef INCLUDES_MPU6050_H_
#define INCLUDES_MPU6050_H_

#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_I2C_driver.h"
#include "../../Stm32_F103C6_Drivers/inc/Stm32_F103C6_TIMER_driver.h"
#include "math.h"
#include <stdint.h>





#define MPU6050_Address		0x68

// MPU6050 Registers
#define  MPU6050_WHO_AM_I	0x75     // Contains the 6-bit I2C address of the MPU-60X0 (By default: 0x68)
#define	 ACCEL_XOUT_H 		0x3B
#define  GYRO_XOUT_H  		0x43
#define  CONFIG				0x1A	// Determine Sample rate for the MPU6050, and Enable DLPF
#define  GYRO_CONFIG		0x1B	// Gyroscope Configuration
#define  ACCEL_CONFIG 		0x1C	// Accelerometer Configuration
#define  PWR_MGMT_1			0x6B	// To wakeup the MPU6050


typedef enum{
	Data_Sent_Error,
	Data_Sent_Successfully,
	ERROR_CONFIG,
	SUCCESS_CONFIG,
	Data_Read_Error,
	Data_Read_Successfully
}MPU6050_Status;



// APIs


MPU6050_Status MPU6050_Init(void);

// We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
// Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
// Read accelerometer values 200 times
void MPU6050_CalculateError(void);


MPU6050_Status MPU6050_Write(uint8_t Register_Address, uint8_t *Data_To_Write, uint8_t dataLength);
MPU6050_Status MPU6050_Read(uint16_t Register_Address, uint8_t *Data_To_Read, uint8_t dataLength);

void MPU6050_GetReadings(char roll_string[], char pitch_string[], char yaw_string[]);

#endif /* INCLUDES_MPU6050_H_ */
