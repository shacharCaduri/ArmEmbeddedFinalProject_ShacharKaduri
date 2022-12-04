#include "../../UUT/Inc/ExtraTools.h"
#include <stdio.h>

/**
 * @brief hold test status for the test, this will be send
 * 		  back to the server to indicate the client test perf
 * 		  status. TEST_SUCCEED = 0x01 , TEST_FAILED = 0xff
 */
t_status test_status = INIT_TO_ZERO;

/**@brief used for printf from the the terminal that connected to the port of the USB redirect printf*/
int __io_putchar(int ch)
{
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

/**@brief used for printf from the the terminal that connected to the port of the USB redirect printf*/
int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)ptr, len, 0xFFFF);
	return len;
}

/**@brief used for scanf from the the terminal that connected to the port of the USB redirect scanf*/
int _read(int file, char *ptr, int len)
{
	int ch=0;
	HAL_UART_Receive(UART_DEBUG, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	if(ch==13)
	{
		ch=10;
		HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	}
	else if(ch==8)
	{
		ch=0x30;
		HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	}

	*ptr=ch;

	return 1;
}

/**
 * @brief 	print message to console in the PC connected via one of the UART ports.
 * 			print with a message number before.
 */
void print_msg(const uint8_t* msg)
{
	static size_t msg_number = 0;
	++msg_number;
	printf("%d) %s" ,msg_number,msg);

}

/**@brief	general function for checking flag of some interrupt driven function in a given maximum waiting time. */
WaitFlag_Status wait_till_flag_set_or_timeout(uint8_t* flag, uint32_t timeout, uint32_t dma_wait_time)
{
	uint32_t start = HAL_GetTick();

	while((*flag) != CALLBACK_FLAG_SET)
	{
		if((HAL_GetTick()-start) > timeout)
			return WAIT_STATUS_TIMEOUT;
	}

	/* reset the flag */
	*flag = CALLBACK_FLAG_RESET;

	/* ********** waiting for dma to finish **************** */
	HAL_Delay(dma_wait_time);
	/* ***************************************************** */

	return WAIT_STATUS_OK;
}
