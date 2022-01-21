#include "../nlab.h"
void free_tmp(var *tmp);
bool UNARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "U-NOT"))
    {
        interp_u_not(p); //codes within excutes only when INTERP is defined
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
        interp_u_eightcount(p); //codes within excutes only when INTERP is defined
        return true;
    }
    return false;
}

void interp_u_eightcount(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v3 = calloc(1, sizeof(var));
    var *v1 = pop(&p->stacknode);
    var *tmp = calloc(1, sizeof(var));

    // v3->y = v1->y;
    // v3->x = v1->x;
    tmp->y = v1->y;
    tmp->x = v1->x;
    allocate_space(v3, v1->y, v1->x);
    // allocate_space(tmp, v1->y + 2, v1->x + 2);

    // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
    tmp->num = (int **)n2dcalloc(v3->y + 2, v3->x + 2, sizeof(int *));
    for (int y = 0; y < tmp->y; y++)
    {
        for (int x = 0; x < tmp->x; x++)
        {
            tmp->num[y + 1][x + 1] = v1->num[y][x];
        }
    }

    //each element represents the offset for one of the eight directions
    int offset[8][2] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1}};

    for (int y = 1; y < tmp->y + 1; y++)
    {
        for (int x = 1; x < tmp->x + 1; x++)
        {
            int count = 0;
            for (int k = 0; k < 8; k++)
            {
                if (tmp->num[y + offset[k][1]][x + offset[k][0]] >= 1)
                {
                    count += 1;
                    v3->num[y - 1][x - 1] = count;
                }
            }
        }
    }
    push(&p->stacknode, v3);
    free_stack_node(v1);
    free_tmp(tmp);
#endif
}

void interp_u_not(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v3 = calloc(1, sizeof(var));
    var *v1 = pop(&p->stacknode);

    // v3->y = v1->y;
    // v3->x = v1->x;
    // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
    allocate_space(v3, v1->y, v1->x);
    for (int y = 0; y < v3->y; y++)
    {
        for (int x = 0; x < v3->y; x++)
        {
            v3->num[y][x] = ~v1->num[y][x];
        }
    }

    push(&p->stacknode, v3);
    free_stack_node(v1);
#endif
}

void free_tmp(var *tmp)
{
    for (int y = 0; y < tmp->y + 2; y++)
    {
        free(tmp->num[y]);
    }
    free(tmp->num);
    free(tmp);
}
