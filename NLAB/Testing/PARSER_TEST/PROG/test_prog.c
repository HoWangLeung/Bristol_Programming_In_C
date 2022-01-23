#include "../../test.h"
void get_prog_data(Program *p, int test_number);
void get_prog_data(Program *p, int test_number)
{
        clear_previous_data(p);
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"BEGIN { }"},               //0: valid
            {"BEGIN { PRINT $A }"},      //1: valid
            {"BEGIN }"},                 //2: invalid 1 digit
            {"BEGIN { SET $Z := 9 ; }"}, //3: valid
            {" { SET $Z := 9 ; }"},      //4: Invalid, missing BEGIN
            {" BEGIN  SET $Z := 9 ; }"}, //5: Invalid, missing {
            {"BEGIN { SET $A := 1  }"},  //6: Invalid, missing ;
            {"BEGIN { SET $A = 1 ; }"},  //7: Invalid, missing :
            {"BEGIN { SET $A : 1 ; }"},  //8: Invalid, missing =
            {"BEGIN { SET A := 1 ; }"},  //9: Invalid, missing $
            {"BEGIN { SET A := @ ; }"},  //10: Invalid, integer only
            {"BEGIN { SET @ := 2 ; }"},  //11: Invalid, variable only
            {"BEGIN { SET 1 := 5 ; }"},  //12: Invalid, variable only
            {"BEGIN { SET $A := 9 ; }"}, //13: valid, variable check
            {"BEGIN { SET $B := 9 ; }"}, //14: valid, variable check
            {"BEGIN { SET $C := 9 ; }"}, //15: valid, variable check
            {"BEGIN { SET $D := 9 ; }"}, //16: valid, variable check
            {"BEGIN { SET $E := 9 ; }"}, //17: valid, variable check
            {"BEGIN { SET $F := 9 ; }"}, //18: valid, variable check
            {"BEGIN { SET $G := 9 ; }"}, //19: valid, variable check
            {"BEGIN { SET $H := 9 ; }"}, //20: valid, variable check
            {"BEGIN { SET $I := 9 ; }"}, //21: valid, variable check
            {"BEGIN { SET $J := 9 ; }"}, //22: valid, variable check
            {"BEGIN { SET $K := 9 ; }"}, //23: valid, variable check
            {"BEGIN { SET $L := 9 ; }"}, //24: valid, variable check
            {"BEGIN { SET $M := 9 ; }"}, //25: valid, variable check
            {"BEGIN { SET $N := 9 ; }"}, //26: valid, variable check
            {"BEGIN { SET $O := 9 ; }"}, //27: valid, variable check
            {"BEGIN { SET $P := 9 ; }"}, //28: valid, variable check
            {"BEGIN { SET $Q := 9 ; }"}, //29: valid, variable check
            {"BEGIN { SET $R := 9 ; }"}, //30: valid, variable check
            {"BEGIN { SET $S := 9 ; }"}, //31: valid, variable check
            {"BEGIN { SET $T := 9 ; }"}, //32: valid, variable check
            {"BEGIN { SET $U := 9 ; }"}, //33: valid, variable check
            {"BEGIN { SET $V := 9 ; }"}, //34: valid, variable check
            {"BEGIN { SET $W := 9 ; }"}, //35: valid, variable check
            {"BEGIN { SET $X := 9 ; }"}, //36: valid, variable check
            {"BEGIN { SET $Y := 9 ; }"}, //37: valid, variable check
            {"BEGIN { SET $Z := 9 ; }"}, //38: valid, variable check
            //==================================================
            //=====  Example Data ======================
            //==================================================
            {"BEGIN { \
             READ \"Data/lglider.arr\" $A\
             LOOP $I 10 {\
                SET $B := $A U-EIGHTCOUNT ; \
                SET $D := $B 3 B-EQUALS ; \
                SET $C := $B 2 B-EQUALS $D B-OR $A B-AND ; \
                SET $E := $A U-NOT $D B-AND $C B-OR ; \
                PRINT $I \
                PRINT $E\
                SET $A := $E ;  \
               } } "},                              //39: Valid, # John Conway's Game of LIFE (B3/S23)
            {"BEGIN {\
                SET $F := 1 ;\
                LOOP $I 10 {\
                SET $F := $F $I B-TIMES ;\
                PRINT $F\
                 }\
               }"},                                 //40: valid, loopa.nlb
            {"BEGIN {\
               LOOP $I 10 {\
            SET $I := $I 1 B-ADD ; PRINT $I } } "}, //41: valid, loopb.nlb
            {"BEGIN {\
                SET $A := 0 ;\
                LOOP $I 5 {\
                    LOOP $J 5 {\
                SET $A := $I $J B-TIMES ;\
                PRINT $A } } } "},                  //42: valid, nestedloop.nlb
            {"BEGIN {\
                ONES 6 5 $A\
                PRINT \"ARRAY\"\
                PRINT $A }  "},                     //43: valid, onesprint.nlb
            {"BEGIN {\
                SET $I := 5 ;\
                PRINT $I }  "},                     //44: valid, setprinta.nlb

            {"BEGIN {\
                ONES 6 5 $A \
                SET $A := $A 2 B-ADD ; \
                PRINT \"ARRAY:\" \
                PRINT $A }  "}, //45: valid, setprintb.nlb
            {"BEGIN {\
                SET $F := 2 ;\
                PRINT $F\
                SET $E := 5 ;\
                PRINT $E\
                SET $D := $F $E B-TIMES ;\
                PRINT $D\
                PRINT $D }  "}, //46: valid, setprintc.nlb

        };

        copy_test_data(p, test_instructions, test_number);
}
void test_prog(Program *p)
{
        get_prog_data(p, 0);
        assert(PROG(p));

        get_prog_data(p, 1);
        assert(PROG(p));

        get_prog_data(p, 2);
        assert(!PROG(p));

        get_prog_data(p, 3);
        assert(PROG(p));

        get_prog_data(p, 4);
        assert(!PROG(p));

        get_prog_data(p, 5);
        assert(!PROG(p));

        get_prog_data(p, 6);
        assert(!PROG(p));

        get_prog_data(p, 7);
        assert(!PROG(p));

        get_prog_data(p, 8);
        assert(!PROG(p));

        get_prog_data(p, 9);
        assert(!PROG(p));

        get_prog_data(p, 10);
        assert(!PROG(p));

        get_prog_data(p, 11);
        assert(!PROG(p));

        get_prog_data(p, 12);
        assert(!PROG(p));

        get_prog_data(p, 12);
        assert(!PROG(p));

        get_prog_data(p, 12);
        assert(!PROG(p));

        get_prog_data(p, 12);
        assert(!PROG(p));

        get_prog_data(p, 13);
        assert(PROG(p));

        get_prog_data(p, 14);
        assert(PROG(p));

        get_prog_data(p, 15);
        assert(PROG(p));

        get_prog_data(p, 16);
        assert(PROG(p));

        get_prog_data(p, 17);
        assert(PROG(p));

        get_prog_data(p, 18);
        assert(PROG(p));

        get_prog_data(p, 19);
        assert(PROG(p));

        get_prog_data(p, 20);
        assert(PROG(p));

        get_prog_data(p, 21);
        assert(PROG(p));

        get_prog_data(p, 22);
        assert(PROG(p));

        get_prog_data(p, 23);
        assert(PROG(p));

        get_prog_data(p, 24);
        assert(PROG(p));

        get_prog_data(p, 25);
        assert(PROG(p));

        get_prog_data(p, 26);
        assert(PROG(p));

        get_prog_data(p, 27);
        assert(PROG(p));

        get_prog_data(p, 28);
        assert(PROG(p));

        get_prog_data(p, 29);
        assert(PROG(p));

        get_prog_data(p, 30);
        assert(PROG(p));

        get_prog_data(p, 31);
        assert(PROG(p));

        get_prog_data(p, 32);
        assert(PROG(p));

        get_prog_data(p, 33);
        assert(PROG(p));

        get_prog_data(p, 34);
        assert(PROG(p));

        get_prog_data(p, 35);
        assert(PROG(p));

        get_prog_data(p, 36);
        assert(PROG(p));

        get_prog_data(p, 37);
        assert(PROG(p));

        get_prog_data(p, 38);
        assert(PROG(p));

        get_prog_data(p, 39);
        assert(PROG(p));

        get_prog_data(p, 40);
        assert(PROG(p));

        get_prog_data(p, 41);
        assert(PROG(p));

        get_prog_data(p, 42);
        assert(PROG(p));

        get_prog_data(p, 43);
        assert(PROG(p));

        get_prog_data(p, 44);
        assert(PROG(p));

        get_prog_data(p, 45);
        assert(PROG(p));

        get_prog_data(p, 46);
        assert(PROG(p));
}
