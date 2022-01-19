#include "../nlab.h"

bool LOOP(Program *p)
{
//SET UP
#ifdef INTERP
    var *v = calloc(1, sizeof(var));
    v->y = 1;
    v->x = 1;
    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));
    v->start = p->cw;
#endif
    increment_cw(p);
    if (!VARNAME(p))
    {
        printf("VAR NOT OK\n");
        ERROR("INVALID VARNAME");
    }
#ifdef INTERP
    //INTERP
    v->pos = get_pos(p);
    p->pos = v->pos;
    p->variables[p->pos].y = 1;
    p->variables[p->pos].x = 1;
    //===========================================SET I INITIAL VALUE
    if (!p->variables[p->pos].num)
    {
        p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    }

    if (p->variables[p->pos].max_loop == 0 || p->variables[p->pos].num[0][0] < p->variables[p->pos].max_loop)
    {
        p->variables[p->pos].num[0][0] += 1;
        v->num[0][0] = p->variables[p->pos].num[0][0];
    }
    else if (p->variables[p->pos].num[0][0] == p->variables[p->pos].max_loop)
    {

        v->num[0][0] = (p->variables[p->pos].num[0][0] % p->variables[p->pos].max_loop) + 1;
        p->variables[p->pos].num[0][0] = v->num[0][0];
    }

    //===========================================SET I INITIAL VALUE
#endif
    increment_cw(p);
    if (!INTEGER(p))
    {
        printf("INTEGER NOT OK\n");
        ERROR("INVALID INTEGER");
    }
#ifdef INTERP
    v->max_loop = atoi(p->wds[p->cw]);
    p->variables[p->pos].max_loop = v->max_loop;

    push(&p->stacknode, v);

    increment_cw(p);
    if (!LEFTBRACKET(p))
    {
        printf("LEFT BRACKET NOT OK\n");
        ERROR("INVALID INTEGER");
    }
#endif
    increment_cw(p);
    INSTRCLIST(p);
#ifdef INTERP
    free_stack_node(v);
#endif
    return true;
}
