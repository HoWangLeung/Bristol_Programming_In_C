#include "../test.h"

void get_interp_data(Program *p, int test_number, char *func_name)
{
    if (strcmp(func_name, "PROG") == 0)
    {
        // char test_instructions[ARR_RANGE][ARR_RANGE] = {
        //     {"BEGIN { SET $A := 5 ; PRINT $A }"},                                                           //0: valid
        //     {"BEGIN { PRINT $A }"},                                                                         //1: Invalid, $A is undefined
        //     {"BEGIN }"},                                                                                    //2: Invalid , missing {
        //     {"BEGIN { SET $Z := 9 ; }"},                                                                    //3: valid
        //     {"BEGIN { SET $A := 5 ; PRINT $B }"},                                                           //4: Invalid, $A is set but $B is undefined
        //     {"BEGIN {  PRINT $C SET $C := 5 ; }"},                                                          //5: Invalid, print $C before $C is set
        //     {"BEGIN {  ONES 3 5 $A   PRINT \"ARRAY:\"  PRINT $A  } "},                                      //6: valid
        //     {"BEGIN {  READ \"lglider.arr\" $A  PRINT $A  } "},                                             //7: valid
        //     {"BEGIN { SET $F := 2 ; PRINT $F SET $E := 5 ; PRINT $E SET $D := $F $E B-TIMES ; PRINT $D }"}, //8:valid: example from setprintc.nlb
        //     {"BEGIN { ONES 6 5 $A SET $A := $A 2 B-ADD ; PRINT \"ARRAY:\" PRINT $A }"},                     //9:valid: example from setprintb.nlb
        //     {"BEGIN { SET $I := 5 ; PRINT $I }"},                                                           //10:valid: example from setprintb.nlb
        //     {"BEGIN { ONES 6 5 $A PRINT \"ARRAY\" PRINT $A }"},                                             //11: valid example from onesprint.nlb
        //     {"BEGIN { SET $A := 0 ; LOOP $I 5 { LOOP $J 5 { SET $A := $I $J B-TIMES ; PRINT $A } } }"},     //12: valid example from nestedloop.nlb
        //     {"BEGIN { LOOP $I 10 { SET $I := $I 1 B-ADD ; PRINT $I } }"},                                   //13: valid example from loopb.nlb
        //     {"BEGIN { LOOP $I 10 { PRINT $I } }"},                                                          //14: valid example from loopa.nlb
        //     {"BEGIN { READ \"lglider.arr\" $A \
        //     LOOP $I 10 { \
        //         SET $B := $A U-EIGHTCOUNT ; \
        //         SET $D := $B 3 B-EQUALS ; SET $C := $B 2 B-EQUALS $D B-OR $A B-AND ; \
        //         SET $E := $A U-NOT $D B-AND $C B-OR ; PRINT $I PRINT $E SET $A := $E ; } }"},               //15: valid example from lifeb3s23.nlb
        // };
        // copy_test_data(p, test_instructions, test_number);
    }
}

