#include "../../test.h"
void get_set_data(Program *p, int test_number);
void get_set_data(Program *p, int test_number)
{
  clear_previous_data(p);
   char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"SET $A := 1 ;"},
            {"SET $A := 3"},
            {"SET $B := $A U-EIGHTCOUNT ;"},
        };
        copy_test_data(p, test_instructions, test_number);
}
void test_set(Program *p)
{
        get_set_data(p, 0);
        assert(SET(p));

        get_set_data(p, 1);
        assert(!SET(p));

        get_set_data(p, 2);
        assert(SET(p));
}
