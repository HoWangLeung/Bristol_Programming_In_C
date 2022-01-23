#include "../nlab.h"

void handle_loop(Program *p, var *v);
void handle_push(Program *p, var *v);
var *set_up_loop(Program *p);

bool LOOP(Program *p)
{
//SET UP
#ifdef INTERP
    var*v = set_up_loop(p);
#endif
    increment_cw(p);
    if (!VARNAME(p))
    {
        ERROR("INVALID VARNAME");
    }
#ifdef INTERP
    handle_loop(p, v);
#endif

    increment_cw(p);
    if (!INTEGER(p))
    {
        ERROR("INVALID INTEGER");
    }
#ifdef INTERP
    handle_push(p, v);
#endif
    increment_cw(p);
    if (!LEFTBRACKET(p))
    {
        ERROR("INVALID INTEGER");
    }
    increment_cw(p);
    INSTRCLIST(p);
#ifdef INTERP
    free_stack_node(v);
#endif
    return true;
}

var *set_up_loop(Program *p)
{
    var *v = calloc(1, sizeof(var));
    allocate_space(v, 1, 1);
    v->start = p->cw;
    return v;
}

void handle_push(Program *p, var *v)
{
    v->max_loop = atoi(p->wds[p->cw]);
    p->variables[p->pos].max_loop = v->max_loop;
    push(&p->stacknode, v);
}

void handle_loop(Program *p, var *v)
{
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
}
