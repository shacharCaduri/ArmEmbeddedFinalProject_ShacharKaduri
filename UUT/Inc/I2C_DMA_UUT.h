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
#include "../../UUT/Inc/ExtraTools.h"

/* ***************************** Defines ********************************************** */
/**@brief the buffer (received data) size */
#define MAX_I2C_SLAVE_BUFFER_SIZE 255

/**@brief the data (sent data) size*/
#define MAX_I2C_MASTER_BUFFER_SIZE 255

/**
 * @brief 	timeout before flag set, maximum waiting time in milliseconds
 * 			for flag to be raised.
 */
#define I2C_TIMEOUT 50

/**@brief time in milliseconds to wait for DMA to finish */
#define I2C_DMA_TIME 20

/**
 * @def   USER_I2C_SLAVE_ADDRESS
 * @brief the user costume define slave address
 */
#define I2C_SLAVE_ADDRESS 30

/**@brief the address of the handle of the I2C Master device*/
#define I2C_MASTER (&hi2c2)

/**@brief the address of the handle of the I2C Slave device*/
#define I2C_SLAVE (&hi2c1)
/* ************************************************************************************ */

/* ***************************** Externs ********************************************** */
/**@brief the handle of i2c Master*/
extern I2C_HandleTypeDef hi2c1;

/**@brief the handle of i2c Slave*/
extern I2C_HandleTypeDef hi2c2;

/**@brief buffer for slave device for receiving data */
extern uint8_t i2c_buffer_slave[MAX_I2C_SLAVE_BUFFER_SIZE];

/**@brief buffer for master device for receiving data */
extern uint8_t i2c_buffer_master[MAX_I2C_MASTER_BUFFER_SIZE];
/* ************************************************************************************ */

/* ******************************* Functions ****************************************** */
/**
 * @fn 		t_status UART_DMA_UUT(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
 * @brief	the I2C under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: Master -> Slave -> Master)
 * @example	Master transmit bit pattern "ASCII" to Slave than the data received transmitted
 * 			which suppose to be "ASCII" back to Master and the received data here which also
 * 			suppose to be "ASCII" will be compared to bit pattern, thus ensure I2C devices
 * 			are passing the test, otherwise the test fails and return result accordingly.
 *
 * @param 	bit_pattern 			the data to test the I2C on
 * @param 	bit_pattern_length		the data's length to test the I2C on
 * @param 	iterations				running tests number of iterations.
 * @return number of iterations will be run, each iteration if bit pattern at start of the communication
 * 		   equals to the same as in the end RETURN 0xff TEST_FAILED, otherwise  0X01 TEST_SUCCEED.
 */
t_status I2C_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations);
/* ************************************************************************************ */

#endif //I2C_H_I2C_H_I2C_H
