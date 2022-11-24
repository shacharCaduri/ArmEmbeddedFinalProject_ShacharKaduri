#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "../../UUT/Inc/MAIN_UUT.h"
#include "string.h"

uint8_t local_master_buffer[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

uint8_t local_slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

uint8_t SPI_UUT_DMA( uint8_t *bit_pattern,  uint8_t bit_pattern_length, uint8_t iterations)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, local_slave_buffer, local_slave_buffer, bit_pattern_length);

		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, bit_pattern, local_master_buffer, bit_pattern_length);

		HAL_Delay(2);

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, local_slave_buffer, local_master_buffer, bit_pattern_length);

		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, local_master_buffer, local_master_buffer, bit_pattern_length);

		HAL_Delay(2);

		if(strcmp((char*)local_master_buffer, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			return TEST_FAILED;
		}

		--iterations;
	}

	return TEST_SUCCEED;
}
