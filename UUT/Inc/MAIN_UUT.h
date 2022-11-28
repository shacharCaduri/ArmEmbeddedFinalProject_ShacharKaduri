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
#include "../../UUT/Inc/ADC_DMA_UUT.h"

/* ******************************** Main Function ************************************************************** */
/**@brief the main function to run the tests, the life of the program*/
void UUT_main(void);
/* ************************************************************************************************************* */

#endif //MAIN_UUT_H_MAIN_UUT_H_MAIN_UUT_H
