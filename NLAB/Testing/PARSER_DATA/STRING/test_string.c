#include "../../test.h"
void get_string_data(Program *p, int test_number);
void get_string_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {" \"WORD\""}, //0:Valid
        {" \"WORD\""}, //1:Valid
        {"NOQUOTES"},  //2:Invalid, missing double qoutes
        {" \"123\""},  //3:Valid
        {" \"!!!\""},  //4:Valid
        {"!!!"},       //5:Invalid, missing double qoutes
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

    get_string_data(p, 3);
    assert(STRING(p));

    get_string_data(p, 4);
    assert(STRING(p));

    get_string_data(p, 5);
    assert(!STRING(p));
}
