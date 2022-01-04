// #include "Unity/unity.h"
#include "Functions/nlab.h"
#define ARR_RANGE 100

void set_up_testdata(Program *p, int test_number, char *func_name);
void RUN_TEST(char *testcase_name);
void copy_test_data(Program *p, char test_instructions[ARR_RANGE][ARR_RANGE], int test_number);
void RUN_INTERP_TEST(char *testcase_name);

void get_parser_data(Program *p, int test_number, char *func_name);
void get_interp_data(Program *p, int test_number, char *func_name);

void clear_previous_data(Program *p);
void free_struct(Program *p);

int main(void)
{
#ifdef PARSER
    RUN_TEST("PROG");
    RUN_TEST("INSTRCLIST");
    RUN_TEST("INSTRC");
    RUN_TEST("SET");
    RUN_TEST("PRINT");
    RUN_TEST("CREATE");
    RUN_TEST("LOOP");
    RUN_TEST("POLISHLIST");
    RUN_TEST("VARNAME");
    RUN_TEST("INTEGER");
    RUN_TEST("POLISH");
    RUN_TEST("PUSHDOWN");
    RUN_TEST("UNARYOP");
    RUN_TEST("BINARYOP");
    RUN_TEST("STRING");
    RUN_TEST("ROWS");
    RUN_TEST("COLS");
    RUN_TEST("FILENAME");
    printf("TESTED PARSER\n");
#endif

#ifdef INTERP
    RUN_INTERP_TEST("PROG");
#endif
    printf("END OF TESTING\n");
    return 0;
}

