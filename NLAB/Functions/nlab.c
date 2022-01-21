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
