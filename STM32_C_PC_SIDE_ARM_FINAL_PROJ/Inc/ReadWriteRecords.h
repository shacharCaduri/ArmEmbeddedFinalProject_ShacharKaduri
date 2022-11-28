#ifndef E7952155_36B4_45B5_878B_FC8F902F0F49
#define E7952155_36B4_45B5_878B_FC8F902F0F49
#include <stdio.h>
#include "ProtocolStructurs.h"
#include "stdlib.h"
#include <time.h>

uint32_t ret_last_test_id();

void update_last_test_id_file(uint32_t last_test_id);

void write_rec(const double test_time, res_prtcl* resPrtcl);


#endif /* E7952155_36B4_45B5_878B_FC8F902F0F49 */
