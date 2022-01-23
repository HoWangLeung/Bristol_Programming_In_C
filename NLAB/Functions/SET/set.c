#include "../nlab.h"
bool missing_colon(Program *p);
bool missing_equal(Program *p);
bool SET(Program *p)
{
    increment_cw(p);
    if (!VARNAME(p))
    {
        ERROR("Expected variable : \n");
        return false;
    }
    p->pos = get_pos(p);
    increment_cw(p);

    if (missing_colon(p))
    {
        ERROR("Expected symbol : \n");
    }

    if (missing_equal(p))
    {
        ERROR("Expected symbol = \n");
    }
    increment_cw(p);
    if (!POLISHLIST(p))
    {
        ERROR("NOT POLISH LIST, RETURN FALSE\n");
    }
    return true;
}

bool missing_colon(Program *p)
{
    return !p->wds[p->cw][0] || p->wds[p->cw][0] != ':';
}
bool missing_equal(Program *p)
{
    return !p->wds[p->cw][1] || p->wds[p->cw][1] != '=';
}
