#include "../../test.h"
void test_set(Program *p)
{
        set_up_testdata(p, 0, "SET");
        assert(SET(p));

        set_up_testdata(p, 1, "SET");
        assert(!SET(p));

        set_up_testdata(p, 2, "SET");
        assert(SET(p));
}
