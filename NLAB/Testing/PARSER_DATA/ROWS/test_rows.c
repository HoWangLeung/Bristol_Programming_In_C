#include "../../test.h"
void get_rows_data(Program *p, int test_number);
void get_rows_data(Program *p, int test_number)
{
  clear_previous_data(p);
 char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"1"},
            {"12"},   //invalid
            {"@123"}, //invalid
        };
        copy_test_data(p, test_instructions, test_number);
}

void test_rows(Program *p)
{
     get_rows_data(p, 0);
        assert(ROWS(p));

        get_rows_data(p, 1);
        assert(ROWS(p));

        get_rows_data(p, 2);
        assert(!ROWS(p));
}
