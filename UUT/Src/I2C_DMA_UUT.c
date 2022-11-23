#include "../../UUT/Inc/I2C_DMA_UUT.h"
#include "../../UUT/Inc/MAIN_UUT.h"
#include <string.h>

uint8_t I2C_UUT_DMA(const uint8_t *bit_pattern, const uint8_t bit_pattern_length)
{
	/* define and declare local buffers for slave and master */
	uint8_t local_buffer_slave[MAX_I2C_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;
	uint8_t local_buffer_master[MAX_I2C_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

	/* check status of receive transmit, error detection. (maby wire disconnected) */
	HAL_StatusTypeDef status = HAL_ERROR;

	/* Master -> Slave */
	status = HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, local_buffer_slave, bit_pattern_length);

	if(status == HAL_ERROR || status == HAL_TIMEOUT || status == HAL_BUSY)
	{
		return TEST_FAILED;
	}

	status = HAL_I2C_Master_Transmit_DMA(I2C_MASTER, I2C_SLAVE_ADDRESS, (uint8_t *)bit_pattern, bit_pattern_length);

	if(status == HAL_ERROR || status == HAL_TIMEOUT || status == HAL_BUSY)
	{
		return TEST_FAILED;
	}
	/* end commands Master -> Slave */

	/* Delay between DMA transmissions **too fast, data may not be send back properly */
	I2C_HAL_DELAY_2MS;

	/* Slave -> Master */
	status = HAL_I2C_Master_Receive_DMA(I2C_MASTER, I2C_SLAVE_ADDRESS, local_buffer_master, bit_pattern_length);

	if(status == HAL_ERROR || status == HAL_TIMEOUT || status == HAL_BUSY)
	{
		return TEST_FAILED;
	}

	status = HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE, local_buffer_slave, bit_pattern_length);

	if(status == HAL_ERROR || status == HAL_TIMEOUT || status == HAL_BUSY)
	{
		return TEST_FAILED;
	}
	/* end commands Slave -> Master */

	/* Delay between DMA transmission to strcmp **too fast, data may not be send back properly */
	I2C_HAL_DELAY_2MS;

	/* compare the data results at the end of communication with data given by the functions parameters */
	if(strcmp((char*)local_buffer_master, (char*)bit_pattern)==STRCMP_EQUALS)
	{
		/* test passed successfuly*/
		return TEST_SUCCEED;
	}

	/* test did not pass, test failed */
	return TEST_FAILED;
}
