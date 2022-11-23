#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "../../UUT/Inc/MAIN_UUT.h"
#include "string.h"

uint8_t SPI_UUT_DMA(const uint8_t *bit_pattern, const uint8_t bit_pattern_length)
{
	uint8_t local_master_buffer[MAX_SPI_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;
	uint8_t local_slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

	HAL_StatusTypeDef status = HAL_ERROR;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	status = HAL_SPI_Receive_DMA(SPI_SLAVE, local_slave_buffer, bit_pattern_length);
	if(status != HAL_OK)
	{
		return TEST_FAILED;
	}

	status = HAL_SPI_Transmit_DMA(SPI_MASTER, (uint8_t *)bit_pattern, bit_pattern_length);
	if(status != HAL_OK)
	{
		return TEST_FAILED;
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	status = HAL_SPI_Receive_DMA(SPI_MASTER, local_master_buffer, bit_pattern_length);
	if(status != HAL_OK)
	{
		return TEST_FAILED;
	}

	status = HAL_SPI_Transmit_DMA(SPI_SLAVE, local_slave_buffer, bit_pattern_length);
	if(status != HAL_OK)
	{
		return TEST_FAILED;
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	if(strcmp((char*)local_master_buffer, (char*)bit_pattern)==STRCMP_EQUALS)
	{
		return TEST_SUCCEED;
	}

	return TEST_FAILED;
}
