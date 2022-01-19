#include "../../test.h"
void test_unaryop(Program *p)
{
      set_up_testdata(p, 0, "UNARYOP");
        assert(UNARYOP(p));

        set_up_testdata(p, 1, "UNARYOP");
        assert(UNARYOP(p));

        set_up_testdata(p, 2, "UNARYOP");
        assert(!UNARYOP(p));
}
