#include "../nlab.h"

bool INSTRC(Program *p)
{
    if (strsame(p->wds[p->cw], "PRINT"))
    {
        if (PRINT(p))
        {
            return true;
        }
    }
    if (strsame(p->wds[p->cw], "SET"))
    {
        if (SET(p))
        {
            return true;
        }
    }

    if (strsame(p->wds[p->cw], "ONES") || strsame(p->wds[p->cw], "READ"))
    {
        if (CREATE(p))
        {
            return true;
        }
    }

    if (strsame(p->wds[p->cw], "LOOP"))
    {
        if (LOOP(p))
        {
            return true;
        }
    }

    if (strsame(p->wds[p->cw], "IF"))
    {
        if (IF(p))
        {
            return true;
        }
    }
    ERROR("INSTRC : Expecting a PRINT or SET or CREATE or LOOP OR '}' OR ';' ?");
    return false;
}
