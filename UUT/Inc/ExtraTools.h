/*
 * printf_redefenition.h
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_EXTRATOOLS_H_
#define INC_EXTRATOOLS_H_
#include "main.h"
#include "stm32f7xx_hal.h"

/**@brief the UART handle which is connected through the USB.*/
extern UART_HandleTypeDef huart3;

/**@brief define the handle UART pointer to be used as UART_DEBUG which is the connected through the USB.*/
#define UART_DEBUG &huart3

/**
 * @brief 	print message to console in the PC connected via one of the UART ports.
 * 			print with a message number before.
 */
void print_msg(const uint8_t* msg);

#endif /* INC_EXTRATOOLS_H_ */
