
#include "test.h"
int main(void)
{
#ifdef PARSER
    RUN_PARSER_TEST("PROG");
    RUN_PARSER_TEST("INSTRCLIST");
    RUN_PARSER_TEST("INSTRC");
    RUN_PARSER_TEST("SET");
    RUN_PARSER_TEST("PRINT");
    RUN_PARSER_TEST("CREATE");
    RUN_PARSER_TEST("LOOP");
    RUN_PARSER_TEST("POLISHLIST");
    RUN_PARSER_TEST("VARNAME");
    RUN_PARSER_TEST("INTEGER");
    RUN_PARSER_TEST("POLISH");
    RUN_PARSER_TEST("PUSHDOWN");
    RUN_PARSER_TEST("UNARYOP");
    RUN_PARSER_TEST("BINARYOP");
    RUN_PARSER_TEST("STRING");
    RUN_PARSER_TEST("ROWS");
    RUN_PARSER_TEST("COLS");
    RUN_PARSER_TEST("FILENAME");
    printf("TESTED PARSER\n");
#endif

#ifdef INTERP
    RUN_INTERP_TEST("PROG");
    printf("PASSED INTERP TESTING\n");
#endif
    printf("END OF TESTING\n");
    return 0;
}

void RUN_PARSER_TEST(char *testcase_name)
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
        free_struct(p);

        set_up_testdata(p, 8, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 9, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 10, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 11, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 12, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 13, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 14, "PROG");
        assert(PROG(p));
        free_struct(p);

        set_up_testdata(p, 15, "PROG");
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
    printf("B4 GETTING DATA\n");
    printf("test number = %d, %s \n", test_number, func_name);
    get_parser_data(p, test_number, func_name);
    printf("RETRIEVED DATA\n");
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
       // printf("%d\n", p->variables[i].num);
        if (p->variables[i].num != 0)
        {
            for (int j = 0; j < p->variables[i].y; j++)
            {
                free(p->variables[i].num[j]);
            }
            free(p->variables[i].num);
        }
    }
} 
