#include "../../UUT/Inc/MAIN_UUT.h"

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
