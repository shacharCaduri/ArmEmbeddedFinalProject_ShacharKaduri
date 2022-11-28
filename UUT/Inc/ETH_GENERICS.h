/*
 * ETH_GENERICS.h
 *
 *  Created on: Nov 22, 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_ETH_GENERICS_H_
#define INC_ETH_GENERICS_H_
#include <lwip.h>
#include <udp.h>
#include "../../UUT/Inc/ExtraTools.h"

/* *********************** Defines *************************************************************************** */
/**@brief define for the address of the generic data structure(linked list) holding all network interfaces*/
#define GNETIF_ADDR &gnetif

/**@brief define for the source port number of the device to be bind to*/
#define SRC_PORT 52000

/**@brief define for the destination port number of the device to connect to*/
#define DST_PORT 58000

/**@brief define, pasting the macro which converting the IP address to the ip_addr_t struct (uint32_t number)*/
#define CONVERTED_SRC_IP_ADDR(SRCIPADDRSTRUCT) IP_ADDR4(&((SRCIPADDRSTRUCT)), 192, 168, 1, 2)

/**@brief define, pasting the macro which converting the IP address to the ip_addr_t struct (uint32_t number)*/
#define CONVERTED_DST_IP_ADDR(DSTIPADDRSTRUCT) IP_ADDR4(&((DSTIPADDRSTRUCT)), 192, 168, 1, 1)

/**@brief indicate a true value for if packet received flag*/
#define PACKET_RECEIVED 1

/**@brief indicate a false value for if packet received flag*/
#define PACKET_NOT_RECEIVED 0

///**@brief defines the max rx buffer possible size */
//#define MAX_RX_BUFFER_SIZE 262
/* *********************************************************************************************************** */

/* ************************************ Externs ************************************************************** */
/**@brief Generic data structure(linked list) used for all lwIP network interfaces.*/
extern struct netif gnetif;
/* ************************************************************************************************************* */

#endif /* INC_ETH_GENERICS_H_ */
