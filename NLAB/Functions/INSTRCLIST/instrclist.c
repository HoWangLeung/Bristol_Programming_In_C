#include "../nlab.h"

bool INSTRCLIST(Program *p)
{

    printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {
        interp_instrclist(p); //codes inside only excute when #ifdef INTERP
        return true;
    }
    if (!INSTRC(p))
    {

        ERROR("INSTRCLIST return false ....\n");
        return false;
    }
    if (strsame(p->wds[p->cw], "}") && strsame(p->wds[p->cw + 1], ""))
    {
        return true;
    }
    increment_cw(p);
    if (!INSTRCLIST(p))
    {
        return false;
    }

    return true;
}

void interp_instrclist(Program *p)
{
    (void)p;
#ifdef INTERP
    var *popped = pop(&p->stacknode);
    if (popped)
    {
        int popped_val = popped->num[0][0];
        int pos = popped->pos;
        int max_loop = popped->max_loop;
        int start = popped->start;
        int latest_val = p->variables[pos].num[0][0];
        if (popped_val != latest_val)
        {
            popped_val = latest_val;
        }
        if (popped_val < max_loop)
        {
            p->cw = start;
            INSTRCLIST(p);
        }
    }
#endif
}


