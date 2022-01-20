#include "../../test.h"
void get_create_data(Program *p, int test_number);

void get_create_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {"ONES 6 5 $A"},             //0: valid
        {"ONES 6 5"},                //1: invalid, missing varname
        {"ONES 6 $A "},              //2: invalid, missing col or row
        {"READ \"lglider.arr\" $A"}, //3: valid
        {"READ \"lglider.arr\""},    //4: invalid, missing varname
        {"READ  $A"},                //5: invalid, missing filename
        {"PRINT \"lglider.arr"},     //6: invalid,missing a double quote on the right
    };

    copy_test_data(p, test_instructions, test_number);
}

void test_create(Program *p)
{
    get_create_data(p, 0);
    assert(CREATE(p));

    get_create_data(p, 1);
    assert(!CREATE(p));

    get_create_data(p, 2);
    assert(!CREATE(p));

    get_create_data(p, 3);
    assert(CREATE(p));

    get_create_data(p, 4);
    assert(!CREATE(p));

    get_create_data(p, 5);
    assert(!CREATE(p));

    get_create_data(p, 6);
    assert(!CREATE(p));
}
