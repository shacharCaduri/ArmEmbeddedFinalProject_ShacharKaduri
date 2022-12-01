#include "../../UUT/Inc/UART_DMA_UUT.h"
#include <string.h>

/**
 * @brief	the UART under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: DEVICE 1 -> DEVICE 0 -> DEVICE 1)
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
