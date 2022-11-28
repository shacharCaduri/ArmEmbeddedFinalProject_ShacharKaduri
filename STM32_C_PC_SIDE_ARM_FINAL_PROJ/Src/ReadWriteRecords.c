#include "../Inc/ReadWriteRecords.h"

uint32_t ret_last_test_id()
{
    FILE* fptr = fopen(LAST_ID_FILE_PATH, "r+");
    uint32_t tmp=INIT_TO_ZERO;

    if(fptr == NULL) {
        return tmp = FIRST_ID;
    }

    fscanf(fptr, "%"SCNu32"", &tmp);

    fclose(fptr);
    
    return tmp;
}

void update_last_test_id_file(uint32_t last_test_id)
{
    FILE* fptr = fopen(LAST_ID_FILE_PATH, "w+");

    if(fptr == NULL) {
        printf("file couldn't be opened\n");
        exit(1);
    }

    fprintf(fptr, "%"PRIu32"", last_test_id);

    fclose(fptr);
}

void write_rec(const double test_time, res_prtcl* resPrtcl)
{
    FILE *fptr = fopen(TEST_RECORDS_PATH,"a");

    if(fptr == NULL) {
        printf("file couldn't be opened\n");
        exit(1);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char delim[DELIM_SIZE] = {" | "};
    char new_line_char = '\n';
    
    fprintf(fptr, "%"PRIu32"", resPrtcl->testId);
    fprintf(fptr, "%s", delim);
    
    fprintf(fptr, "%f", test_time);
    fprintf(fptr, "%s", delim);
    if(resPrtcl->testResult == TEST_SUCCEED)
    {
        fprintf(fptr, "%s", "PASSED");
    } 
    else
    {
        fprintf(fptr, "%s", "FAILED");        
    }
    fprintf(fptr, "%s", delim);

    fprintf(fptr, "%d-", tm.tm_year+YEAR_FIX_VALUE);
    fprintf(fptr, "%02d-", tm.tm_mon + MONTHS_FIX_VALUE);
    fprintf(fptr, "%02d-", tm.tm_mday);
    
    fprintf(fptr, "%02d:", tm.tm_hour);
    fprintf(fptr, "%02d:", tm.tm_min);
    fprintf(fptr, "%02d", tm.tm_sec);

    fprintf(fptr, "%c", new_line_char);
    
    fclose(fptr);
}