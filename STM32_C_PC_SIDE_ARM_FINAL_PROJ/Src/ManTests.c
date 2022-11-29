#include "../Inc/ManTests.h"


void manual_tests()
{    
    /************* Init & Defs *****************/
    int sockfd = INIT_TO_ZERO;
    struct timespec start;
    struct timespec end;
    double test_duration;
    pr_prtcl test_protocol = INIT_ALL_ZERO;
    struct sockaddr_in servaddr, cliaddr;
    res_prtcl resPrtcl = INIT_ALL_ZERO;
    uint32_t len = INIT_TO_ZERO;
    ssize_t n = INIT_TO_ZERO;
    int is_client_response = CLIENT_CANNOT_CONNECT;
    int res = INIT_TO_ZERO; // for checking scanf results;
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
        len = sizeof(cliaddr); // len is value/result 
        n = RECV_FUNC_RET_MIN_VAL;
        do
        {
            n = recvfrom(sockfd, &resPrtcl, sizeof(resPrtcl),
                            MSG_WAITALL, (struct sockaddr *)&cliaddr,
                            &len);
        } while (n < RECV_FUNC_RET_MIN_VAL);


        if(is_client_response == CLIENT_RESPONDED_FIRST_TIME_OK)
        {
            clock_gettime(CLOCK_MONOTONIC, &end);
            /* time in nano seconds turn into seconds */
            test_duration = ((double)(end.tv_sec) + (double)(end.tv_nsec)/TEN_POW_NINE) - ((double)(start.tv_sec) + (double)(start.tv_nsec)/TEN_POW_NINE);
            write_rec(test_duration,&resPrtcl);
        }
        
        if(is_client_response == CONNECTION_ESTABSLISHED)
        {
            printf("first connection with client established.\r\n");
            is_client_response = CLIENT_RESPONDED_FIRST_TIME_OK;
        }

        printf("Client said:\n\tTest ID: %u\n\tTest Result: %u\n", resPrtcl.testId, resPrtcl.testResult);
        printf("enter test parameters: ");
        memset(&test_protocol, INIT_TO_ZERO, sizeof(test_protocol));
        
        test_protocol.testId = TestID;
        update_last_test_id_file(TestID);
        TestID++;

        printf("enter peripheral to test:\n[1-Timer,2-UART,4-SPI,8-I2C,16-ADC]\n");
        res = scanf("%" SCNu8 "", &test_protocol.perfToTest);
        /* ending the function */
        if (res == RET_TO_MENU)
            break;

        printf("enter number of times to do the test:\n");
        res = scanf("%" SCNu8 "", &test_protocol.iterations);
        /* ending the function */
        if (res == RET_TO_MENU)
            break;

        printf("enter the length of the string to be sent:\n");
        res = scanf("%" SCNu8 "", &test_protocol.bitPatrnStrLen);
        /* ending the function */
        if (res == RET_TO_MENU)
            break;

        printf("enter some string to test communication peripherals on,"
        "and based on the length you wrote:\n");
        res = scanf("%s", test_protocol.bitPatrnStr);
        /* ending the function */
        if (res == RET_TO_MENU)
            break;

        clock_gettime(CLOCK_MONOTONIC,&start);
        sendto(sockfd, (const pr_prtcl *)&test_protocol, sizeof(test_protocol),
                MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                len);

        printf("test protocol sent.\n");
    }
    
    close(sockfd);
}