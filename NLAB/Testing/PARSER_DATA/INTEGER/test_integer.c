#include "../../test.h"

void get_integer_data(Program *p, int test_number);

void get_integer_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"1"},         //0: Valid 1 digit
            {"12"},        //1: Valid 2 digits
            {"123"},       //2: Valid 3 digits
            {"abc"},       //3: Invalid, not [0-9]+
            {"!@#"},       //4: Invalid. not [0-9]+
            {"1234"},      //5: Valid 4 digits
            {"12345"},     //6: Valid 5 digits
            {"1-2-3-4-5"}, //7: Valid 5 digits
            {"1,2,3,4,5"}, //8: Valid 5 digits
        };
        copy_test_data(p, test_instructions, test_number);
}
void test_integer(Program *p)
{
        get_integer_data(p, 0);
        assert(INTEGER(p));

        get_integer_data(p, 1);
        assert(INTEGER(p));

        get_integer_data(p, 2);
        assert(INTEGER(p));

        get_integer_data(p, 3);
        assert(!INTEGER(p));

        get_integer_data(p, 4);
        assert(!INTEGER(p));

        get_integer_data(p, 5);
        assert(INTEGER(p));

        get_integer_data(p, 6);
        assert(INTEGER(p));

        get_integer_data(p, 7);
        assert(!INTEGER(p));

        get_integer_data(p, 8);
        assert(!INTEGER(p));
}
