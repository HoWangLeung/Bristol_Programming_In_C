#include "../../test.h"
void get_pushdown_data(Program *p, int test_number);
void get_pushdown_data(Program *p, int test_number)
{
  clear_previous_data(p);
  char test_instructions[ARR_RANGE][ARR_RANGE] = {
      {"5"},  //valid
      {"$A"}, //valid
      {"@"},  //invalid
  };
  copy_test_data(p, test_instructions, test_number);
}
void test_pushdown(Program *p)
{
  get_pushdown_data(p, 0);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 1);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 2);
  assert(!PUSHDOWN(p));
}