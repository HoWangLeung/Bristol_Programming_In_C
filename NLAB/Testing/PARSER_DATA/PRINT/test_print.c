#include "../../test.h"

void get_print_data(Program *p, int test_number);
void get_print_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"PRINT $A"},
            {"PRINT \"WORD\""},
            {"PRINT \"WORD"}, //invalid
            {"PRINT $@"},     //invalid
        };

        copy_test_data(p, test_instructions, test_number);
}
void test_print(Program *p)
{
        get_print_data(p, 0);
        assert(PRINT(p));

        get_print_data(p, 1);
        assert(PRINT(p));

        get_print_data(p, 2);
        assert(!PRINT(p));

        get_print_data(p, 3);
        assert(!PRINT(p));
}
