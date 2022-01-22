#include "../nlab.h"

void handle_set_value(Program *p);
bool missing_semi_colon(Program *p);
bool missing_string(Program *p);

bool POLISHLIST(Program *p)
{
    if (p->wds[p->cw][0] == ';')
    {
#ifdef INTERP
        handle_set_value(p);
#endif
        return true;
    }
    if (missing_string(p))
    {
        ERROR("EMPTY STRING, RETURN FALSE");
    }
    if (!POLISH(p))
    {
        ERROR("POLISH ERROR:\n");
        return false;
    }
    increment_cw(p);
    POLISHLIST(p);
    if (missing_semi_colon(p))
    {
        return false;
    }
    return true;
}

void handle_set_value(Program *p)
{
    var *v = pop(&p->stacknode);
    if (v)
    {
        set_value(p, v);
    }
    free_stack_node(v);
}

bool missing_semi_colon(Program *p)
{
    return p->wds[p->cw][0] != ';';
}

bool missing_string(Program *p)
{
    return p->wds[p->cw] && !p->wds[p->cw][0];
}
