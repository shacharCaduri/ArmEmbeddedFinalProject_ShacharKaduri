#ifndef SPI_H_SPI_H_SPI_H
#define SPI_H_SPI_H_SPI_H
#include "main.h"
#include "stm32f7xx_hal.h"
#include "../../UUT/Inc/ExtraTools.h"

/* ******************** Defines ********************************************************************* */
/**@brief 	the buffer (received data) size*/
#define MAX_SPI_SLAVE_BUFFER_SIZE 255

/**@brief 	the buffer (received data) size*/
#define MAX_SPI_MASTER_BUFFER_SIZE 255

/**@brief 	the address of the handle of the SPI device that transmit*/
#define SPI_MASTER &hspi1

/**@brief 	the address of the handle of the SPI device that receive*/
#define SPI_SLAVE &hspi4

/**
 * @brief	hale delay for spi when running number of iterations, thus the continuous
 * 		 	transmit and receive will have enough time to update the buffers.
 */
#define SPI_HAL_DELAY_2MS HAL_Delay(2);
/* ************************************************************************************************** */

/* ************************ Externs ***************************************************************** */
/**@brief the handle of SPI_SLAVE*/
extern SPI_HandleTypeDef hspi4;

/**@brief the handle of SPI_MASTER*/
extern SPI_HandleTypeDef hspi1;

/**@brief holding the data received back in master at the end of each iteration */
extern uint8_t master_buffer[MAX_SPI_MASTER_BUFFER_SIZE];

/**@brief static variable, holding the data received and sent back by the slave in each iteration */
extern uint8_t slave_buffer[MAX_SPI_SLAVE_BUFFER_SIZE];
/* ************************************************************************************************** */

/* *********************** Functions **************************************************************** */
t_status SPI_UUT_DMA(uint8_t *bit_pattern, uint8_t bit_pattern_length,
		uint8_t iterations);
/* ************************************************************************************************** */

#endif //SPI_H_SPI_H_SPI_H
