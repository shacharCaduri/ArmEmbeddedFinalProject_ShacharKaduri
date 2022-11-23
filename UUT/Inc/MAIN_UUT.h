#ifndef MAIN_UUT_H_MAIN_UUT_H_MAIN_UUT_H
#define MAIN_UUT_H_MAIN_UUT_H_MAIN_UUT_H

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../UUT/Inc/ExtraTools.h"
#include "../../UUT/Inc/I2C_DMA_UUT.h"
#include "../../UUT/Inc/SPI_DMA_UUT.h"
#include "../../UUT/Inc/TIMER_UUT.h"
#include "../../UUT/Inc/UART_DMA_UUT.h"
#include "../../UUT/Inc/UDP_Client.h"

/* ******************** Defines ****************************************************************************** */
/**@brief define for the while life loop , TRUE means it will run forever(hence life loop).*/
#define TRUE 1

/**@brief define for the magic number for if test passed successfully*/
#define TEST_SUCCEED 0x01

/**@brief define for the magic number for if test failed to pass*/
#define TEST_FAILED  0xff

/**@brief the value for the protocol variable which considered as no protocol defined.*/
#define NO_PROTOCOL 0

/**@brief the value for the protocol variable which considered as UART protocol defined.*/
#define UART_PROTOCOL 1

/**@brief the value for the protocol variable which considered as I2C protocol defined.*/
#define I2C_PROTOCOL 2

/**@brief the value for the protocol variable which considered as SPI protocol defined.*/
#define SPI_PROTOCOL 3

/**@brief magic number to check strcmp equals*/
#define STRCMP_EQUALS 0
/* *********************************************************************************************************** */

/* ******************************* Externs ******************************************************************* */
/**
 * @brief hold test status for the test, this will be send
 * 		  back to the server to indicate the client test perf
 * 		  status.
 */
extern uint8_t test_status;
/* *********************************************************************************************************** */

/* ************************************ Functions ************************************************************** */
/**@brief the main function to run the tests, the life of the program*/
void UUT_main(void);
/* ************************************************************************************************************* */

#endif //MAIN_UUT_H_MAIN_UUT_H_MAIN_UUT_H
