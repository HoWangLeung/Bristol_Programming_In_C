#include "../../test.h"
void test_polishlist(Program *p)
{
     set_up_testdata(p, 0, "POLISHLIST");
        assert(POLISHLIST(p));

        set_up_testdata(p, 1, "POLISHLIST");
        assert(POLISHLIST(p));

        set_up_testdata(p, 2, "POLISHLIST");
        assert(POLISHLIST(p));
}
