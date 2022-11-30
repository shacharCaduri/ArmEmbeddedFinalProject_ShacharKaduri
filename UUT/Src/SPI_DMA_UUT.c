#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "string.h"

/**@brief holding the data received back in master at the end of each iteration */
uint8_t master_buffer[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief static variable, holding the data received and sent back by the slave in each iteration */
uint8_t slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

/**
 * @brief 	the SPI under unit testing function which perform the actual tests according to number of
 * 			iterations, each iteration checks if the sent bit_pattern value equalt to the master buffer
 * 			after sending back to the master
 * @param bit_pattern
 * @param bit_pattern_length
 * @param iterations
 * @return
 */
t_status SPI_UUT_DMA( uint8_t *bit_pattern,  uint8_t bit_pattern_length, uint8_t iterations)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	/*
	 * temporary buffer to use when transmitting and receiving at the same time,
	 * thus, prevent race conditions.
	 */
	uint8_t tmp_buf[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;


	while(iterations)
	{
		memset(slave_buffer, INIT_TO_ZERO, sizeof(slave_buffer)/sizeof(*slave_buffer));
		memset(master_buffer, INIT_TO_ZERO, sizeof(master_buffer)/sizeof(*master_buffer));

		/* MASTER -> SLAVE */
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, tmp_buf, slave_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, bit_pattern, tmp_buf, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* delay time between transmissions for buffers to be update */
		SPI_SYNC_TIME;

		/* SLAVE -> MASTER*/
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buffer, tmp_buf, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, tmp_buf, master_buffer, bit_pattern_length);

		/* if something went wrong: wire/s disconnected, busy (still transmitting), noise on the line.. */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* delay time between transmissions for buffers to be update */
		SPI_SYNC_TIME;

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
