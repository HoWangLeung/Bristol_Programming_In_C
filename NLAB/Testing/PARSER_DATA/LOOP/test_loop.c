#include "../../test.h"
void test_loop(Program *p)
{
      set_up_testdata(p, 0, "LOOP");
        assert(LOOP(p));

        set_up_testdata(p, 1, "LOOP");
        assert(LOOP(p));

        set_up_testdata(p, 2, "LOOP");
        assert(LOOP(p));
}
