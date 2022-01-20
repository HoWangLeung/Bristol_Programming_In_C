#include "../../test.h"

void test_cols(Program *p)
{
     set_up_testdata(p, 0, "COLS");
        assert(COLS(p));

        set_up_testdata(p, 1, "COLS");
        assert(COLS(p));

        set_up_testdata(p, 2, "COLS");
        assert(!COLS(p));
}
