#include "../../test.h"

void test_binaryop(Program *p)
{
    set_up_testdata(p, 0, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 1, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 2, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 3, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 4, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 5, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 6, "BINARYOP");
    assert(BINARYOP(p));

    set_up_testdata(p, 7, "BINARYOP");
    assert(!BINARYOP(p));
}
