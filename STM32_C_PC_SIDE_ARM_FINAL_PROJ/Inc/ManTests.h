#ifndef BE633414_4091_4AE7_A0EB_663DE2DBE90C
#define BE633414_4091_4AE7_A0EB_663DE2DBE90C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <time.h>

#include "../Inc/Defines.h"
#include "../Inc/ProtocolStructurs.h"
#include "../Inc/ReadWriteRecords.h"
#include "../Inc/TestsGlobals.h"

/** @brief wait until bytes receieved via the ethernet connected to the board and check first connection with client */
void mantests_wait_till_recv_bytes(ssize_t n_bytes_read, uint32_t *len, 
int *is_client_response, struct sockaddr_in *cliaddr, struct timespec *end, int sockfd,
 res_prtcl *resPrtcl, struct timespec *start);

/** @brief the scanf to input parameters to test protocol to send to the the board */
void input_Protocol(pr_prtcl *test_protocol);

/** @brief send the test protocol to the board via ethernet */
void mantests_send_protocol(struct timespec *start, pr_prtcl *test_protocol, struct sockaddr_in *cliaddr, uint32_t len, int sockfd);

/**
 * @brief ask the users if want to continue manual tests or return to main menu.
 * @return return 1 - CONTI_MAN_TESTS if the user want to contiue, 0 - DONOT_CONTI_MAN_TESTS otherwise.
*/
uint8_t ask_user_to_continue_man_tests();

/** @brief manual tests until user hits he does not want to conitue */
void manual_tests();
#endif /* BE633414_4091_4AE7_A0EB_663DE2DBE90C */
