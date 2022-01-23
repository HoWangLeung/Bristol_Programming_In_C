#include "../../test.h"
void get_binaryop_data(Program *p, int test_number);

void get_binaryop_data(Program *p, int test_number)
{
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        {"B-AND"},        //0:valid
        {"B-OR"},         //1:valid
        {"B-GREATER"},    //2:valid
        {"B-LESS"},       //3:valid
        {"B-ADD"},        //4:valid
        {"B-TIMES"},      //5:valid
        {"B-EQUALS"},     //6:valid
        {"TEXT"},         //7:invalid
        {"!@@@!"},        //8:invalid
        {"AND"},          //9:invalid
        {"OR"},           //10:invalid
        {"B"},            //11:invalid
        {"B-"},           //12:invalid
        {"B-AN"},         //13:invalid
        {"B-ORR"},        //14:invalid
        {"BOR"},          //15:invalid
        {"BAND"},         //16:invalid
        {"B-GREATERSSS"}, //17:invalid

    };
    copy_test_data(p, test_instructions, test_number);
}

void test_binaryop(Program *p)
{
    get_binaryop_data(p, 0);
    assert(BINARYOP(p));

    get_binaryop_data(p, 1);
    assert(BINARYOP(p));

    get_binaryop_data(p, 2);
    assert(BINARYOP(p));

    get_binaryop_data(p, 3);
    assert(BINARYOP(p));

    get_binaryop_data(p, 4);
    assert(BINARYOP(p));

    get_binaryop_data(p, 5);
    assert(BINARYOP(p));

    get_binaryop_data(p, 6);
    assert(BINARYOP(p));

    get_binaryop_data(p, 7);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 8);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 9);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 10);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 11);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 12);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 13);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 14);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 15);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 16);
    assert(!BINARYOP(p));

    get_binaryop_data(p, 17);
    assert(!BINARYOP(p));
}


