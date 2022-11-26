#include "../../UUT/Inc/MAIN_UUT.h"

/**
 * @brief hold test status for the test, this will be send
 * back to the server to indicate the client test perf status
 */
uint8_t test_status = INIT_TO_ZERO;

/**@brief the main function to run the tests, the life of the program*/
void UUT_main(void)
{

	/* ******* INIT PHASE ******* */
	UDP_Client_Init();
	/* ******************** */

	/* ******* LIFE LOOP ******* */
	while(TRUE)
	{
		/**
		 * @brief 	function that should be called when the Ethernet interface identify a coming packet
		 * 			because this client need to constantly receives some packets to tell it to do some tests
		 * 			its inside the while(TRUE), e.g. life loop.
		 */
		ethernetif_input(GNETIF_ADDR);
		sys_check_timeouts();
		if(udp_packet_is_received == PACKET_RECEIVED)
		{
			test_status = (UART_DMA_UUT((uint8_t*)"ShacharIsTheKing\r\n", 18,5));
			test_status = (I2C_UUT_DMA((uint8_t*)"ShacharIsTheKing\r\n", 18,5));
			test_status = (SPI_UUT_DMA((uint8_t*)"ShacharIsTheKing\r\n", 18,5));

			test_status = TIMER_UUT(/*7199,9999,*/2);
			buildResProtocol(*(uint32_t*)"1523\n", TEST_SUCCEED);
			udpClient_send(&sentPacketData,sizeof(sentPacketData));
			udp_packet_is_received = PACKET_NOT_RECEIVED;
		}
	}
	/* ************************* */
}
