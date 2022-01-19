#include "../../test.h"
void test_print(Program *p)
{
     set_up_testdata(p, 0, "PRINT");
        assert(PRINT(p));

        set_up_testdata(p, 1, "PRINT");
        assert(PRINT(p));

        set_up_testdata(p, 2, "PRINT");
        assert(!PRINT(p));

        set_up_testdata(p, 3, "PRINT");
        assert(!PRINT(p));
}

