#ifndef UART_H_UART_H_UART_H
#define UART_H_UART_H_UART_H
#include "main.h"
#include "stm32f7xx_hal.h"
#include "../../UUT/Inc/ExtraTools.h"

/* ***************************** Defines ********************************************** */
/**
 * @brief Hal delay for purpose of timing between transmit receive Device 1 -> Device 0
 * 		  to  Device 0 -> Device 1 (back), otherwise the times will be 2 short between the
 * 		  2 send and receive and it can affect the reliability of the communication, maby no
 * 		  data will be received. here 1 mili second is enough for this synchronization bewtween
 * 		  the 2 transmissions.
 */
#define UART_HAL_DELAY_1MS HAL_Delay(1)

/**
 * @brief the buffer (received data) size
 */
#define MAX_UART_DEV0_BUFFER_SIZE 255

/**
 * @brief the buffer (received data) size
 */
#define MAX_UART_DEV1_BUFFER_SIZE 255

/**
 * @brief the address of the handle of some UART device
 */
#define UART_DEVICE_1 &huart4

/**
 * @brief the address of the handle of some UART device
 */
#define UART_DEVICE_0 &huart6
/* ************************************************************************************ */

/* ************************ Externs *************************************************** */
/**
 * @brief the handle of some UART device
 */
extern UART_HandleTypeDef huart4;

/**
 * @brief the handle of some UART device
 */
extern UART_HandleTypeDef huart6;
/* ************************************************************************************ */

/* ************************** Functions *********************************************** */
/**
 * @fn 		t_status UART_DMA_UUT(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
 * @brief	the UART under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: DEVICE 1 -> DEVICE 0 -> DEVICE 1)
 * @example	DEVICE 1 transmit bit pattern "ASCII" to DEVICE 0 than the data received transmitted
 * 			which suppose to be "ASCII" back to DEVICE 1 and the received data here which also suppose
 * 			to be "ASCII" will be compared to bit pattern thus ensure UART is devices are passing the
 * 			test, otherwise the test fails and return result accordingly. number of iterations will be
 * 			run if one fails the test fails otherwise test passed
 *
 * @param bit_pattern 			the data to test the UART on
 * @param bit_pattern_length	the data's length to test the UART on
 * @param iterations			running tests number of iterations.
 * @return number of iterations will be run, each iteration if bit pattern at start of the communication
 * 		   equals to the same as in the end RETURN 0xff TEST_FAILED, otherwise  0X01 TEST_SUCCEED.
 */
t_status UART_DMA_UUT(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations);
/* ************************************************************************************ */
#endif //UART_H_UART_H_UART_H
