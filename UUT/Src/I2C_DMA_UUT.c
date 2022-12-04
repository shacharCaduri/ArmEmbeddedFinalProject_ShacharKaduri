#include "../../UUT/Inc/I2C_DMA_UUT.h"
#include <string.h>


/**@brief buffer for slave device for receiving data */
uint8_t i2c_buffer_slave[MAX_I2C_SLAVE_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief buffer for master device for receiving data */
uint8_t i2c_buffer_master[MAX_I2C_MASTER_BUFFER_SIZE] = INIT_ALL_ZERO;

/**@brief i2c master callback flag indicate receive completed */
static uint8_t i2c_master_rcv_callback_flag = CALLBACK_FLAG_RESET;

/**@brief i2c slave callback flag indicate receive completed */
static uint8_t i2c_slave_rcv_callback_flag = CALLBACK_FLAG_RESET;


/**@brief  Master Rx Transfer completed callback. */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C_MASTER->Instance)
	{
		i2c_master_rcv_callback_flag = CALLBACK_FLAG_SET;
	}
}

/**@brief  Slave Rx Transfer completed callback.  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C_SLAVE->Instance)
	{
		i2c_slave_rcv_callback_flag = CALLBACK_FLAG_SET;
	}
}

/**
 * @fn 		t_status UART_DMA_UUT(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
 * @brief	the I2C under unit test, tests if bit pattern equals to the same data received after
 * 			completing a communication cycle (data sent as follows: Master -> Slave -> Master)
 */
t_status I2C_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length, uint8_t iterations)
{
	/* check status of receive transmit, error detection. */
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{
		/* Master -> Slave */
		status = HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, i2c_buffer_slave, bit_pattern_length);

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

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(&i2c_slave_rcv_callback_flag, I2C_TIMEOUT, I2C_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		/* Slave -> Master */
		status = HAL_I2C_Master_Receive_DMA(I2C_MASTER, I2C_SLAVE_ADDRESS, i2c_buffer_master, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE, i2c_buffer_slave, bit_pattern_length);

		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		/* end commands Slave -> Master */

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(&i2c_master_rcv_callback_flag, I2C_TIMEOUT, I2C_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		/* compare the data results at the end of communication with data given by the functions parameters */
		if(strcmp((char*)i2c_buffer_master, (char*)bit_pattern)!=STRCMP_EQUALS)
		{
			/* test did not pass, test failed */
			return TEST_FAILED;
		}

		--iterations;
	}

	/* test passed successfuly*/
	return TEST_SUCCEED;
}
