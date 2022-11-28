#include "../../UUT/Inc/MAIN_UUT.h"

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
			switch(receivedPacketData.perfToTest)
			{
			case UART_PERIPHERAL:
			{
				test_status = UART_UUT_DMA((uint8_t *)receivedPacketData.bitPatrnStr, receivedPacketData.bitPatrnStrLen, receivedPacketData.iterations);
			}
			break;
			case I2C_PERIPHERAL:
			{
				test_status = I2C_UUT_DMA((uint8_t *)receivedPacketData.bitPatrnStr, receivedPacketData.bitPatrnStrLen, receivedPacketData.iterations);
			}
			break;
			case SPI_PERIPHERAL:
			{
				test_status = SPI_UUT_DMA((uint8_t *)receivedPacketData.bitPatrnStr, receivedPacketData.bitPatrnStrLen, receivedPacketData.iterations);
			}
			break;
			case TIMER_PERIPHERAL:
			{
				test_status = TIMER_UUT(receivedPacketData.iterations);
			}
			break;
			case ADC_PERIPHERAL:
			{
				test_status = ADC_UUT_DMA(receivedPacketData.iterations);
			}
			break;
			default:
			{
				/* no other protocol or peripheral defined */
				test_status = TEST_FAILED;
			}
			break;
			}

			/* building the result protocol struct with data: testId and status of the test */
			buildResProtocol(receivedPacketData.testId, test_status);

			/* send via UDP the packet to the server */
			udpClient_send(&sentPacketData,sizeof(sentPacketData));

			/* initializing the flag of packet received to be not received so only when a packet will be received some test will be performed */
			udp_packet_is_received = PACKET_NOT_RECEIVED;
		}
	}
	/* ************************* */
}
