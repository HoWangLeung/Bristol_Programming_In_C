#include "../../test.h"

void get_instrc_data(Program *p, int test_number);

void get_instrc_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {"SET $X = $Y"}, //invalid missing :
        {"SET $A = 5"},  //invalid, missing :
        {"SET $A := 5"}, //invalid, missing :

    };

    copy_test_data(p, test_instructions, test_number);
}
void test_instrc(Program *p)
{
    get_instrc_data(p, 0);
    assert(!INSTRC(p));

    get_instrc_data(p, 1);
    assert(!INSTRC(p));

    get_instrc_data(p, 2);
    assert(!INSTRC(p));

    printf("TESTED INSTRC\n");
}
