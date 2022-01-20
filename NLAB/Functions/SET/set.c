#include "../nlab.h"

bool SET(Program *p)
{
    increment_cw(p);
    if (!VARNAME(p))
    {
        // printf("HIIHIHIHIH\n");
        ERROR("Expected variable : \n");
        return false;
    }
    p->pos = get_pos(p);
    increment_cw(p);

    if (!p->wds[p->cw][0] || p->wds[p->cw][0] != ':')
    {
        ERROR("Expected symbol : \n");
    }

    if (!p->wds[p->cw][1] || p->wds[p->cw][1] != '=')
    {
        ERROR("Expected symbol = \n");
    }
    increment_cw(p);
    if (!POLISHLIST(p))
    {
        printf("NOT POLISH LIST, RETURN FALSE\n");
        return false;
    }
    return true;
}
