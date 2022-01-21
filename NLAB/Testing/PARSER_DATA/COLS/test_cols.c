#include "../../test.h"
void get_cols_data(Program *p, int test_number);

void get_cols_data(Program *p, int test_number)
{
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"1"},     //0:Valid
            {"12"},    //1:Valid
            {"@123"},  //2:Invalid
            {"!!!"},   //3:Invalid
            {"123"},   //4:Valid 3-digits
            {"12345"}, //5:Valid 5-digits
            {"ABC"},   //6:Invalid, should be digit only
            {"A!!C"},  //7:Invalid, should be digit only
            {"-5"},    //8:Invalid, positive integer only
            {"-15"},   //9:Invalid, positive integer only
            {"-125"},  //10:Invalid, positive integer only
        };
        copy_test_data(p, test_instructions, test_number);
}

void test_cols(Program *p)
{
        get_cols_data(p, 0);
        assert(COLS(p));

        get_cols_data(p, 1);
        assert(COLS(p));

        get_cols_data(p, 2);
        assert(!COLS(p));

        get_cols_data(p, 3);
        assert(!COLS(p));

        get_cols_data(p, 4);
        assert(COLS(p));

        get_cols_data(p, 5);
        assert(COLS(p));

        get_cols_data(p, 6);
        assert(!COLS(p));

        get_cols_data(p, 7);
        assert(!COLS(p));

        get_cols_data(p, 8);
        assert(!COLS(p));

        get_cols_data(p, 9);
        assert(!COLS(p));

        get_cols_data(p, 10);
        assert(!COLS(p));
}
