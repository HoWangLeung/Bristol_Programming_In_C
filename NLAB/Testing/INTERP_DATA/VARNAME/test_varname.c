#include "../../test.h"
void test_varname(Program *p)
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
