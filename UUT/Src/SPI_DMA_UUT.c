#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "string.h"

/**@brief holding the data received back in master at the end of each iteration */
uint8_t master_buffer[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief static variable, holding the data received and sent back by the slave in each iteration */
uint8_t slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

t_status SPI_UUT_DMA( uint8_t *bit_pattern,  uint8_t bit_pattern_length, uint8_t iterations)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{
		/* MASTER -> SLAVE */
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buffer, slave_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, bit_pattern, master_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* delay so buffers will have enough time to update */
		SPI_HAL_DELAY_2MS;

		/* SLAVE -> MASTER*/
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buffer, master_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, master_buffer, master_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* delay so buffers will have enough time to update */
		SPI_HAL_DELAY_2MS;

		/* end of iteration test if sent bit pattern is not equal to buffer at the end the peripheral not working correctly, test failed*/
		if(strcmp((char*)master_buffer, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			return TEST_FAILED;
		}

		/* decrement iterations variable so the loop will stop when reach 0*/
		--iterations;
	}

	/*
	 * if all the tests iterations passed (bit_pattern equals master_buffer in every iteration) than the peripheral is working correctly,
	 * test passed.
	 */
	return TEST_SUCCEED;
}
