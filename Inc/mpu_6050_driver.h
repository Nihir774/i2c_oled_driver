/*
 * mpu_6050_driver.h
 *
 *  Created on: May 23, 2026
 *      Author: Nihirjyoti Muchahary
 */

#ifndef MPU_6050_DRIVER_H_
#define MPU_6050_DRIVER_H_

#include <stdint.h>

/**
  ******************************************************************************
  * @file    mpu6050_defs.h
  * @author  Hasan Erol
  * @brief   Register definitions and configuration macros for MPU6050 IMU
  ******************************************************************************
  * @attention
  * Reference: InvenSense MPU6050 Register Map and Datasheet
  *
  * This file provides all register addresses, bit masks, and configuration
  * options for the MPU6050 accelerometer and gyroscope.
  ******************************************************************************
  */

/* -------------------------------------------------------------------------- */
/* Device ID                                                                  */
/* -------------------------------------------------------------------------- */
#define MPU6050_WHO_AM_I_ID         (0x68)

/* -------------------------------------------------------------------------- */
/* Register map                                                               */
/* -------------------------------------------------------------------------- */
#define MPU6050_REG_SMPLRT          (0x19)
#define MPU6050_REG_CONFIG          (0x1A)
#define MPU6050_REG_GYRO_CONFIG     (0x1B)
#define MPU6050_REG_ACCEL_CONFIG    (0x1C)
#define MPU6050_REG_ACCEL_XOUT_H    (0x3B)
#define MPU6050_REG_TEMP_OUT_H      (0x41)
#define MPU6050_REG_GYRO_XOUT_H     (0x43)
#define MPU6050_REG_PWR_MGMT_1      (0x6B)
#define MPU6050_REG_PWR_MGMT_2      (0x6C)
#define MPU6050_REG_WHO_AM_I        (0x75)

/* -------------------------------------------------------------------------- */
/* Bit positions and masks                                                    */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_Bits Bit masks
 *  @brief Control and config bit positions/masks
 *  @{
 */

#define MPU6050_PWR1_SLEEP_Pos      (6)
#define MPU6050_PWR1_SLEEP_Msk      (1 << MPU6050_PWR1_SLEEP_Pos)

#define MPU6050_PWR1_TEMP_DIS_Pos   (3)
#define MPU6050_PWR1_TEMP_DIS_Msk   (1 << MPU6050_PWR1_TEMP_DIS_Pos)

#define MPU6050_PWR1_CLKSEL_Pos    (0U)
#define MPU6050_PWR1_CLKSEL_Msk    (0x7U << MPU6050_PWR1_CLKSEL_Pos)

#define MPU6050_ACCEL_FS_SEL_Pos   (3U)
#define MPU6050_ACCEL_FS_SEL_Msk   (0x3U << MPU6050_ACCEL_FS_SEL_Pos)

#define MPU6050_GYRO_FS_SEL_Pos    (3U)
#define MPU6050_GYRO_FS_SEL_Msk    (0x3U << MPU6050_GYRO_FS_SEL_Pos)
/** @} */

/* -------------------------------------------------------------------------- */
/* Accelerometer range                                                        */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_AccelRange Accelerometer range
 *  @brief Full-scale selection for accelerometer
 *  @{
 */

#define MPU6050_ACCEL_RANGE_2G             (0x0 << MPU6050_ACCEL_FS_SEL_Pos)
#define MPU6050_ACCEL_RANGE_4G             (0x1 << MPU6050_ACCEL_FS_SEL_Pos)
#define MPU6050_ACCEL_RANGE_8G             (0x2 << MPU6050_ACCEL_FS_SEL_Pos)
#define MPU6050_ACCEL_RANGE_16G            (0x3 << MPU6050_ACCEL_FS_SEL_Pos)


/* -------------------------------------------------------------------------- */
/* Gyroscope range                                                            */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_GyroRange Gyroscope range
 *  @brief Full-scale selection for gyroscope
 *  @{
 */
#define MPU6050_GYRO_RANGE_250DPS          (0x0 << MPU6050_GYRO_FS_SEL_Pos)
#define MPU6050_GYRO_RANGE_500DPS          (0x1 << MPU6050_GYRO_FS_SEL_Pos)
#define MPU6050_GYRO_RANGE_1000DPS         (0x2 << MPU6050_GYRO_FS_SEL_Pos)
#define MPU6050_GYRO_RANGE_2000DPS         (0x3 << MPU6050_GYRO_FS_SEL_Pos)

/* -------------------------------------------------------------------------- */
/* Digital low-pass filter                                                    */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_DLPF Digital low-pass filter
 *  @brief Configurations for DLPF (0–6)
 *  @{
 */
#define MPU6050_DLPF_CFG_0           (0x00)
#define MPU6050_DLPF_CFG_1           (0x01)
#define MPU6050_DLPF_CFG_2           (0x02)
#define MPU6050_DLPF_CFG_3           (0x03)
#define MPU6050_DLPF_CFG_4           (0x04)
#define MPU6050_DLPF_CFG_5           (0x05)
#define MPU6050_DLPF_CFG_6           (0x06)
/** @} */


/* -------------------------------------------------------------------------- */
/* Sensitivity scale factors                                                  */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_Scale Sensitivity scale factors
 *  @brief LSB per physical unit
 *  @{
 */
#define MPU6050_ACCEL_SENS_2G       (16384.0)
#define MPU6050_ACCEL_SENS_4G       (8192.0)
#define MPU6050_ACCEL_SENS_8G       (4096.0)
#define MPU6050_ACCEL_SENS_16G      (2048.0)

#define MPU6050_GYRO_SENS_250DPS    (131.0)
#define MPU6050_GYRO_SENS_500DPS    (65.5)
#define MPU6050_GYRO_SENS_1000DPS   (32.8)
#define MPU6050_GYRO_SENS_2000DPS   (16.4)
/** @} */

/* -------------------------------------------------------------------------- */
/* Bit positions and masks                                                    */
/* -------------------------------------------------------------------------- */
/** @defgroup MPU6050_Bits Bit masks
 *  @brief Control and config bit positions/masks
 *  @{
 */

#endif /* MPU_6050_DRIVER_H_ */
