
#ifndef MPU6050_CONFIG_H
#define MPU6050_CONFIG_H

/************************************************************************************/
/******************************* MPU6050 & I2C Configuration ************************/
/************************************************************************************/
#define MPU6050_I2C              I2C_1    /* Get Option From I2C Interface          */
#define MPU6050_I2C_PORT         PORTB    /* Get Option From GPIO Interface         */
#define MPU6050_I2C_SDA_PIN      PIN7     /* Get Option From GPIO Interface         */
#define MPU6050_I2C_SCL_PIN      PIN6     /* Get Option From GPIO Interface         */
#define MPU6050_I2C_PULL         HIGH     /* Set  HIGH if Pull up Or LOW if No Pull */
/************************************************************************************/
/******************************* MPU6050 Configuration ******************************/
/************************************************************************************/
// power management register 0X6B we should write all 0's to wake the sensor up
#define MPU6050_PWR_MGMT_1_DATA       0
// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
#define MPU6050_SMPLRT_DIV_DATA       0x07
// Set accelerometer configuration in ACCEL_CONFIG Register
// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
#define MPU6050_ACCEL_CONFIG_DATA     0x00
// Set Gyroscopic configuration in GYRO_CONFIG Register
// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 °/s
#define MPU6050_GYRO_CONFIG_DATA      0x00
/************************************************************************************/
/*** convert the RAW values into dps (°/s)
	 we have to divide according to the Full scale value set in FS_SEL
	 I have configured FS_SEL = 0. So I am dividing by 131.0
	 for more details check GYRO_CONFIG Register              ****/
#define MPU6050_GYRO_DIVIDE         131.0
/*** convert the RAW values into dps (°/s)
	 we have to divide according to the Full scale value set in FS_SEL
	 I have configured FS_SEL = 0. So I am dividing by 131.0
	 for more details check GYRO_CONFIG Register              ****/
#define MPU6050_ACCEL_DIVIDE        16384.0
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/


#endif 