void RUN_TEST(char *testcase_name)
{
    Program *p = calloc(1, sizeof(Program));

    if (strcmp(testcase_name, "PROG") == 0)
    {
        printf("ASSERTING**\n");
        set_up_testdata(p, 0, "PROG");
        assert(PROG(p));

        set_up_testdata(p, 1, "PROG");
        assert(PROG(p));

        set_up_testdata(p, 2, "PROG");
        assert(!PROG(p));

        set_up_testdata(p, 3, "PROG");
        assert(PROG(p));

        printf("TESTING PROG\n");
    }

    if (strcmp(testcase_name, "INSTRCLIST") == 0)
    {
        set_up_testdata(p, 0, "INSTRCLIST");
        assert(INSTRCLIST(p));

        set_up_testdata(p, 1, "INSTRCLIST");
        assert(INSTRCLIST(p));

        set_up_testdata(p, 2, "INSTRCLIST");
        assert(INSTRCLIST(p));

        set_up_testdata(p, 3, "INSTRCLIST");
        assert(INSTRCLIST(p));

        set_up_testdata(p, 4, "INSTRCLIST");
        assert(INSTRCLIST(p));
    }
    if (strcmp(testcase_name, "INSTRC") == 0)
    {
        set_up_testdata(p, 0, "INSTRC");
        assert(!INSTRC(p));

        set_up_testdata(p, 1, "INSTRC");
        assert(!INSTRC(p));

        set_up_testdata(p, 2, "INSTRC");
        assert(!INSTRC(p));

        printf("TESTED INSTRC\n");
    }

    if (strcmp(testcase_name, "VARNAME") == 0)
    {
        set_up_testdata(p, 0, "VARNAME");
        assert(VARNAME(p));

        set_up_testdata(p, 1, "VARNAME");
        assert(VARNAME(p));

        set_up_testdata(p, 2, "VARNAME");
        assert(!VARNAME(p));

        set_up_testdata(p, 3, "VARNAME");
        assert(!VARNAME(p));

        set_up_testdata(p, 4, "VARNAME");
        assert(!VARNAME(p));

        set_up_testdata(p, 5, "VARNAME");
        assert(!VARNAME(p));

        set_up_testdata(p, 6, "VARNAME");
        assert(!VARNAME(p));

        set_up_testdata(p, 7, "VARNAME");
        assert(!VARNAME(p));
    }

    if (strcmp(testcase_name, "INTEGER") == 0)
    {
        set_up_testdata(p, 0, "INTEGER");
        assert(INTEGER(p));

        set_up_testdata(p, 1, "INTEGER");
        assert(INTEGER(p));

        set_up_testdata(p, 2, "INTEGER");
        assert(INTEGER(p));

        set_up_testdata(p, 3, "INTEGER");
        assert(!INTEGER(p));

        set_up_testdata(p, 4, "INTEGER");
        assert(!INTEGER(p));
    }

    if (strcmp(testcase_name, "SET") == 0)
    {
        // printf("START\n");

        set_up_testdata(p, 0, "SET");
        assert(SET(p));

        set_up_testdata(p, 1, "SET");
        assert(!SET(p));

        set_up_testdata(p, 2, "SET");
        assert(SET(p));
    }
    if (strcmp(testcase_name, "PRINT") == 0)
    {
        set_up_testdata(p, 0, "PRINT");
        assert(PRINT(p));

        set_up_testdata(p, 1, "PRINT");
        assert(PRINT(p));

        set_up_testdata(p, 2, "PRINT");
        assert(!PRINT(p));

        set_up_testdata(p, 3, "PRINT");
        assert(!PRINT(p));
    }
    if (strcmp(testcase_name, "CREATE") == 0)
    {
        set_up_testdata(p, 0, "CREATE");
        assert(CREATE(p));

        set_up_testdata(p, 1, "CREATE");
        assert(!CREATE(p));

        set_up_testdata(p, 2, "CREATE");
        assert(!CREATE(p));

        set_up_testdata(p, 3, "CREATE");
        assert(CREATE(p));

        set_up_testdata(p, 4, "CREATE");
        assert(!CREATE(p));

        set_up_testdata(p, 5, "CREATE");
        assert(!CREATE(p));

        set_up_testdata(p, 6, "CREATE");
        assert(!CREATE(p));
    }
    if (strcmp(testcase_name, "LOOP") == 0)
    {
        set_up_testdata(p, 0, "LOOP");
        assert(LOOP(p));

        set_up_testdata(p, 1, "LOOP");
        assert(LOOP(p));

        set_up_testdata(p, 2, "LOOP");
        assert(LOOP(p));
    }

    if (strcmp(testcase_name, "POLISHLIST") == 0)
    {
        set_up_testdata(p, 0, "POLISHLIST");
        assert(POLISHLIST(p));

        set_up_testdata(p, 1, "POLISHLIST");
        assert(POLISHLIST(p));

        set_up_testdata(p, 2, "POLISHLIST");
        assert(POLISHLIST(p));
    }

    if (strcmp(testcase_name, "POLISH") == 0)
    {
        set_up_testdata(p, 0, "POLISH");
        assert(POLISH(p));

        set_up_testdata(p, 1, "POLISH");
        assert(POLISH(p));

        set_up_testdata(p, 2, "POLISH");
        assert(!POLISH(p));
    }

    if (strcmp(testcase_name, "PUSHDOWN") == 0)
    {
        set_up_testdata(p, 0, "PUSHDOWN");
        assert(PUSHDOWN(p));

        set_up_testdata(p, 1, "PUSHDOWN");
        assert(PUSHDOWN(p));

        set_up_testdata(p, 2, "PUSHDOWN");
        assert(!PUSHDOWN(p));
    }

    if (strcmp(testcase_name, "UNARYOP") == 0)
    {
        set_up_testdata(p, 0, "UNARYOP");
        assert(UNARYOP(p));

        set_up_testdata(p, 1, "UNARYOP");
        assert(UNARYOP(p));

        set_up_testdata(p, 2, "UNARYOP");
        assert(!UNARYOP(p));
    }

    if (strcmp(testcase_name, "STRING") == 0)
    {
        set_up_testdata(p, 0, "STRING");
        assert(STRING(p));

        set_up_testdata(p, 1, "STRING");
        assert(STRING(p));

        set_up_testdata(p, 2, "STRING");
        assert(!STRING(p));
    }

    if (strcmp(testcase_name, "BINARYOP") == 0)
    {
        set_up_testdata(p, 0, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 1, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 2, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 3, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 4, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 5, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 6, "BINARYOP");
        assert(BINARYOP(p));

        set_up_testdata(p, 7, "BINARYOP");
        assert(!BINARYOP(p));
    }

    if (strcmp(testcase_name, "ROWS") == 0)
    {
        set_up_testdata(p, 0, "ROWS");
        assert(ROWS(p));

        set_up_testdata(p, 1, "ROWS");
        assert(ROWS(p));

        set_up_testdata(p, 2, "ROWS");
        assert(!ROWS(p));
    }

    if (strcmp(testcase_name, "COLS") == 0)
    {
        set_up_testdata(p, 0, "COLS");
        assert(COLS(p));

        set_up_testdata(p, 1, "COLS");
        assert(COLS(p));

        set_up_testdata(p, 2, "COLS");
        assert(!COLS(p));
    }

    if (strcmp(testcase_name, "FILENAME") == 0)
    {
        set_up_testdata(p, 0, "FILENAME");
        assert(FILENAME(p));

        set_up_testdata(p, 1, "FILENAME");
        assert(FILENAME(p));

        set_up_testdata(p, 2, "FILENAME");
        assert(!FILENAME(p));
    }
    // free(p->variables);

    free(p);
}

