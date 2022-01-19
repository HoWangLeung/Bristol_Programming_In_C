
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
        test_prog(p);
    }

    if (strcmp(testcase_name, "INSTRCLIST") == 0)
    {
        test_instrclist(p);
    }

    if (strcmp(testcase_name, "INSTRC") == 0)
    {
        test_instrc(p);
    }

    if (strcmp(testcase_name, "VARNAME") == 0)
    {
        test_varname(p);
    }

    if (strcmp(testcase_name, "INTEGER") == 0)
    {
        test_integer(p);
    }

    if (strcmp(testcase_name, "SET") == 0)
    {
        // printf("START\n");

        test_set(p);
    }
    if (strcmp(testcase_name, "PRINT") == 0)
    {
        test_print(p);
    }
    if (strcmp(testcase_name, "CREATE") == 0)
    {
        test_create(p);
    }
    if (strcmp(testcase_name, "LOOP") == 0)
    {
        test_loop(p);
    }

    if (strcmp(testcase_name, "POLISHLIST") == 0)
    {
        test_polishlist(p);
    }

    if (strcmp(testcase_name, "POLISH") == 0)
    {
        test_polish(p);
    }

    if (strcmp(testcase_name, "PUSHDOWN") == 0)
    {
        test_pushdown(p);
    }

    if (strcmp(testcase_name, "UNARYOP") == 0)
    {
        test_unaryop(p);
    }

    if (strcmp(testcase_name, "STRING") == 0)
    {
       test_string(p);
    }

    if (strcmp(testcase_name, "BINARYOP") == 0)
    {
       test_binaryop(p);
    }

    if (strcmp(testcase_name, "ROWS") == 0)
    {
     test_rows(p);
    }

    if (strcmp(testcase_name, "COLS") == 0)
    {
       test_cols(p);
    }

    if (strcmp(testcase_name, "FILENAME") == 0)
    {
      test_filename(p);
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
