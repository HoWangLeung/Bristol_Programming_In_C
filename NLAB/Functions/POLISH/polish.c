#include "../nlab.h"

bool POLISH(Program *p)
{
    printCur(p, __LINE__);
    if (PUSHDOWN(p) == true)
    {

        return true;
    }
    else if (UNARYOP(p))
    {

        return true;
    }
    else if (BINARYOP(p))
    {

        return true;
    }
    else if (SORTOP(p))
    {

        return true;
    }
    else if (FLIPOP(p))
    {

        return true;
    }
    else if (ROTATEOP(p))
    {

        return true;
    }
    else
    {
        ERROR("POLISH ERROR:EXPECT PUSHDOWN | UNARYOP | BINARYOP ");
    }
}

