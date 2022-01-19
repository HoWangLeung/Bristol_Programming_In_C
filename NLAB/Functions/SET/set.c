#include "../nlab.h"

bool SET(Program *p)
{
    increment_cw(p);
    if (!VARNAME(p))
    {
        return false;
    }
    int pos = get_pos(p);
    p->pos = pos;
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

void interp_pushdown_digits(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v = calloc(1, sizeof(var));
    v->y = 1;
    v->x = 1;
    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));

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
    v->y = val.y;
    v->x = val.x;
    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));

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
