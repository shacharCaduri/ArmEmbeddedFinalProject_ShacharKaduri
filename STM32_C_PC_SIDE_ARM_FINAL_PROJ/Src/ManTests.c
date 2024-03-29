#include "../Inc/ManTests.h"

/** @brief manual tests until user hits he does not want to conitue */
void manual_tests()
{    
    /************* Init & Defs *****************/
    int sockfd = INIT_TO_ZERO;
    struct timespec start;
    struct timespec end;
    pr_prtcl test_protocol = INIT_ALL_ZERO;
    struct sockaddr_in servaddr, cliaddr;
    res_prtcl resPrtcl = INIT_ALL_ZERO;
    uint32_t len = INIT_TO_ZERO;
    ssize_t n_bytes_read = INIT_TO_ZERO;
    int is_client_response = CLIENT_CANNOT_CONNECT;
    TestID = ret_last_test_id();
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
    
    while(TRUE)
    {
        mantests_wait_till_recv_bytes(n_bytes_read,&len,&is_client_response, &cliaddr,&end,sockfd,&resPrtcl,&start);

        if ((is_client_response == CLIENT_RESPONDED_FIRST_TIME_OK) &&
            (ask_user_to_continue_man_tests() == DONOT_CONTI_MAN_TESTS))
        {
            break;
        }

        if (is_client_response == CONNECTION_ESTABSLISHED)
        {
            printf("first connection with client established.\n");
            is_client_response = CLIENT_RESPONDED_FIRST_TIME_OK;
        }

        input_Protocol(&test_protocol);

        mantests_send_protocol(&start, &test_protocol, &cliaddr, len, sockfd);

    }
    
    close(sockfd);
}

/** @brief send the test protocol to the board via ethernet */
void mantests_send_protocol(struct timespec *start, pr_prtcl *test_protocol, struct sockaddr_in *cliaddr, uint32_t len, int sockfd)
{
    clock_gettime(CLOCK_MONOTONIC,start);
    sendto(sockfd, (const pr_prtcl *)test_protocol, sizeof(*test_protocol),
            MSG_CONFIRM, (const struct sockaddr *)cliaddr,
            len);

    printf("test protocol sent.\n");
}

/** @brief wait until bytes receieved via the ethernet connected to the board and check first connection with client */
void mantests_wait_till_recv_bytes(ssize_t n_bytes_read, uint32_t *len, 
int *is_client_response, struct sockaddr_in *cliaddr, struct timespec *end, int sockfd,
 res_prtcl *resPrtcl, struct timespec *start)
{
    *len = sizeof(*cliaddr); // len is value/result 
    n_bytes_read = RECV_FUNC_RET_MIN_VAL;
    do
    {
        n_bytes_read = recvfrom(sockfd, resPrtcl, sizeof(*resPrtcl),
                                MSG_WAITALL, (struct sockaddr *)cliaddr,
                                len);
    } while (n_bytes_read < RECV_FUNC_RET_MIN_VAL);

    if(*is_client_response == CLIENT_RESPONDED_FIRST_TIME_OK)
    {
        clock_gettime(CLOCK_MONOTONIC, end);
        /* time in nano seconds turn into seconds */
        const double test_duration = ((double)(end->tv_sec) + (double)(end->tv_nsec)/TEN_POW_NINE) - ((double)(start->tv_sec) + (double)(start->tv_nsec)/TEN_POW_NINE);
        write_rec(test_duration,resPrtcl);
    }

    printf("Client said:\n\tTest ID: %u\n\tTest Result: %u\n", resPrtcl->testId, resPrtcl->testResult);

}

/** @brief the scanf to input parameters to test protocol to send to the the board */
void input_Protocol(pr_prtcl *test_protocol)
{    
    printf("enter test parameters: ");
    memset(test_protocol, INIT_TO_ZERO, sizeof(*test_protocol));
    
    test_protocol->testId = TestID;
    TestID++;
    update_last_test_id_file(TestID);

    printf("enter peripheral to test:\n[1-Timer,2-UART,4-SPI,8-I2C,16-ADC]\n");
    scanf("%" SCNu8 "", &test_protocol->perfToTest);


    printf("enter number of times to do the test:\n");
    scanf("%" SCNu8 "", &test_protocol->iterations);

    printf("enter the length of the string to be sent:\n");
    scanf("%" SCNu8 "", &test_protocol->bitPatrnStrLen);

    printf("enter some string to test communication peripherals on,"
    "and based on the length you wrote:\n");
    scanf("%s", test_protocol->bitPatrnStr);
}

/**
 * @brief ask the users if want to continue manual tests or return to main menu.
 * @return return 1 - CONTI_MAN_TESTS if the user want to contiue, 0 - DONOT_CONTI_MAN_TESTS otherwise.
*/
uint8_t ask_user_to_continue_man_tests()
{
    uint8_t answer = INIT_TO_ZERO;
    printf("do you want to continue manual tests:\n");
    printf("1) Yes\n2) No\n[hit the number before the choice to choose option you want]\n");
    while (TRUE)
    {
        scanf("%" SCNu8 "", &answer);
        if (answer == DONOT_CONTI_MAN_TESTS || answer == CONTI_MAN_TESTS)
        {
            break;
        }
    }

    return answer;
}