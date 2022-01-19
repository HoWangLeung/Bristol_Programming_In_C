#include "../../test.h"
void test_create(Program *p)
{
    set_up_testdata(p, 0, "CREATE");
    assert(CREATE(p));

    set_up_testdata(p, 1, "CREATE");
    assert(!CREATE(p));

    set_up_testdata(p, 2, "CREATE");
    assert(!CREATE(p));

    set_up_testdata(p, 3, "CREATE");
    assert(CREATE(p));

    set_up_testdata(p, 4, "CREATE");
    assert(!CREATE(p));

    set_up_testdata(p, 5, "CREATE");
    assert(!CREATE(p));

    set_up_testdata(p, 6, "CREATE");
    assert(!CREATE(p));
}