void RUN_INTERP_TEST(char *testcase_name)
{
    Program *p = calloc(1, sizeof(Program));

    if (strcmp(testcase_name, "PROG") == 0)
    {
        printf("ASSERTIN*\n");
        set_up_testdata(p, 0, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 1, "PROG");
        assert(!PROG(p));

        set_up_testdata(p, 2, "PROG");
        assert(!PROG(p));

        set_up_testdata(p, 3, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 4, "PROG");
        assert(!PROG(p));
        free_struct(p);

        set_up_testdata(p, 5, "PROG");
        assert(!PROG(p));

        set_up_testdata(p, 6, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 7, "PROG");
        assert(PROG(p));

        printf("RUN_INTERP_TEST PROG\n");
    }

    free_struct(p);
    free(p);
}

void set_up_testdata(Program *p, int test_number, char *func_name)
{
    clear_previous_data(p);
#ifdef PARSER
    get_parser_data(p, test_number, func_name);
#elif INTERP
    get_interp_data(p, test_number, func_name);
    printf("INTERP TESTING\n");

#else
    printf("Need to add -DPARSER or -DINTERP in makefile\n");
#endif
}

void copy_test_data(Program *p, char test_instructions[ARR_RANGE][ARR_RANGE], int test_number)
{
    char *pch = strtok(test_instructions[test_number], " ");
    int i = 0;
    while (pch != NULL)
    {
        strcpy(p->wds[i++], pch);
        pch = strtok(NULL, " ");
    }
}

void get_parser_data(Program *p, int test_number, char *func_name)
{
    if (strcmp(func_name, "PROG") == 0)
    {

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
            {"1"},
            {"12"},   //invalid
            {"@123"}, //invalid
        };
        copy_test_data(p, test_instructions, test_number);
    }

    if (strcmp(func_name, "COLS") == 0)
    {

        char test_instructions[ARR_RANGE][ARR_RANGE] = {
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

void get_interp_data(Program *p, int test_number, char *func_name)
{
    if (strcmp(func_name, "PROG") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE] = {
            {"BEGIN { SET $A := 5 ; PRINT $A }"},                      //0: valid
            {"BEGIN { PRINT $A }"},                                    //1: invalid, $A is undefined
            {"BEGIN }"},                                               //2: invalid , missing {
            {"BEGIN { SET $Z := 9 ; }"},                               //3: valid
            {"BEGIN { SET $A := 5 ; PRINT $B }"},                      //4: invalid, $A is set but $B is undefined
            {"BEGIN {  PRINT $C SET $C := 5 ; }"},                     //5: invalid, print $C before $C is set
            {"BEGIN {  ONES 3 5 $A   PRINT \"ARRAY:\"  PRINT $A  } "}, //6: valid
            {"BEGIN {  READ \"lglider.arr\" $A  PRINT $A  } "},        //7: valid

        };
        copy_test_data(p, test_instructions, test_number);
    }
}

void clear_previous_data(Program *p)
{
    memset(p->wds, 0, sizeof(p->wds));
    memset(p->variables, 0, sizeof(p->variables));
    p->cw = 0;
}

void free_struct(Program *p)
{
    for (int i = 0; i < 26; i++)
    {
        if (p->variables[i] != 0)
        {
            for (int j = 0; j < p->variables[i]->y; j++)
            {
                free(p->variables[i]->num[j]);
            }
            free(p->variables[i]->num);
            free(p->variables[i]);
        }
    }
}