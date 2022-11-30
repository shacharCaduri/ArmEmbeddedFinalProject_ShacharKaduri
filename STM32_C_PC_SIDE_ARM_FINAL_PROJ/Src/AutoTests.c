#include "../Inc/AutoTests.h"


/** @brief automatic tests until finished all predefined tests in the file tests_to_do.json */
void automatic_tests()
{    
    /************* Init & Defs *****************/
    int sockfd = INIT_TO_ZERO;
    struct timespec start;
    struct timespec end;
    pr_prtcl *test_protocols_arr = INIT_ALL_ZERO;
    struct sockaddr_in servaddr, cliaddr;
    res_prtcl resPrtcl = INIT_ALL_ZERO;
    uint32_t len = INIT_TO_ZERO;
    ssize_t n_bytes_read = INIT_TO_ZERO;
    int is_client_response = CLIENT_CANNOT_CONNECT;
    TestID = ret_last_test_id();
    size_t n_tests = INIT_TO_ZERO;
    size_t test_index = INIT_TO_ZERO;
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
    
    n_tests = ret_num_of_tests_to_do();
    get_tests_to_do(&test_protocols_arr, n_tests);

    while(test_index  < n_tests)
    {
        autotests_wait_till_recv_bytes(n_bytes_read,&len,&is_client_response, &cliaddr,&end,sockfd,&resPrtcl,&start);

        if (is_client_response == CONNECTION_ESTABSLISHED)
        {
            printf("first connection with client established.\n");
            is_client_response = CLIENT_RESPONDED_FIRST_TIME_OK;
        }


        autotests_send_protocol(&start, &test_protocols_arr[test_index], &cliaddr, len, sockfd, is_client_response);
        if(is_client_response == CLIENT_RESPONDED_FIRST_TIME_OK)
        {
            test_index++;
        }
    }
    
    free(test_protocols_arr);
    close(sockfd);
}

/** @brief send the test protocol to the board via ethernet */
void autotests_send_protocol(struct timespec *start, pr_prtcl *test_protocol, 
struct sockaddr_in *cliaddr, uint32_t len, int sockfd, int is_client_response)
{
     if(is_client_response == CLIENT_RESPONDED_FIRST_TIME_OK)
    {clock_gettime(CLOCK_MONOTONIC,start);}
    sendto(sockfd, (const pr_prtcl *)test_protocol, sizeof(*test_protocol),
            MSG_CONFIRM, (const struct sockaddr *)cliaddr,
            len);

    printf("test protocol sent.\n");
}

/** @brief wait until bytes receieved via the ethernet connected to the board and check first connection with client */
void autotests_wait_till_recv_bytes(ssize_t n_bytes_read, uint32_t *len, 
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

/**
 * @brief check how many tests there is to do.
 * @return number of tests to do.
*/
size_t ret_num_of_tests_to_do() {
    FILE* fptr = INIT_ALL_ZERO;
    size_t n_of_lines = INIT_TO_ZERO;
    char code = INIT_TO_ZERO;

    fptr = fopen(TESTS_FILE_PATH, "r");
    if(fptr == NULL)
    {
        printf("failed to open json file.\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        code = (char)fgetc(fptr);
        if(code == ',')
        {
            n_of_lines++;
        }
    } while (code != EOF);
    n_of_lines++; //plus the last test that in the end has no ','
    return n_of_lines;
    fclose(fptr);
}

/** 
 * @brief get the tests to be done from dedicated file, put the data into an array of pr_prctl 
 *        structs which will be sent to the board for tests
 */
void get_tests_to_do(pr_prtcl **test_protocols, size_t n_of_tests)
{
    *test_protocols = (pr_prtcl*)calloc(n_of_tests,sizeof(**test_protocols));
    FILE* fptr = INIT_ALL_ZERO;
    int code = INIT_TO_ZERO;
    
    fptr = fopen(TESTS_FILE_PATH, "r");
    if(fptr == NULL)
    {
        printf("failed to open json file.\n");
        exit(EXIT_FAILURE);
    }

    size_t i = INIT_TO_ZERO, j = INIT_TO_ZERO;
    do
    {
        test_protocols[j][i].testId = TestID;
        TestID++;
        update_last_test_id_file(TestID);

        fscanf(fptr, "%"SCNu8"", &((test_protocols[j][i]).perfToTest));
        fscanf(fptr, "%"SCNu8"", &((test_protocols[j][i]).iterations));
        fscanf(fptr, "%"SCNu8"", &((test_protocols[j][i]).bitPatrnStrLen));
        fscanf(fptr, "%s", ((test_protocols[j][i]).bitPatrnStr));
        while((code = fgetc(fptr)) != ',')
        {
            if(code == EOF)
            {
                break;
            }
        };
        
        i++;
    } while (code != EOF);

    fclose(fptr);
}