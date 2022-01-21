#include "../nlab.h"

bool PUSHDOWN(Program *p)
{
    printCur(p, __LINE__);
    if (digits_only(p->wds[p->cw]))
    {
        interp_pushdown_digits(p);
        return true;
    }

    if (is_variable(p->wds[p->cw]))
    {
        interp_pushdown_variable(p);
        return true;
    }
    return false;
}

void interp_pushdown_digits(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v = calloc(1, sizeof(var));
    allocate_space(v, 1, 1);

    for (int y = 0; y < v->y; y++)
    {
        for (int x = 0; x < v->x; x++)
        {
            v->num[y][x] = atoi(p->wds[p->cw]);
        }
    }

    push(&p->stacknode, v);
#endif
}

void interp_pushdown_variable(Program *p)
{
    (void)p;
#ifdef INTERP
    //(p, __LINE__);
    var val = get_value(p);

    var *v = calloc(1, sizeof(var));
    // v->y = val.y;
    // v->x = val.x;
    // v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));

    allocate_space(v, val.y, val.x);

    for (int y = 0; y < v->y; y++)
    {
        for (int x = 0; x < v->x; x++)
        {
            v->num[y][x] = val.num[y][x];
        }
    }
    push(&p->stacknode, v);
#endif
}
