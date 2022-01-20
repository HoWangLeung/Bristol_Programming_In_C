#include "../../test.h"

void get_polishlist_data(Program *p, int test_number);
void get_polishlist_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {";"},    //valid
            {"$A ;"}, //valid
            {"5 ;"},  //valid

        };
        copy_test_data(p, test_instructions, test_number);
}

void test_polishlist(Program *p)
{
        get_polishlist_data(p, 0);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 1);
        assert(POLISHLIST(p));

        get_polishlist_data(p, 2);
        assert(POLISHLIST(p));
}
