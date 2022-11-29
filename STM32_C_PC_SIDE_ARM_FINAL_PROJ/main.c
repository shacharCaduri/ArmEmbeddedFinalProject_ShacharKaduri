#include <stdio.h>
#include "Inc/ManTests.h"
#include "Inc/TestsGlobals.h"

typedef enum {AUTO_TESTS=1, MAN_TESTS=2,EXIT=3, DO_NOTH=0} CHOICE;

/**
 * @name Driver code
 * @brief the main entry of the program.
 *
 */
int main()
{
    int choice = DO_NOTH;

    printf("=====================================\n");
    printf("Welcome to STM32 Unit Tests Program\n");
    printf("=====================================\n");

    while (TRUE)
    {
        choice = DO_NOTH;
        printf("\nplease choose one of the options below:\n");
        printf("--------------------------------------------\n");
        printf("1) Automatic Tests (predefined tests will be performed in sequence)\n");
        printf("2) Manual Tests (you choose which tests to do by input the parameters until user hits CTRL-D)\n");
        printf("3) Exit the program \n");
        scanf("%d", &choice);

        switch(choice)
        {
            case AUTO_TESTS:
            break;
            case MAN_TESTS:
                manual_tests();
            break;
            case EXIT:
                /* exit program with status code 0 */
                exit(0);
            break;
            default:
                printf("Not a valid option. choose from the numbers given by the menu.\n");
            break;
        }

        clean_buffer();

    }
    return 0;
}



