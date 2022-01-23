#include "../../test.h"
void get_unaryop_data(Program *p, int test_number);
void get_unaryop_data(Program *p, int test_number)
{
  clear_previous_data(p);
  char test_instructions[ARR_RANGE][ARR_RANGE] = {
      //========================================
      //=====<testcase No.>:<description>=======
      //========================================
      {"U-NOT"},        //0:valid
      {"U-EIGHTCOUNT"}, //1:valid
      {"TEXT"},         //2:invalid
      {"B-ADD"},        //3:invalid
      {"B-AND"},        //4:invalid
      {"B-OR"},         //5:invalid
      {"B-GREATER"},    //6:invalid
      {"B-LESS"},       //7:invalid
      {"B-EQUALS"},     //8:invalid
      {"UNOT"},         //9:invalid
      {"UEIGHTCOUNT"},  //10:invalid
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

  get_unaryop_data(p, 3);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 4);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 5);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 6);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 7);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 8);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 9);
  assert(!UNARYOP(p));

  get_unaryop_data(p, 10);
  assert(!UNARYOP(p));
}
