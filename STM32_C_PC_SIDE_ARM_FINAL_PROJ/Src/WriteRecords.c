#include "../Inc/WriteRecords.h"

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