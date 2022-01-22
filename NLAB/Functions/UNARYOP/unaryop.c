#include "../nlab.h"
void free_tmp(var *tmp);
void push_and_free(Program *p, var *v1, var *v3);
void count_eight(var *tmp, var *v3);
void calculate_not(var *v1, var *v3);
void pad_with_zeros(var *v1, var *tmp);
bool UNARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "U-NOT"))
    {
#ifdef INTERP
        interp_u_not(p);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
#ifdef INTERP
        interp_u_eightcount(p);
#endif
        return true;
    }
    return false;
}

void interp_u_eightcount(Program *p)
{
    var *v3 = calloc(1, sizeof(var));
    var *v1 = pop(&p->stacknode);
    var *tmp = calloc(1, sizeof(var));
    tmp->y = v1->y;
    tmp->x = v1->x;
    allocate_space(v3, v1->y, v1->x);
    tmp->num = (int **)n2dcalloc(v3->y + 2, v3->x + 2, sizeof(int *));
    pad_with_zeros(v1, tmp);
    count_eight(tmp, v3);
    push_and_free(p, v1, v3);
    free_tmp(tmp);
}

void interp_u_not(Program *p)
{
    var *v3 = calloc(1, sizeof(var));
    var *v1 = pop(&p->stacknode);
    allocate_space(v3, v1->y, v1->x);
    calculate_not(v1, v3);
    push_and_free(p, v1, v3);
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

void push_and_free(Program *p, var *v1, var *v3)
{
    push(&p->stacknode, v3);
    free_stack_node(v1);
}

void count_eight(var *tmp, var *v3)
{
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
}

void calculate_not(var *v1, var *v3)
{
    for (int y = 0; y < v3->y; y++)
    {
        for (int x = 0; x < v3->y; x++)
        {
            v3->num[y][x] = ~v1->num[y][x];
        }
    }
}

void pad_with_zeros(var *v1, var *tmp)
{
    for (int y = 0; y < tmp->y; y++)
    {
        for (int x = 0; x < tmp->x; x++)
        {
            tmp->num[y + 1][x + 1] = v1->num[y][x];
        }
    }
}

