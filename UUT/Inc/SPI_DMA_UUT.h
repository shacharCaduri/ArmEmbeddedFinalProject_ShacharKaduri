#ifndef SPI_H_SPI_H_SPI_H
#define SPI_H_SPI_H_SPI_H
#include "main.h"
#include "stm32f7xx_hal.h"

/**@brief the buffer (received data) size*/
#define MAX_SPI_SLAVE_BUFFER_SIZE 255

/**@brief the buffer (received data) size*/
#define MAX_SPI_MASTER_BUFFER_SIZE 255

/**@brief the address of the handle of the SPI device that transmit*/
#define SPI_MASTER &hspi1

/**@brief the address of the handle of the SPI device that receive*/
#define SPI_SLAVE &hspi4

/**@brief the handle of SPI_MASTER*/
extern SPI_HandleTypeDef hspi1;

/**@brief the handle of SPI_SLAVE*/
extern SPI_HandleTypeDef hspi4;

uint8_t SPI_UUT_DMA(const uint8_t *bit_pattern, const uint8_t bit_pattern_length);

#endif //SPI_H_SPI_H_SPI_H
