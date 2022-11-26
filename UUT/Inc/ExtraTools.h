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

/* ******************** Defines ****************************************************************************** */
/**@brief define for the while life loop , TRUE means it will run forever(hence life loop).*/
#define TRUE 1

/**@brief magic number to initiate pointers/arrays with the {0}.*/
#define INIT_ALL_ZERO {0}

/**@brief magic number to initiate variable's values with 0.*/
#define INIT_TO_ZERO 0

/**@brief magic number to check strcmp equals*/
#define STRCMP_EQUALS 0

/**@brief the first test id to be sent by this client when first transmitting for checking occur*/
#define FIRST_TEST_ID 0x0000

/**@brief define the handle UART pointer to be used as UART_DEBUG which is the connected through the USB.*/
#define UART_DEBUG &huart3
/* *********************************************************************************************************** */

/* ******************************* Structures Enumurators Typedef  ******************************************* */
typedef enum TEST_STATUS { TEST_SUCCEED = (uint8_t)0x01, TEST_FAILED = (uint8_t)0xff} t_status;

/**
 * @brief	values for tested peripherals, using names instead of numbers in code,
 * 			because they are magic numbers.
 */
typedef enum TESTED_PERIPHERAL {
	NO_PERIPHERAL		=	(uint8_t)0,	/**< NO_PERIPHERAL */
	TIMER_PERIPHERAL	=	(uint8_t)1, /**< TIMER_PERIPHERAL */
	UART_PERIPHERAL		=	(uint8_t)2, /**< UART_PROTOCOL */
	SPI_PERIPHERAL		=	(uint8_t)4, /**< SPI_PROTOCOL */
	I2C_PERIPHERAL		=	(uint8_t)8, /**< I2C_PROTOCOL */
	ADC_PERIPHERAL		=	(uint8_t)16 /**< ADC_PERIPHERAL */
}t_perf;
/* *********************************************************************************************************** */

/* ******************************* Externs ******************************************************************* */
/**
 * @brief hold test status for the test, this will be send
 * 		  back to the server to indicate the client test perf
 * 		  status. TEST_SUCCEED = 0x01 , TEST_FAILED = 0xff
 */
extern t_status test_status;

/**@brief the UART handle which is connected through the USB.*/
extern UART_HandleTypeDef huart3;
/* *********************************************************************************************************** */

/* ******************************** Functions **************************************************************** */
/**
 * @brief 	print message to console in the PC connected via one of the UART ports.
 * 			print with a message number before.
 */
void print_msg(const uint8_t* msg);
/* ************************************************************************************************************ */
#endif /* INC_EXTRATOOLS_H_ */
