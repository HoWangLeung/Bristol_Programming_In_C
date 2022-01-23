#include "../../Functions/nlab.h"
void flip(Program *p);
bool FLIPOP(Program *p)
{

    if (strsame(p->wds[p->cw], "FLIP"))
    {
#ifdef INTERP
        flip(p);
#endif
        return true;
    }

    return false;
}

void flip(Program *p)
{
    var *v3 = calloc(1, sizeof(var));

    var *v1 = pop(&p->stacknode);

    v3->y = v1->y;
    v3->x = v1->x;
    v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
    for (int y = 0; y < v3->y; y++)
    {
        for (int x = 0; x < v3->x; x++)
        {
            v3->num[y][x] = v1->num[y][x];
        }
    }

    for (int y = 0; y < v3->y; y++)
    {
        for (int x = 0; x < v3->x; x++)
        {
            v3->num[y][x] = v1->num[v3->y-1-y][x];
        }
    }

    push(&p->stacknode, v3);
    free_stack_node(v1);
}

 