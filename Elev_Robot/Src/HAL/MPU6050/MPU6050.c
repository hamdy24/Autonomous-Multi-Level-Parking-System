/*
 * MPU6050.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Abdallah
 */


#include "../includes/MPU6050.h"


/**================================================================
 * @Fn					- MPU6050_Init
 * @brief 				- Initializes MPU6050 By initializing I2C and configuration registers in MPU6050
 * @param [in] 			- None
 * @retval 				- MPU6050_Status: Configuration Status (Succeeded or not)
 * Note					- Data written in ACCEL and GYRO register should be changed to be suitable for your application
 */

MPU6050_Status MPU6050_Init(void)
{
	MPU6050_Status Status = ERROR_CONFIG;

	// I2C_init
	// PB6: I2C1_SCL
	// PB7: I2C1_SDA

	I2C_Config_t I2C_Cfg;

	// I2C Controller act as a master
	I2C_Cfg.General_Call_Address_Detection = I2C_ENGC_DISABLE;
	I2C_Cfg.ACK_Control = I2C_ACK_DISABLE;
	I2C_Cfg.I2C_Clock_Speed = I2C_SCLK_SM_100K;
	I2C_Cfg.I2C_Mode = I2C_MODE_I2C;
	I2C_Cfg.P_Slave_Event_CallBack = NULL;
	I2C_Cfg.Stretch_Mode = I2C_CLK_Stretch_Enable;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C_Cfg);

	// ===================================================== //


	uint8_t DataCheck = 0;
	uint8_t Data = 0;

	// Read the MPU6050 address from WHO_AM_I register and make sure that it is 0x68
	MPU6050_Read(MPU6050_WHO_AM_I, &DataCheck, 1);

	if(DataCheck != (0x68))
	{
		while(1);
	}else{
		// Start Initialization of the MPU6050
		// where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz
		// when the DLPF is enabled (see Register 26)
		Data = 0x05;
		MPU6050_Write(CONFIG, &Data, 1);


		// Set gyroscope Configuration
		// (FS_SEL = 1) (± 500 °/s )suitable for applications that involve faster and more dynamic rotational movements
		Data = 0x08;
		MPU6050_Write(GYRO_CONFIG, &Data, 1);


		// Set accelerometer configuration
		// (AF_SEL = 2) (± 8g)suitable for applications that require measuring very high levels of acceleration
		Data = 0x10;
		MPU6050_Write(ACCEL_CONFIG, &Data, 1);


		// Wake up the MPU6050
		// On writing (0x00) to the PWR_MGMT_1 Register, sensor wakes up and the Clock sets up to 8 MHz
		// 0x00 Internal 8MHz oscillator
		Data = 0x00;
		MPU6050_Write(PWR_MGMT_1, &Data, 1);

	}
	Status = SUCCESS_CONFIG;
	return Status;
}



/**================================================================
 * @Fn					- MPU6050_Write
 * @brief 				- Write Data in a specific register in MPU6050
 * @param [in] 			- Register_Address: Address of register you want to write in
 * @param [in] 			- Data_To_Write: Data bytes to be written in this register (Mostly 1Byte to just configure the register)
 * @param [in] 			- dataLength: Number of bytes to write in this register (Mostly 1)
 * @retval 				- MPU6050_Status: Data written status (If succeeded or not)
 * Note					- The write sequence is specified in MPU6050 Datasheet
 */


MPU6050_Status MPU6050_Write(uint8_t Register_Address, uint8_t *Data_To_Write, uint8_t dataLength)
{
	MPU6050_Status Status = Data_Sent_Error;

	// Write Sequence: Master (S / AD+W / RA / DATA / DATA / P)
	// Slave sends ACK after each byte

	uint8_t ByteCounter = 0;

	// Maximum Bytes to write is (2 Bytes (Register Address + DataToBeWritten in the Register))
	uint8_t Buffer[3];

	Buffer[0] = (uint8_t)Register_Address;

	for(ByteCounter=1; ByteCounter<(dataLength+1);ByteCounter++)
	{
		Buffer[ByteCounter] = Data_To_Write[ByteCounter-1];
	}

	// dataLength+1 to include the Register address to write on
	MCAL_I2C_Master_Transmit(I2C1, MPU6050_Address, Buffer, dataLength+1, With_Stop, Start);


	Status = Data_Sent_Successfully;

	return Status;
}


/**================================================================
 * @Fn					- MPU6050_Read
 * @brief 				- Read MultiBytes data from a specific register in MPU6050
 * @param [in] 			- Register_Address: Address of register you want to read from
 * @param [in] 			- Data_To_Read: Data bytes to read from a specific register
 * @param [in] 			- dataLength: Number of bytes to be read
 * @retval 				- MPU6050_Status: Data Read status (If succeeded or not)
 * Note					- This function supports multibytes read from registers in MPU6050 by moving among registers
 */

MPU6050_Status MPU6050_Read(uint16_t Register_Address, uint8_t *Data_To_Read, uint8_t dataLength)
{
	MPU6050_Status Status = Data_Read_Error;

	// Read Sequence: Master (S / AD+W / RA / S / AD+R      / ACK      / NACK / P)
	// 				  Slave (		  ACK  ACK        ACK DATA    DATA           )

	uint8_t Buffer[2];
	Buffer[0] = (uint8_t)Register_Address;

	// Sends the Register address to read from
	MCAL_I2C_Master_Transmit(I2C1, MPU6050_Address, Buffer, 1, Without_Stop, Start);
	// Receives MultiByte data from this register
	MCAL_I2C_Master_Receive(I2C1, MPU6050_Address, Data_To_Read, dataLength, With_Stop, RepeatedStart);

	Status = Data_Read_Successfully;


	return Status;
}


