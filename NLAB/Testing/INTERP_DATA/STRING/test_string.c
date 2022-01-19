#include "../../test.h"
void test_string(Program *p)
{
    set_up_testdata(p, 0, "STRING");
        assert(STRING(p));

        set_up_testdata(p, 1, "STRING");
        assert(STRING(p));

        set_up_testdata(p, 2, "STRING");
        assert(!STRING(p));
}
