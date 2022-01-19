#include "../../test.h"

void test_prog(Program *p){
        set_up_testdata(p, 0, "PROG");
        assert(PROG(p));

        set_up_testdata(p, 1, "PROG");
        assert(PROG(p));

        set_up_testdata(p, 2, "PROG");
        assert(!PROG(p));

        set_up_testdata(p, 3, "PROG");
        assert(PROG(p));
}
