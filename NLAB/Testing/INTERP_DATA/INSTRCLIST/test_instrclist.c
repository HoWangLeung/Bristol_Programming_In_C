#include "../../test.h"
void test_instrclist(Program *p)
{
    set_up_testdata(p, 0, "INSTRCLIST");
    assert(INSTRCLIST(p));

    set_up_testdata(p, 1, "INSTRCLIST");
    assert(INSTRCLIST(p));

    set_up_testdata(p, 2, "INSTRCLIST");
    assert(INSTRCLIST(p));

    set_up_testdata(p, 3, "INSTRCLIST");
    assert(INSTRCLIST(p));

    set_up_testdata(p, 4, "INSTRCLIST");
    assert(INSTRCLIST(p));
}
