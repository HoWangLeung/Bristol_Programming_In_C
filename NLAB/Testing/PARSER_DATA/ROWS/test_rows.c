#include "../../test.h"
void test_rows(Program *p)
{
     set_up_testdata(p, 0, "ROWS");
        assert(ROWS(p));

        set_up_testdata(p, 1, "ROWS");
        assert(ROWS(p));

        set_up_testdata(p, 2, "ROWS");
        assert(!ROWS(p));
}
