#include "../../test.h"
void get_create_data(Program *p, int test_number);

void get_create_data(Program *p, int test_number)
{
    clear_previous_data(p);

    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        //========================================
        //=====<testcase No.>:<description>=======
        //========================================
        {"ONES 6 5 $A"},                     //0: Valid
        {"ONES 6 5"},                        //1: Invalid, missing varname
        {"ONES 6 $A "},                      //2: Invalid, missing col or row
        {"READ \"Data/lglider.arr\" $A"},    //3: valid
        {"READ \"Data/lglider.arr\""},       //4: Invalid, missing varname
        {"READ  $A"},                        //5: Invalid, missing filename
        {"PRINT \"Data/lglider.arr"},        //6: Invalid,missing a double quote on the right
        {"READ"},                            //7: Invalid, no filename and variable
        {"READ \"Data/nosuchfile.arr\" $A"}, //8: Invalid, no such file
        {"ONES 16 15 $A"},                   //9: Valid , 2-digits
        {"ONES 165 155 $A"},                 //10:Valid , $A
        {"ONES 1 1 $F"},                     //11:Valid , save in $F
        {"ONES 1 1 $Z"},                     //12:Valid , save in $Z
        {"ONES -1 -1 $F"},                   //13:InValid , negative number
        {"ONES -15 -12 $Z"},                 //14:InValid , negative number
        {"ONES 1 5 $1"},                     //15:InValid , A-Z only
        {"ONES 1 5 A"},                      //16:InValid , missing $ for A
        {"ONES 1 5 =="},                     //17:InValid , wrong symbol
        {"ONES 1 5 B-ADD 4 B-TIMES "},       //18:InValid , wrong symbol
        {"PRINT \"Data/lglider"},            //19: Invalid,missing .arr
        {"ONES65$A"},                        //20: Invalid, stick together
       

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

    get_create_data(p, 7);
    assert(!CREATE(p));

    get_create_data(p, 8);
    assert(!CREATE(p));

    get_create_data(p, 9);
    assert(CREATE(p));

    get_create_data(p, 10);
    assert(CREATE(p));

    get_create_data(p, 11);
    assert(CREATE(p));

    get_create_data(p, 12);
    assert(CREATE(p));

    get_create_data(p, 13);
    assert(!CREATE(p));

    get_create_data(p, 14);
    assert(!CREATE(p));

    get_create_data(p, 15);
    assert(!CREATE(p));

    get_create_data(p, 16);
    assert(!CREATE(p));

    get_create_data(p, 17);
    assert(!CREATE(p));

    get_create_data(p, 18);
    assert(!CREATE(p));

    get_create_data(p, 19);
    assert(!CREATE(p));

    get_create_data(p, 20);
    assert(!CREATE(p));

  
}
