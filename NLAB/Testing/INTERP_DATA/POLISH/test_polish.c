#include "../../test.h"
void test_polish(Program *p)
{
   set_up_testdata(p, 0, "POLISH");
        assert(POLISH(p));

        set_up_testdata(p, 1, "POLISH");
        assert(POLISH(p));

        set_up_testdata(p, 2, "POLISH");
        assert(!POLISH(p));
}
