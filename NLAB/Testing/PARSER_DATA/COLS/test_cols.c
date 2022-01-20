#include "../../test.h"
void get_cols_data(Program *p, int test_number);
void test_cols(Program *p)
{
        get_cols_data(p, 0);
        assert(COLS(p));

        get_cols_data(p, 1);
        assert(COLS(p));

        get_cols_data(p, 2);
        assert(!COLS(p));
}

void get_cols_data(Program *p, int test_number)
{
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
