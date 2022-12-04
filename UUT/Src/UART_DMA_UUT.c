#include "../../UUT/Inc/UART_DMA_UUT.h"
#include <string.h>

/**@brief buffer for uart device 1 for receiving data */
uint8_t buffer_dev_1[MAX_UART_DEV1_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief buffer for uart device 0 for receiving data */
uint8_t buffer_dev_0[MAX_UART_DEV0_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief flag to raise when receive callback called indicate finished */
static uint8_t device0_rx_cplt_flag = CALLBACK_FLAG_RESET;

/**@brief flag to raise when receive callback called indicate device1 receive finished */
static uint8_t device1_rx_cplt_flag = CALLBACK_FLAG_RESET;

/**@brief  Rx Transfer completed callback. */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART_DEVICE_0->Instance)
	{
		device0_rx_cplt_flag = CALLBACK_FLAG_SET;
	}
	else if(huart->Instance == UART_DEVICE_1->Instance)
	{
		device1_rx_cplt_flag = CALLBACK_FLAG_SET;
	}
}

/**
 * @brief	the UART under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: DEVICE 1 -> DEVICE 0 -> DEVICE 1)
 */
t_status UART_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
{
	/* check status of receive transmit, error detection.*/
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{
		/* DEVICE 1 -> DEVICE 0 */
		status = HAL_UART_Receive_DMA(UART_DEVICE_0, buffer_dev_0, bit_pattern_length);

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

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(&device0_rx_cplt_flag, UART_TIMEOUT, UART_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		/* DEVICE 0 -> DEVICE 1 */
		status = HAL_UART_Receive_DMA(UART_DEVICE_1, buffer_dev_1, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_UART_Transmit_DMA(UART_DEVICE_0, buffer_dev_0, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands DEVICE 0 -> DEVICE 1 */

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(&device1_rx_cplt_flag, UART_TIMEOUT, UART_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		/* compare the data results at the end of communication with data given by the functions parameters */
		if(strcmp((char*)buffer_dev_1, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			/* test did not pass, test failed */
			return TEST_FAILED;
		}

		--iterations;
	}

	/* test passed successfuly*/
	return TEST_SUCCEED;
}
