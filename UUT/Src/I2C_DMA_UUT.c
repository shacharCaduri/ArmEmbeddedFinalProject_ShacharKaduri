#include "../../UUT/Inc/I2C_DMA_UUT.h"
#include "../../UUT/Inc/MAIN_UUT.h"
#include <string.h>

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
uint8_t I2C_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
{
	/* define and declare local buffers for slave and master */
	uint8_t local_buffer_slave[MAX_I2C_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;
	uint8_t local_buffer_master[MAX_I2C_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

	/* check status of receive transmit, error detection. (maby wire disconnected) */
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
