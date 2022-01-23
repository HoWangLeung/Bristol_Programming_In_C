#include "../../test.h"

void get_instrc_data(Program *p, int test_number);

void get_instrc_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        //========================================
        //=====<testcase No.>:<description>=======
        //========================================
        {"SET $X = $Y"},                                  //0:invalid missing colon
        {"SET $A = 5"},                                   //1:invalid, missing colon
        {"SET $A := 5"},                                  //2:invalid, missing semi-colon
        {"SET $X := $Y ; "},                              //3:Valid , values not defined but syntactically correct, which is fine for parser
        {"SET $X := $Y 2 B-ADD ; "},                      //4:Valid
        {"SET $X := $Y 2 B-TIMES ; "},                    //5:Valid
        {"SET $X := $Y 2 B-EQUALS ; "},                   //6:Valid
        {"SET $X := $Y 2 B-AND ; "},                      //7:Valid
        {"SET $X := $Y 2 B-OR ; "},                       //8:Valid
        {"SET $X := $Y 2 B-GREATER ; "},                  //9:Valid
        {"SET $X := $Y 2 B-LESS ; "},                     //10:Valid
        {"SET $X := $Y 2 B-HELLO ; "},                    //11:Invalid
        {"SET ($X) := ($Y 2 B-ADD) ; "},                  //12:Invalid, unknown symbols
        {"SET $AB := $Y 2 B-ADD ; "},                     //13:Invalid, unknown symbols AB
        {"SET $A : = $Y 2 B-ADD ; "},                     //14:Invalid, colon and equal should stick together
        {"SET $A := $F 2 B-ADD 3 B-TIMES 4 B-EQUALS ; "}, //15:Invalid, colon and equal should stick together

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

    get_instrc_data(p, 3);
    assert(INSTRC(p));

    get_instrc_data(p, 4);
    assert(INSTRC(p));

    get_instrc_data(p, 5);
    assert(INSTRC(p));

    get_instrc_data(p, 6);
    assert(INSTRC(p));

    get_instrc_data(p, 7);
    assert(INSTRC(p));

    get_instrc_data(p, 8);
    assert(INSTRC(p));

    get_instrc_data(p, 9);
    assert(INSTRC(p));

    get_instrc_data(p, 10);
    assert(INSTRC(p));

    get_instrc_data(p, 11);
    assert(!INSTRC(p));

    get_instrc_data(p, 12);
    assert(!INSTRC(p));

    get_instrc_data(p, 13);
    assert(!INSTRC(p));

    get_instrc_data(p, 14);
    assert(!INSTRC(p));

    get_instrc_data(p, 15);
    assert(INSTRC(p));
}
