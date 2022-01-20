#include "../../test.h"
void get_unaryop_data(Program *p, int test_number);
void get_unaryop_data(Program *p, int test_number)
{
  clear_previous_data(p);
      char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"U-NOT"},        //valid
            {"U-EIGHTCOUNT"}, //valid
            {"TEXT"},         //invalid
        };
        copy_test_data(p, test_instructions, test_number);
}
void test_unaryop(Program *p)
{
  get_unaryop_data(p, 0);
  assert(UNARYOP(p));

  get_unaryop_data(p, 1);
  assert(UNARYOP(p));

  get_unaryop_data(p, 2);
  assert(!UNARYOP(p));
}
