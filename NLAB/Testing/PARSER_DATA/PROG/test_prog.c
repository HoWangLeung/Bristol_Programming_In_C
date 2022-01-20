#include "../../test.h"
void get_prog_data(Program *p, int test_number);
void get_prog_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"BEGIN { }"},               //0: valid
            {"BEGIN { PRINT $A }"},      //0: valid
            {"BEGIN }"},                 //0: invalid 1 digit
            {"BEGIN { SET $Z := 9 ; }"}, //0: valid

        };

        copy_test_data(p, test_instructions, test_number);
}
void test_prog(Program *p)
{
        get_prog_data(p, 0);
        assert(PROG(p));

        get_prog_data(p, 1);
        assert(PROG(p));

        get_prog_data(p, 2);
        assert(!PROG(p));

        get_prog_data(p, 3);
        assert(PROG(p));

        get_prog_data(p, 4);
        assert(!PROG(p));
}
