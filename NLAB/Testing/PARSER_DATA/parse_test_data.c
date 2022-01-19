#include "../test.h"

void get_parser_data(Program *p, int test_number, char *func_name)
{
    printf("IND get_parser_data\n");
    if (strcmp(func_name, "PROG") == 0)
    {
        printf("IN PROG GET PARASE DATA\n");
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"BEGIN { }"},               //0: valid
            {"BEGIN { PRINT $A }"},      //0: valid
            {"BEGIN }"},                 //0: invalid 1 digit
            {"BEGIN { SET $Z := 9 ; }"}, //0: valid
        };

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "INSTRCLIST") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"PRINT $A }"},
            {"PRINT $A PRINT $B }"},
            {"SET $A := 5 ; }"},
            {"ONES 6 5 $A }"},
            {"}"},
        };
        copy_test_data(p, test_instructions, test_number);
    }
    if (strcmp(func_name, "VARNAME") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"$A"}, //0: valid
            {"$M"}, //1: valid
            {"$1"}, //2: invalid: not A-Z
            {"$@"}, //3: invalid: not A-Z
            {"$!"}, //4: invalid: not A-Z
            {"*1"}, //5: invalid: expected '$' but received '*'
            {"*@"}, //6: invalid: expected '$' but received '*'
            {"1"},  //7: invalid: missing '$'
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "INTEGER") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"1"},   //0: valid 1 digit
            {"12"},  //1: valid 2 digits
            {"123"}, //2: valid 3 digits
            {"abc"}, //2: invalid, not [0-9]+
            {"!@#"}, //2: invalid. not [0-9]+
        };

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "INSTRC") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"SET $X = $Y"}, //invalid missing :
            {"SET $A = 5"},  //invalid, missing :
            {"SET $A := 5"}, //invalid, missing :

        };

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "SET") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"SET $A := 1 ;"},
            {"SET $A := 3"},
            {"SET $B := $A U-EIGHTCOUNT ;"},
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "PRINT") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"PRINT $A"},
            {"PRINT \"WORD\""},
            {"PRINT \"WORD"}, //invalid
            {"PRINT $@"},     //invalid
        };

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "CREATE") == 0)
    {

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

    if (strcmp(func_name, "LOOP") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"LOOP $I 10 { SET $F := $F $I B-TIMES; PRINT $F } "}, //valid
            {"LOOP $I 10 { } "},                                   //valid
            {" LOOP $I 5 { LOOP $J 5 {  SET $A := $I $J B-TIMES ; PRINT $A } }"}};

        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "POLISHLIST") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {";"},    //valid
            {"$A ;"}, //valid
            {"5 ;"},  //valid

        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "POLISH") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"5"},  //valid
            {"$A"}, //valid
            {"@"},  //invalid

        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "PUSHDOWN") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"5"},  //valid
            {"$A"}, //valid
            {"@"},  //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "UNARYOP") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"U-NOT"},        //valid
            {"U-EIGHTCOUNT"}, //valid
            {"TEXT"},         //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "STRING") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {" \"WORD\""},
            {" \"WORD\""}, //invalid
            {"NOQUOTES"},  //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "BINARYOP") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"B-AND"},     //valid
            {"B-OR"},      //valid
            {"B-GREATER"}, //valid
            {"B-LESS"},    //valid
            {"B-ADD"},     //valid
            {"B-TIMES"},   //valid
            {"B-EQUALS"},  //valid
            {"TEXT"},      //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "ROWS") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"1"},
            {"12"},   //invalid
            {"@123"}, //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "COLS") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            //========================================
            //=====<testcase No.>:<description>=======
            //========================================
            {"1"},
            {"12"},   //invalid
            {"@123"}, //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "FILENAME") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {" \"WORD\""},
            {" \"WORD\""}, //invalid
            {"NOQUOTES"},  //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }
}

