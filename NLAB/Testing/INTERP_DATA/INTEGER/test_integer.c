#include "../../test.h"
void test_integer(Program *p)
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
