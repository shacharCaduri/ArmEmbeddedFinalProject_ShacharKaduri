/*
 * UDP_Client.h
 *
 *  Created on: Nov 21, 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_UDP_CLIENT_H_
#define INC_UDP_CLIENT_H_
#include "main.h"
#include "lwip.h"
#include "udp.h"
#include "string.h"
#include "../../UUT/Inc/ETH_GENERICS.h"
#include "../../UUT/Inc/ExtraTools.h"

/* ******************** Defines ****************************************************************************** */
/**
 * @brief the maximum size the bit pattern string can be
 * (bit pattern length defined as maximum 1Byte in size so 2^8-1=255)
 */
#define MAX_BIT_PATTERN_SIZE 255
/* *********************************************************************************************************** */

/* ******************** Structures *************************************************************************** */
/**
 * @brief set the alignment of the 2 structures below to be 1 byte, thus,
 * 		  padding will not occur.
 */
#pragma pack(1)
/**
 * @struct proprietary_protocol
 * @brief  1) testId - a number given to the
 * 		   test so it will be easy to map it to
 * 		   the later on test result.
 *
 * 		   2) pefToTest - a bitfield for the peripheral being
 * 		   tested: 1 –Timer, 2 – UART, SPI – 4, I2C – 8,
 * 		   ADC – 16.
 *
 * 		   3) iterations - the number of iterations the test
 * 		   should run at the UUT (Unit Under Test).
 *
 * 		   4) bitPatrnStrLen - the actual size of the Bit pattern
 * 		   string sent to UUT.
 *
 * 		   5) bitPatrnStr - the actual string of characters
 * 		   sent to the UUT
 */
typedef struct proprietary_protocol {
	uint32_t testId;
	uint8_t perfToTest;
	uint8_t iterations;
	uint8_t bitPatrnStrLen;
	char 	bitPatrnStr[MAX_BIT_PATTERN_SIZE];
}pr_prtcl;


/**
 * @struct result_protocol
 * @brief  1) testId - a number given to the test so it'll be easy
 * 		   to map it to the later on test result.
 *
 *		   2) testResult - bitfield:  1 – test succeeded, 0xff –test
 *		   failed.
 */
typedef struct result_protocol {
	uint32_t testId;
	uint8_t testResult;
}res_prtcl;
/**@brief resets the alignment to be as before the pragma pack 1*/
#pragma pack()
/* *********************************************************************************************************** */

/* ************************************ Externs ************************************************************** */
/**@brief flag indicates the Ethernet packet received via UDP*/
extern uint8_t udp_packet_is_received;

/**@brief the structure which will be sent as data in the Ethernet packet.*/
extern res_prtcl sentPacketData;

/**@brief the variable which will hold the packet to be constructed after received by the Ethernet*/
extern pr_prtcl receivedPacketData;
/* ************************************************************************************************************* */

/* ************************************ Functions ************************************************************** */
/**
 * @fn 		void UDP_Client_Init(voiMAIN_UUTd)
 * @brief	initialize a UDP connection
 */
void UDP_Client_Init(void);

/**
 * @brief the data to send back with the UDP protocol
 * @param [in] pdata	 - pointer to the resultProtocol structure variable (sentPacketData)
 * 		 			 	   to send to the server via UDP
 * @param [in] data_size - the size of the data to send back to the server via UDP.
 */
void udpClient_send(res_prtcl *pdata, size_t data_size);

/**
 * @brief build resultProtocol structure variable (sentPacketData) to send via UDP
 * @param [in] test_id 			- the test identifier.
 * @param [in] is_test_succeed 	- the result of the test, TEST_SUCCEED 0x01 if the passed successfully, TEST_FAILED 0xff otherwise.
 */
void buildResProtocol(uint32_t test_id, t_status is_test_succeed);
/* ************************************************************************************************************* */

#endif /* INC_UDP_CLIENT_H_ */
