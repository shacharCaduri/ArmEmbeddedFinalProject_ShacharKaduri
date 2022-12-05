#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "string.h"

/**@brief holding the data received back in master at the end of each iteration */
uint8_t master_buffer[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief static variable, holding the data received and sent back by the slave in each iteration */
uint8_t slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief callback flag when receive is done */
static	uint8_t  spi_master_cplt_callback_flag = CALLBACK_FLAG_RESET;

/**@brief callback flag when receive is done */
static	uint8_t  spi_slave_cplt_callback_flag = CALLBACK_FLAG_RESET;

/**@brief  Tx and Rx Transfer completed callback.  */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI_MASTER->Instance)
	{
		spi_master_cplt_callback_flag = CALLBACK_FLAG_SET;
	}
	else if(hspi->Instance == SPI_SLAVE->Instance)
	{
		spi_slave_cplt_callback_flag = CALLBACK_FLAG_SET;
	}
}


/**
 * @brief 	the SPI under unit testing function which perform the actual tests according to number of
 * 			iterations, each iteration checks if the sent bit_pattern value equalt to the master buffer
 * 			after sending back to the master
 */
t_status SPI_UUT_DMA( uint8_t *bit_pattern,  uint8_t bit_pattern_length, uint8_t iterations)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	/*
	 * temporary buffer to use when transmitting and receiving at the same time.
	 */
	uint8_t tmp_buf[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;


	while(iterations)
	{
		memset(slave_buffer, INIT_TO_ZERO, sizeof(slave_buffer)/sizeof(*slave_buffer));
		memset(master_buffer, INIT_TO_ZERO, sizeof(master_buffer)/sizeof(*master_buffer));

		/* MASTER -> SLAVE */
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, tmp_buf, slave_buffer, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, bit_pattern, tmp_buf, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(NOT_ADC, SPI_SLAVE->hdmarx, &spi_slave_cplt_callback_flag, SPI_TIMEOUT, SPI_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		/* SLAVE -> MASTER*/
		status = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buffer, tmp_buf, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, tmp_buf, master_buffer, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(NOT_ADC,SPI_MASTER->hdmarx, &spi_master_cplt_callback_flag, SPI_TIMEOUT, SPI_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

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
