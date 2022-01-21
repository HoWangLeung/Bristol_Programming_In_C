#include "../../test.h"
void get_instrclist_data(Program *p, int test_number);

void get_instrclist_data(Program *p, int test_number)
{
    clear_previous_data(p);
    char test_instructions[ARR_RANGE][ARR_RANGE] = {
        //========================================
        //=====<testcase No.>:<description>=======
        //========================================
        {"PRINT $A }"},                                    //0:Valid INSTRCLIST
        {"PRINT $A PRINT $B }"},                           //1:Valid INSTRCLIST
        {"SET $A := 5 ; }"},                               //2:Valid INSTRCLIST
        {"ONES 6 5 $A }"},                                 //3:Valid INSTRCLIST
        {"}"},                                             //4:Valid INSTRCLIST
        {"SET $A = $Y"},                                   //5:invalid missing colon
        {"SET $B = 5"},                                    //6:invalid, missing colon
        {"SET $C := 5"},                                   //7:invalid, missing semi-colon
        {"SET $A := $B ; }"},                              //8:Valid , values not defined but syntactically correct, which is fine for parser
        {"SET $E := $Y 2 B-ADD ; } "},                     //9:Valid
        {"SET $F := $Y 2 B-TIMES ; } "},                   //10:Valid
        {"SET $G := $Y 2 B-EQUALS ; }"},                   //11:Valid
        {"SET $H := $Y 2 B-AND ; }"},                      //12:Valid
        {"SET $I := $Y 2 B-OR ; }"},                       //13:Valid
        {"SET $J := $Y 2 B-GREATER ; }"},                  //14:Valid
        {"SET $K := $Y 2 B-LESS ; }"},                     //15:Valid
        {"SET $L := $Y 2 B-HELLO ; }"},                    //16:Invalid
        {"SET ($M) := ($Y 2 B-ADD) ; }"},                  //17:Invalid
        {"SET $MN := $Y 2 B-ADD ; }"},                     //18:Invalid
        {"SET $O : = $Y 2 B-ADD ; }"},                     //19:Invalid
        {"SET $P := $F 2 B-ADD 3 B-TIMES 4 B-EQUALS ; }"}, //20:Invalid
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

    get_instrclist_data(p, 5);
    assert(!INSTRCLIST(p));

    get_instrclist_data(p, 6);
    assert(!INSTRCLIST(p));

    get_instrclist_data(p, 7);
    assert(!INSTRCLIST(p));

    get_instrclist_data(p, 8);
    assert(INSTRCLIST(p));

    get_instrclist_data(p, 9);
    assert(INSTRCLIST(p));

    // get_instrclist_data(p, 10);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 11);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 12);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 13);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 14);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 15);
    // assert(INSTRCLIST(p));

    // get_instrclist_data(p, 16);
    // assert(!INSTRCLIST(p));

    // get_instrclist_data(p, 17);
    // assert(!INSTRCLIST(p));

    // get_instrclist_data(p, 18);
    // assert(!INSTRCLIST(p));

    // get_instrclist_data(p, 19);
    // assert(!INSTRCLIST(p));

    // get_instrclist_data(p, 20);
    // assert(INSTRCLIST(p));
}
