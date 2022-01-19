#include "../../test.h"
void test_filename(Program *p)
{
    set_up_testdata(p, 0, "FILENAME");
    assert(FILENAME(p));

    set_up_testdata(p, 1, "FILENAME");
    assert(FILENAME(p));

    set_up_testdata(p, 2, "FILENAME");
    assert(!FILENAME(p));
}
