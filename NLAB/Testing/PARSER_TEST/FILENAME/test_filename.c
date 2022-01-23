#include "../../test.h"

void get_filename_data(Program *p, int test_number);

void get_filename_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        //========================================
        //=====<testcase No.>:<description>=======
        //========================================
        {" \"lgblock\""},
        {" \"lglider\""}, //invalid
        {"NOQUOTES"},     //invalid
    };
    copy_test_data(p, test_instructions, test_number);
}
void test_filename(Program *p)
{
    get_filename_data(p, 0);
    assert(FILENAME(p));

    get_filename_data(p, 1);
    assert(FILENAME(p));

    get_filename_data(p, 2);
    assert(!FILENAME(p));
}
