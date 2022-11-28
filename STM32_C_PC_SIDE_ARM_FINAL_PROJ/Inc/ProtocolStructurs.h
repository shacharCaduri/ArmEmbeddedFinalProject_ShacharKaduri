#ifndef C9F5C030_B9FE_415D_8AD0_B3E836826A6C
#define C9F5C030_B9FE_415D_8AD0_B3E836826A6C
#include <inttypes.h>
#include "Defines.h"

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

#endif /* C9F5C030_B9FE_415D_8AD0_B3E836826A6C */
