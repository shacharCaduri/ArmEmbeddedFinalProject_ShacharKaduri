/*
 * ETH_DMA.h
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */
#ifndef I2C_H_I2C_H_I2C_H
#define I2C_H_I2C_H_I2C_H
#include "main.h"
#include "stm32f7xx_hal.h"

/* ***************************** Defines ********************************************** */
/**@brief the buffer (received data) size */
#define MAX_I2C_SLAVE_BUFFER_SIZE 255

/**@brief the data (sent data) size*/
#define MAX_I2C_MASTER_BUFFER_SIZE 255

/**
 * @brief Hal delay for purpose of timing between transmit receive Master -> Slave
 * 		  to  Slave -> Master (back), otherwise the times will be 2 short between the
 * 		  2 send and receive and it can affect the reliability of the communication, maby no
 * 		  data will be received. here 2 milliseconds is enough for this synchronization bewtween
 * 		  the 2 transmissions.
 */
#define I2C_HAL_DELAY_2MS HAL_Delay(2)

/**
 * @def   USER_I2C_SLAVE_ADDRESS
 * @brief the user costume define slave address
 */
#define I2C_SLAVE_ADDRESS 15

/**@brief the address of the handle of the I2C Master device*/
#define I2C_MASTER &hi2c2

/**@brief the address of the handle of the I2C Slave device*/
#define I2C_SLAVE &hi2c1
/* ************************************************************************************ */

/* ***************************** Externs ********************************************** */
/**@brief the handle of i2c Master*/
extern I2C_HandleTypeDef hi2c1;

/**@brief the handle of i2c Slave*/
extern I2C_HandleTypeDef hi2c2;
/* ************************************************************************************ */

/* ******************************* Functions ****************************************** */
/**
 * @fn 		uint8_t I2C_UUT_DMA(const uint8_t *bit_pattern, const uint8_t bit_pattern_length)
 * @brief	the I2C under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: Master -> Slave -> Master)
 * @example	Master transmit bit pattern "ASCII" to Slave than the data received transmitted
 * 			which suppose to be "ASCII" back to Master and the received data here which also
 * 			suppose to be "ASCII" will be compared to bit pattern, thus ensure I2C devices
 * 			are passing the test, otherwise the test fails and return result accordingly.
 *
 * @param 	bit_pattern 			the data to test the I2C on
 * @param 	bit_pattern_length		the data's length to test the I2C on
 * @param iterations			running tests number of iterations.
 * @return number of iterations will be run, each iteration if bit pattern at start of the communication
 * 		   equals to the same as in the end RETURN 0xff TEST_FAILED, otherwise  0X01 TEST_SUCCEED.
 */
uint8_t I2C_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations);
/* ************************************************************************************ */

#endif //I2C_H_I2C_H_I2C_H
