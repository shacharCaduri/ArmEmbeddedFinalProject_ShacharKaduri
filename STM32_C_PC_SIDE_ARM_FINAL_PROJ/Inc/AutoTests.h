#ifndef A11FB89A_B7BE_4DAA_A117_52EC3335B628
#define A11FB89A_B7BE_4DAA_A117_52EC3335B628

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
void autotests_wait_till_recv_bytes(ssize_t n_bytes_read, uint32_t *len, 
int *is_client_response, struct sockaddr_in *cliaddr, struct timespec *end, int sockfd,
 res_prtcl *resPrtcl, struct timespec *start);

/** @brief send the test protocol to the board via ethernet */
void autotests_send_protocol(struct timespec *start, pr_prtcl *test_protocol, 
struct sockaddr_in *cliaddr, uint32_t len, int sockfd, int is_client_response);

/** 
 * @brief get the tests to be done from dedicated file, put the data into an array of pr_prctl 
 *        structs which will be sent to the board for tests
 */
void get_tests_to_do(pr_prtcl **test_protocols, size_t n_of_tests);

/**
 * @brief check how many tests there is to do.
 * @return number of tests to do.
*/
size_t ret_num_of_tests_to_do();

/** @brief automatic tests until finished all predefined tests in the file tests_to_do.json */
void automatic_tests();

#endif /* A11FB89A_B7BE_4DAA_A117_52EC3335B628 */
