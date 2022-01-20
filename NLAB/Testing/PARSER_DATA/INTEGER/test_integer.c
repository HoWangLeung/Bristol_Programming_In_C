#include "../../test.h"

void get_integer_data(Program *p, int test_number);

void get_integer_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"1"},   //0: valid 1 digit
            {"12"},  //1: valid 2 digits
            {"123"}, //2: valid 3 digits
            {"abc"}, //2: invalid, not [0-9]+
            {"!@#"}, //2: invalid. not [0-9]+
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
}
