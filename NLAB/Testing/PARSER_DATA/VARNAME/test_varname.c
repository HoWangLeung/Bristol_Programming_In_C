#include "../../test.h"
void get_varname_data(Program *p, int test_number);
void get_varname_data(Program *p, int test_number)
{
        clear_previous_data(p);
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
void test_varname(Program *p)
{
        get_varname_data(p, 0);
        assert(VARNAME(p));

        get_varname_data(p, 1);
        assert(VARNAME(p));

        get_varname_data(p, 2);
        assert(!VARNAME(p));

        get_varname_data(p, 3);
        assert(!VARNAME(p));

        get_varname_data(p, 4);
        assert(!VARNAME(p));

        get_varname_data(p, 5);
        assert(!VARNAME(p));

        get_varname_data(p, 6);
        assert(!VARNAME(p));

        get_varname_data(p, 7);
        assert(!VARNAME(p));
}
