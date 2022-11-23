/*
 * UDP_Client.c
 *
 *  Created on: Nov 21, 2022
 *      Author: shachar-ubuntu
 */
#include "../../UUT/Inc/UDP_Client.h"
#include "../../UUT/Inc/MAIN_UUT.h"

/**@brief the variable which will hold the packet to be constructed after received by the Ethernet*/
pr_prtcl receivedPacketData = INIT_ALL_ZERO;

/**@brief the variable which will hold the packet to be constructed after received by the Ethernet*/
res_prtcl sentPacketData = INIT_ALL_ZERO;

/**@brief flag indicates the Ethernet packet received via UDP*/
uint8_t udp_packet_is_received = INIT_TO_ZERO;

/**@brief the protocol control block holding the MetaData of the packet*/
static struct udp_pcb *my_upcb = INIT_ALL_ZERO;

/**
* @fn 			void udp_recv_callback(void*, struct udp_pcb*, struct pbuf*, const ip_addr_t*, u16_t)
* @brief 		callback function when receiving an Ethernet packet via UDP Protocol
*
* @param arg	user supplied argument (udp_pcb.recv_arg)
* @param pcb	the udp_pcb which received the data
* @param p		the packet buffer that was received
* @param addr	the remote IP address from which the packet was received
* @param port	the remote port from which the packet was received
*/
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	/* Copy the data from the pbuf */
	memcpy((char*)&receivedPacketData, (char *)p->payload, p->len);

	udp_packet_is_received = PACKET_RECEIVED;

	/* Free receive pbuf */
	pbuf_free(p);
}

/**
 * @brief the data to send back with the UDP protocol
 * @param [in] pdata	 - pointer to the resultProtocol structure variable (sentPacketData)
 * 		 			 	   to send to the server via UDP
 * @param [in] data_size - the size of the data to send back to the server via UDP.
 */
void udpClient_send(res_prtcl *pdata, size_t data_size)
{
  /* allocate pbuf from pool*/
  struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT, data_size, PBUF_RAM);

  if (txBuf != NULL)
  {
    /* copy data to pbuf */
    pbuf_take(txBuf, (char*)pdata, data_size);

    /* send udp data */
    udp_send(my_upcb, txBuf);

    /* free pbuf */
    pbuf_free(txBuf);
  }
}

/**
 * @fn 		void UDP_Client_Init(void)
 * @brief	initialize a UDP connection
 */
void UDP_Client_Init(void)
{

	err_t err;

	/* 1. Create a new UDP control block  */
	my_upcb = udp_new();

	/* Bind the block to module's IP and port */
	ip_addr_t myIPaddr;
	CONVERTED_SRC_IP_ADDR(myIPaddr);
	udp_bind(my_upcb, &myIPaddr, SRC_PORT);


	/* configure destination IP address and port */
	ip_addr_t DestIPaddr;
	CONVERTED_DST_IP_ADDR(DestIPaddr);
	err= udp_connect(my_upcb, &DestIPaddr, DST_PORT);

	if (err == ERR_OK)
	{
		/* 2. Send message to server */
		/* the first data to send via UDP*/
		buildResProtocol(*(uint32_t*)"Test\r", *(uint8_t*)'\n');

		udpClient_send(&sentPacketData,sizeof(sentPacketData));

		/* 3. Set a receive callback for the upcb */
		udp_recv(my_upcb, udp_receive_callback, NULL);
	}
	else
	{
		udp_remove(my_upcb);
	}
}

/**
 * @brief build resultProtocol structure variable (sentPacketData) to send via UDP
 * @param [in] test_id 			- the test identifier.
 * @param [in] is_test_succeed 	- the result of the test 0x01 if the passed successfully, 0xff otherwise.
 */
void buildResProtocol(uint32_t test_id, uint8_t is_test_succeed)
{
	sentPacketData.testId = test_id;
	sentPacketData.testResult = is_test_succeed;
}
