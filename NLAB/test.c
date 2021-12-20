// #include "Unity/unity.h"
#include "Functions/nlab.h"
#define ARR_RANGE 100

void set_up_testdata(Program *p, int test_number, char *func_name);
void RUN_TEST(char *testcase_name);

int main(void)
{
    RUN_TEST("VARNAME");
    RUN_TEST("INTEGER");
    RUN_TEST("PROG");
    RUN_TEST("INSTRCLIST");
    RUN_TEST("INSTRC");
     RUN_TEST("SET");

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

    if (strcmp(testcase_name, "INSTRCLIST") == 0)
    {
        set_up_testdata(p, 0, "INSTRCLIST");
        assert(INSTRCLIST(p));
    }
    if (strcmp(testcase_name, "INSTRC") == 0)
    {
        // printf("START\n");

        set_up_testdata(p, 0, "INSTRC");
        assert(INSTRC(p));
    }

    if (strcmp(testcase_name, "SET") == 0)
    {
        // printf("START\n");

        set_up_testdata(p, 0, "SET");
        assert(SET(p));

        set_up_testdata(p, 1, "SET");
        assert(SET(p));
    }

    free(p);
}

void set_up_testdata(Program *p, int test_number, char *func_name)
{
    p->cw = 0;

    if (strcmp(func_name, "VARNAME") == 0)
    {
        char test_instructions[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"PRINT", "$A"}, //0: valid
            {"PRINT", "$M"}, //1: valid
            {"PRINT", "$1"}, //2: invalid: not A-Z
            {"PRINT", "$@"}, //3: invalid: not A-Z
            {"PRINT", "$!"}, //4: invalid: not A-Z
            {"PRINT", "*1"}, //5: invalid: expected '$' but received '*'
            {"PRINT", "*@"}, //6: invalid: expected '$' but received '*'
            {"PRINT", "1"},  //7: invalid: missing '$'
        };
        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions[test_number][i]);
        }
    }

    if (strcmp(func_name, "INTEGER") == 0)
    {
        char test_instructions_integer[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"ROW", "1"},   //0: valid 1 digit
            {"ROW", "12"},  //1: valid 2 digits
            {"ROW", "123"}, //2: valid 3 digits
            {"ROW", "abc"}, //2: invalid, not [0-9]+
            {"ROW", "!@#"}, //2: invalid. not [0-9]+
        };

        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions_integer[test_number][i]);
        }
    }
    if (strcmp(func_name, "PROG") == 0)
    {
        char test_instructions_integer[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"BEGIN", "{", "}"},                //0: valid
            {"BEGIN", "{", "PRINT", "$A", "}"}, //0: valid
            {"BEGIN", "}"},                     //0: valid 1 digit
        };

        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions_integer[test_number][i]);
        }
    }

    if (strcmp(func_name, "INSTRCLIST") == 0)
    {
        char test_instructions_integer[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"PRINT", "$A", "}"},
        };

        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions_integer[test_number][i]);
        }
    }

    if (strcmp(func_name, "INSTRC") == 0)
    {
        char test_instructions_integer[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"PRINT", "$A"},
        };

        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions_integer[test_number][i]);
        }
    }

    if (strcmp(func_name, "SET") == 0)
    {
        char test_instructions_integer[ARR_RANGE][ARR_RANGE][ARR_RANGE] = {
            {"SET", "$A", ":=", "2", ";"},
            {"SET",
             "$A",
             ":=",
             "2"},
        };

        for (int i = 0; i < ARR_RANGE; i++)
        {
            strcpy(p->wds[i], test_instructions_integer[test_number][i]);
        }
    }
}
