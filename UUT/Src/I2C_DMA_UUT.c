#include "../../UUT/Inc/I2C_DMA_UUT.h"
#include <string.h>

/**
 * @fn 		t_status UART_DMA_UUT(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
 * @brief	the I2C under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: Master -> Slave -> Master)
 */
t_status I2C_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
{
	/* define and declare local buffers for slave and master */
	uint8_t local_buffer_slave[MAX_I2C_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;
	uint8_t local_buffer_master[MAX_I2C_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

	/* check status of receive transmit, error detection. */
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{
		/* Master -> Slave */
		status = HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, local_buffer_slave, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_I2C_Master_Transmit_DMA(I2C_MASTER, I2C_SLAVE_ADDRESS, (uint8_t *)bit_pattern, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands Master -> Slave */

		/* Delay between DMA transmissions **too fast, data may not be send back properly */
		I2C_HAL_DELAY_2MS;

		/* Slave -> Master */
		status = HAL_I2C_Master_Receive_DMA(I2C_MASTER, I2C_SLAVE_ADDRESS, local_buffer_master, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE, local_buffer_slave, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands Slave -> Master */

		/* Delay between DMA transmission to strcmp **too fast, data may not be send back properly */
		I2C_HAL_DELAY_2MS;

		/* compare the data results at the end of communication with data given by the functions parameters */
		if(strcmp((char*)local_buffer_master, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			/* test did not pass, test failed */
			return TEST_FAILED;
		}

		--iterations;
	}

	/* test passed successfuly*/
	return TEST_SUCCEED;
}
