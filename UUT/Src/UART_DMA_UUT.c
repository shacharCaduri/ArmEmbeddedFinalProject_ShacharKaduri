#include "../../UUT/Inc/UART_DMA_UUT.h"
#include <string.h>

/**
 * @fn 		t_status UART_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
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
t_status UART_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
{
	/* define and declare local buffers for device 1 and device 0 */
	uint8_t local_buffer_dev_1[MAX_UART_DEV1_BUFFER_SIZE] = INIT_ALL_ZERO;
	uint8_t local_buffer_dev_0[MAX_UART_DEV0_BUFFER_SIZE] = INIT_ALL_ZERO;

	/* check status of receive transmit, error detection.*/
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{
		/* DEVICE 1 -> DEVICE 0 */
		status = HAL_UART_Receive_DMA(UART_DEVICE_0, local_buffer_dev_0, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_UART_Transmit_DMA(UART_DEVICE_1, bit_pattern, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands DEVICE 1 -> DEVICE 0 */

		/* Delay between DMA transmissions **too fast, data may be send back properly */
		UART_SYNC_TIME;

		/* DEVICE 0 -> DEVICE 1 */
		status = HAL_UART_Receive_DMA(UART_DEVICE_1, local_buffer_dev_1, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_UART_Transmit_DMA(UART_DEVICE_0, local_buffer_dev_0, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands DEVICE 0 -> DEVICE 1 */

		/* Delay between DMA transmission to strcmp **too fast, data may not be send back properly */
		UART_SYNC_TIME;

		/* compare the data results at the end of communication with data given by the functions parameters */
		if(strcmp((char*)local_buffer_dev_1, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			/* test did not pass, test failed */
			return TEST_FAILED;
		}

		--iterations;
	}

	/* test passed successfuly*/
	return TEST_SUCCEED;
}
