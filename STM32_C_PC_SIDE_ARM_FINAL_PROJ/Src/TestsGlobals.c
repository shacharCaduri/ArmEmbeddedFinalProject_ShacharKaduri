#include "../Inc/TestsGlobals.h"

/** @brief global variable for test-id, always start from the last id there was */
uint32_t TestID = INIT_TO_ZERO;

void clean_buffer()
{
    int c;
    while ((c = getchar()) != '\n');
}