#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0
#define PORT 58000
#define MAXLINE 1024
#define TEST_FAILED 0xff
#define TEST_SUCCEED 0x01
#define TEST_RECORDS_PATH "./Rec"
#define INIT_ALL_ZERO \
    {                 \
        0             \
    }

typedef struct test_result_protocol
{
    uint32_t TEST_ID;
    uint8_t test_result; // can be either 0x01 - SUCCEED or 0xff - FAILED
} res_prtcl;

/**
 * @name Driver code
 * @brief the main entry of the program.
 *
 */
int main()
{
    /************* Init *****************/
    int sockfd;
    // char buffer[MAXLINE];
    char hello[MAXLINE] = INIT_ALL_ZERO;
    struct sockaddr_in servaddr, cliaddr;
    res_prtcl resPrtcl = INIT_ALL_ZERO;
    /************************************/

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("listening on port %d...\r\n", PORT);
    uint32_t len;
    ssize_t n;
    int flag = 2;
    while (TRUE)
    {
        len = sizeof(cliaddr); // len is value/result 
        n = -1;
        n = recvfrom(sockfd, &resPrtcl, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        while (n < 0){}
        printf("Client said:\n\tTest ID: %u\n\tTest Result: %u,", resPrtcl.TEST_ID, resPrtcl.test_result);
        printf("enter msg to client: ");
        memset((char*)hello, 0, MAXLINE);
        scanf(" %s",hello);

        sendto(sockfd, (const char *)hello, strlen(hello),
                MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                len);
        printf("Hello message sent.\n");
        flag--;
    }

    close(sockfd);
    return 0;
}