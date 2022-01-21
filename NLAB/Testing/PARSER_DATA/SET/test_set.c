#include "../../test.h"
void get_set_data(Program *p, int test_number);
void get_set_data(Program *p, int test_number)
{
        //SET GRAMMAR: <SET> ::= <VARNAME> ":=" <SET>
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"SET $A := 1 ;"},                                                               //0:Valid
            {"SET $A := 3"},                                                                 //1:Invalid, missing semi-colon
            {"SET $B := $A U-EIGHTCOUNT ;"},                                                 //2:Valid
            {"SET $C := $C U-EIGHTCOUNT ;"},                                                 //3:Valid
            {"SET $D := $D U-NOT ;"},                                                        //4:Valid
            {"SET $E := $E 1 B-ADD ;"},                                                      //5:Valid
            {"SET $F := $F 2 B-AND ;"},                                                      //6:Valid
            {"SET $G := $G 3 B-OR ;"},                                                       //7:Valid
            {"SET $H := $H 4 B-TIMES ;"},                                                    //8:Valid
            {"SET $I := $I 5 B-GREATER ;"},                                                  //9:Valid
            {"SET $J := $J 6 B-LESS ;"},                                                     //10:Valid
            {"SET $K := $K 7 B-EQUALS ;"},                                                   //11:Valid
            {"SET $K := $K 7 B-EQUALS 1 B-ADD 2 B-TIMES 3 B-GREATER 4 B-LESS 5 B-EQUALS ;"}, //12:Valid
            {"SET 1 := 2 3 B-EQUALS ;"},                                                     //13:InValid
            {"SET 1 := $A $B B-EQUALS ;"},                                                   //14:InValid
            {"SET $AB := $AD $B B-EQUALS ;"},                                                //15:InValid
           

        };
        copy_test_data(p, test_instructions, test_number);
}
void test_set(Program *p)
{
        get_set_data(p, 0);
        assert(SET(p));

        get_set_data(p, 1);
        assert(!SET(p));

        get_set_data(p, 2);
        assert(SET(p));

        get_set_data(p, 3);
        assert(SET(p));

        get_set_data(p, 4);
        assert(SET(p));

        get_set_data(p, 5);
        assert(SET(p));

        get_set_data(p, 6);
        assert(SET(p));

        get_set_data(p, 7);
        assert(SET(p));

        get_set_data(p, 8);
        assert(SET(p));

        get_set_data(p, 9);
        assert(SET(p));

        get_set_data(p, 10);
        assert(SET(p));

        get_set_data(p, 11);
        assert(SET(p));

        get_set_data(p, 12);
        assert(SET(p));

        get_set_data(p, 13);
        assert(!SET(p));

        get_set_data(p, 14);
        assert(!SET(p));

        get_set_data(p, 15);
        assert(!SET(p));

 
}
