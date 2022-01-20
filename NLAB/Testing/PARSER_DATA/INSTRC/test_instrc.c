#include "../../test.h"
void test_instrc(Program *p)
{
    set_up_testdata(p, 0, "INSTRC");
    assert(!INSTRC(p));

    set_up_testdata(p, 1, "INSTRC");
    assert(!INSTRC(p));

    set_up_testdata(p, 2, "INSTRC");
    assert(!INSTRC(p));

    printf("TESTED INSTRC\n");
}
