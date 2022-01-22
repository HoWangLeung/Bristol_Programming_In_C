#include "nlab.h"
// #define INTERP

bool PROG(Program *p)
{
    int *cw = &p->cw;
    if (!strsame(p->wds[*cw], "BEGIN"))
    {
        ERROR("No BEGIN statement ?");
    }
    increment_cw(p);
    if (!strsame(p->wds[*cw], "{"))
    {
        ERROR("Expected {");
    }
    increment_cw(p);
    if (!INSTRCLIST(p))
    {
        return false;
    }
    return true;
}







