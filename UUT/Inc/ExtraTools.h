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

/**@brief magic number indicate callback flag is set */
#define CALLBACK_FLAG_SET 	1

/**@brief magic number indicate callback flag is not set */
#define CALLBACK_FLAG_RESET 	0

/**@brief for checking if is ADC*/
#define IS_ADC	1

/**@brief for checking if is ADC*/
#define NOT_ADC 0
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

/**
 * @brief	wait status numbers for wait till flag set or timeout function.
 */
typedef enum WAIT_FLAG_STATUS {
	WAIT_STATUS_OK		=	(uint8_t)1, /**< WAIT_STATUS_OK */         /**< WAIT_STATUS_OK */
	WAIT_STATUS_TIMEOUT	=	(uint8_t)0,	/**< WAIT_STATUS_TIMEOUT *//**< WAIT_STATUS_TIMEOUT */
}WaitFlag_Status;
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

/**
 * @brief	general function for checking flag of some interrupt driven function in a given maximum waiting time.
 * @param dma_handle	[in]	the dma handle to check for finish flag
 * @param flag			[in]	the flag to check.
 * @param timeout		[in]	maximum waiting time (timeout) in case flag is not set.
 * @param dma_wait_time [in]	time for dma to wait to finish.
 * @param	isADC 		[in]	check if adc do not do need dma time wait.
 * @return	if all is ok flag is set and WAIT_STATUS_OK will be returned, otherwise timeout over
 * 			and WAIT_STATUS_TIMEOUT will be returned.
 */
WaitFlag_Status wait_till_flag_set_or_timeout(uint8_t isADC, DMA_HandleTypeDef *hdma, uint8_t* flag, uint32_t timeout, uint32_t dma_wait_time);
/* ************************************************************************************************************ */
#endif /* INC_EXTRATOOLS_H_ */
