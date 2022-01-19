#include "../nlab.h"

bool POLISHLIST(Program *p)
{

    if (p->wds[p->cw][0] == ';')
    {
#ifdef INTERP
        var *v = pop(&p->stacknode);
        if (v)
        {
            set_value(p, v);
        }
        free_stack_node(v);
#endif
        return true;
    }
    //

    if (p->wds[p->cw] && !p->wds[p->cw][0])
    {

        ERROR("EMPTY STRING, RETURN FALSE");
    }

    if (!POLISH(p))
    {

        ERROR("POLISH ERROR:\n");
        return false;
    }

    printCur(p, __LINE__);
    increment_cw(p);
    printCur(p, __LINE__);
    POLISHLIST(p);
    if (p->wds[p->cw][0] != ';')
    {

        return false;
    }

    return true;
}

