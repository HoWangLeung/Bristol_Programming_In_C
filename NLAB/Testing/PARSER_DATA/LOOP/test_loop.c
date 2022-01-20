#include "../../test.h"
void get_loop_data(Program *p, int test_number);
void get_loop_data(Program *p, int test_number)
{
  clear_previous_data(p);
  char test_instructions[ARR_RANGE][ARR_RANGE] = {
      {"LOOP $I 10 { SET $F := $F $I B-TIMES; PRINT $F } "}, //valid
      {"LOOP $I 10 { } "},                                   //valid
      {" LOOP $I 5 { LOOP $J 5 {  SET $A := $I $J B-TIMES ; PRINT $A } }"}};

  copy_test_data(p, test_instructions, test_number);
}

void test_loop(Program *p)
{
  get_loop_data(p, 0);
  assert(LOOP(p));

  get_loop_data(p, 1);
  assert(LOOP(p));

  get_loop_data(p, 2);
  assert(LOOP(p));
}
