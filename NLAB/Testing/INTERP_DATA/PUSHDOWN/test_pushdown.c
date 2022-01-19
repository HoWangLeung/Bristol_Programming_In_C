#include "../../test.h"
void test_pushdown(Program *p)
{
  set_up_testdata(p, 0, "PUSHDOWN");
        assert(PUSHDOWN(p));

        set_up_testdata(p, 1, "PUSHDOWN");
        assert(PUSHDOWN(p));

        set_up_testdata(p, 2, "PUSHDOWN");
        assert(!PUSHDOWN(p));
}