int counterReadings = 0;
float AccErrorX, AccErrorY;
int GyroErrorX, GyroErrorY, GyroErrorZ;
float AccX, AccY, AccZ;
uint8_t dataFromMPU6050X[6];



/**================================================================
 * @Fn					- MPU6050_CalculateError
 * @brief 				- Calculates Error in readings of MPU6050
 * @param [in] 			- None
 * @retval 				- None
 * Note					- This function reads 200 readings first to specify the error in readings and this value
 * 							can be offset to the actual readings in the main application
 */

void MPU6050_CalculateError(void)
{
	while(counterReadings < 200)
	{
		MPU6050_Read(ACCEL_XOUT_H, dataFromMPU6050X, 6);
		AccX = ((dataFromMPU6050X[0] << 8) | (dataFromMPU6050X[1])) / 4096.0;
		AccY = ((dataFromMPU6050X[2] << 8) | (dataFromMPU6050X[3])) / 4096.0;
		AccZ = ((dataFromMPU6050X[4] << 8) | (dataFromMPU6050X[5])) / 4096.0;
		// These calculations are part of a sensor fusion algorithm to estimate the orientation of the sensor with respect to the gravitational field.
		AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / 3.14));
		AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / 3.14));
		counterReadings++;
	}
	//Divide the sum by 200 to get the error value
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;
	counterReadings = 0;

	while(counterReadings < 200)
	{
		// ± 500 °/s 65.5 LSB/°/s
		MPU6050_Read(GYRO_XOUT_H, dataFromMPU6050X, 6);
		GyroErrorX = ((int16_t)(dataFromMPU6050X[0] << 8 | dataFromMPU6050X [1])) / 65.5;
		GyroErrorY = ((int16_t)(dataFromMPU6050X[2] << 8 | dataFromMPU6050X [3])) / 65.5;
		GyroErrorZ = ((int16_t)(dataFromMPU6050X[4] << 8 | dataFromMPU6050X [5])) / 65.5;
		counterReadings++;
	}
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorY / 200;
}


uint8_t Data = 0;
float Accel_X_RAW = 0;
float Accel_Y_RAW = 0;
float Accel_Z_RAW = 0;
uint8_t dataFromMPU6050[6];
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ,yaw,roll,pitch;
int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;
float GyroX,GyroY,GyroZ;
float elapsedTime=0.015, currentTime, previousTime;





void MPU6050_GetReadings(char roll_string[], char pitch_string[], char yaw_string[])
{
	// Init Acceleration
	Data = 0x00;
	MPU6050_Write(PWR_MGMT_1, &Data, 1);

	Data = 0x05;
	MPU6050_Write(CONFIG, &Data, 1);

	Data = 0x10;
	MPU6050_Write(ACCEL_CONFIG, &Data, 1);


	// Acceleration Measurements
	// 2 ±8g 4096 LSB/g
	// Read 6 Registers from ACCEL_XOUT_H till ACCEL_ZOUT_L
	MPU6050_Read(ACCEL_XOUT_H, dataFromMPU6050, 6);
	Accel_X_RAW = ((int16_t)((dataFromMPU6050[0] << 8) | (dataFromMPU6050[1]))) / 4096.0;
	Accel_Y_RAW = ((int16_t)((dataFromMPU6050[2] << 8) | (dataFromMPU6050[3]))) / 4096.0;
	Accel_Z_RAW = ((int16_t)((dataFromMPU6050[4] << 8) | (dataFromMPU6050[5]))) / 4096.0;

	accAngleX = (atan(Accel_Y_RAW / sqrt(pow(Accel_X_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) - 0.58; // AccErrorX ~(0.58)
	accAngleY = (atan(-1 * Accel_X_RAW / sqrt(pow(Accel_Y_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) + 1.58; // AccErrorY ~(-1.58)

	// Init Gyroscope
	Data = 0x08;
	MPU6050_Write(GYRO_CONFIG, &Data, 1);


	// Gyroscope Measurements
	MPU6050_Read(GYRO_XOUT_H, dataFromMPU6050, 6);
	Gyro_X_RAW = (int16_t)(dataFromMPU6050[0] << 8 | dataFromMPU6050 [1]);
	Gyro_Y_RAW = (int16_t)(dataFromMPU6050[2] << 8 | dataFromMPU6050 [3]);
	Gyro_Z_RAW = (int16_t)(dataFromMPU6050[4] << 8 | dataFromMPU6050 [5]);
	// Correct the outputs with the calculated error values
	GyroX = (Gyro_X_RAW / 65.5) - GyroErrorX; // GyroErrorX ~(-0.56)
	GyroY = (Gyro_Y_RAW / 65.5) - GyroErrorY; // GyroErrorY ~(2)
	GyroZ = (Gyro_Z_RAW / 65.5) - GyroErrorZ; // GyroErrorZ ~ (-0.8)

	// Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by seconds (s) to get the angle in degrees
	// Calculate elapsed time with seconds
	elapsedTime = Get_TIMER2_Counter();
	elapsedTime /= 1000000;

	TIMER2_Stop();

	gyroAngleX = gyroAngleX + (GyroX * elapsedTime);
	gyroAngleY = gyroAngleY + (GyroY * elapsedTime);
	yaw = yaw + (GyroZ * elapsedTime);


	TIMER2_Start();


	roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
	pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;


	sprintf(roll_string, "%d\n", (int)roll);
	sprintf(pitch_string, "%d\n", (int)pitch);
	sprintf(yaw_string, "%d\n", (int)yaw);
}






