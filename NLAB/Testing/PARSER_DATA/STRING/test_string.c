#include "../../test.h"
void get_string_data(Program *p, int test_number);
void get_string_data(Program *p, int test_number)
{
  clear_previous_data(p);
      char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {" \"WORD\""},
            {" \"WORD\""}, //invalid
            {"NOQUOTES"},  //invalid
        };
        copy_test_data(p, test_instructions, test_number);
}
void test_string(Program *p)
{
    get_string_data(p, 0);
    assert(STRING(p));

    get_string_data(p, 1);
    assert(STRING(p));

    get_string_data(p, 2);
    assert(!STRING(p));
}
