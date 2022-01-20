#include "../../test.h"
void get_instrclist_data(Program *p, int test_number);

void get_instrclist_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {"PRINT $A }"},
        {"PRINT $A PRINT $B }"},
        {"SET $A := 5 ; }"},
        {"ONES 6 5 $A }"},
        {"}"},
    };
    copy_test_data(p, test_instructions, test_number);
}

void test_instrclist(Program *p)
{
    get_instrclist_data(p, 0);
    assert(INSTRCLIST(p));

    get_instrclist_data(p, 1);
    assert(INSTRCLIST(p));

    get_instrclist_data(p, 2);
    assert(INSTRCLIST(p));

    get_instrclist_data(p, 3);
    assert(INSTRCLIST(p));

    get_instrclist_data(p, 4);
    assert(INSTRCLIST(p));
}
