#ifndef E7952155_36B4_45B5_878B_FC8F902F0F49
#define E7952155_36B4_45B5_878B_FC8F902F0F49
#include <stdio.h>
#include "ProtocolStructurs.h"
#include "stdlib.h"
#include <time.h>

/** @brief returning the last id used saved in file, thus, ensure test id not repeated, even if program closed */
uint32_t ret_last_test_id();

/** @brief update the file that saves the test-id to be the last id used by the program */
void update_last_test_id_file(uint32_t last_test_id);

/** @brief write the test record to a file, thus holds a list of test records can be view later, indicating the board tests status */
void write_rec(const double test_time, res_prtcl* resPrtcl);

#endif /* E7952155_36B4_45B5_878B_FC8F902F0F49 */
