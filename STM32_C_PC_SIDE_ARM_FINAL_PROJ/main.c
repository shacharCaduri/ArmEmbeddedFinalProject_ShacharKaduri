#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define TRUE                            1
#define PORT                            58000
#define TEST_FAILED                     0xff
#define TEST_SUCCEED                    0x01
#define TEST_RECORDS_PATH               "./Rec"
#define INIT_ALL_ZERO                   {0}
#define INIT_TO_ZERO                    0
#define MAX_BIT_PATTERN_LEN             255
#define FILE_DESC_NON_VALID_VAL         -1
#define AUTO_PRTCL_VAL                  0
#define BIND_FUNC_NON_VALI_VAL          -1
#define RECV_FUNC_RET_MIN_VAL           0
#define CONNECTION_ESTABSLISHED         0
#define CLIENT_RESPONDED_FIRST_TIME_OK  1

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
typedef struct proprietary_protocol
{
    uint32_t testId;
    uint8_t perfToTest;
    uint8_t iterations;
    uint8_t bitPatrnStrLen;
    char bitPatrnStr[MAX_BIT_PATTERN_LEN];
} pr_prtcl;

/**
 * @struct result_protocol
 * @brief  1) testId - a number given to the test so it'll be easy
 * 		   to map it to the later on test result.
 *
 *		   2) testResult - bitfield:  1 – test succeeded, 0xff –test
 *		   failed.
 */
typedef struct result_protocol
{
    uint32_t testId;
    uint8_t testResult;
} res_prtcl;
/**@brief resets the alignment to be as before the pragma pack 1*/
#pragma pack()
/* *********************************************************************************************************** */

/**
 * @name Driver code
 * @brief the main entry of the program.
 *
 */
int main()
{
    /************* Init & Defs *****************/
    int sockfd = INIT_TO_ZERO;
    pr_prtcl test_protocol = INIT_ALL_ZERO;
    struct sockaddr_in servaddr, cliaddr;
    res_prtcl resPrtcl = INIT_ALL_ZERO;
    uint32_t len = INIT_TO_ZERO;
    ssize_t n = INIT_TO_ZERO;
    int res = INIT_TO_ZERO; // for checking scanf results;
    int is_client_response = CLIENT_RESPONDED_FIRST_TIME_OK;
    /*******************************************/

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, AUTO_PRTCL_VAL)) <= FILE_DESC_NON_VALID_VAL)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, INIT_TO_ZERO, sizeof(servaddr));
    memset(&cliaddr, INIT_TO_ZERO, sizeof(cliaddr));

    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) <= BIND_FUNC_NON_VALI_VAL)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("listening on port %d...\r\n", PORT);
    is_client_response = CONNECTION_ESTABSLISHED;
    while (TRUE)
    {
        len = sizeof(cliaddr); // len is value/result 
        n = RECV_FUNC_RET_MIN_VAL;
        do
        {
            n = recvfrom(sockfd, &resPrtcl, sizeof(resPrtcl),
                         MSG_WAITALL, (struct sockaddr *)&cliaddr,
                         &len);
        } while (n < RECV_FUNC_RET_MIN_VAL);
        if(is_client_response == CONNECTION_ESTABSLISHED)
        {
            printf("first connection with client established.\r\n");
            is_client_response = CLIENT_RESPONDED_FIRST_TIME_OK;
        }

        printf("Client said:\n\tTest ID: %u\n\tTest Result: %u\n", resPrtcl.testId, resPrtcl.testResult);
        printf("enter test parameters: ");
        memset(&test_protocol, INIT_TO_ZERO, sizeof(test_protocol));
        res = scanf("%" SCNu32 "", &test_protocol.testId);
        /* ending the program */
        if (res == EOF)
            break;
        res = scanf("%" SCNu8 "", &test_protocol.perfToTest);
        /* ending the program */
        if (res == EOF)
            break;
        res = scanf("%" SCNu8 "", &test_protocol.iterations);
        /* ending the program */
        if (res == EOF)
            break;
        res = scanf("%" SCNu8 "", &test_protocol.bitPatrnStrLen);
        /* ending the program */
        if (res == EOF)
            break;
        res = scanf("%s", test_protocol.bitPatrnStr);
        /* ending the program */
        if (res == EOF)
            break;

        sendto(sockfd, (const pr_prtcl *)&test_protocol, sizeof(test_protocol),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
               len);

        printf("test protocol sent.\n");
    }

    close(sockfd);
    return 0;
}