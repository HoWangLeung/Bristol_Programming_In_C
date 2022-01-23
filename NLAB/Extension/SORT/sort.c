#include "../../Functions/nlab.h"

bool SORTOP(Program *p)
{

    if (strsame(p->wds[p->cw], "B-SORT"))
    {
#ifdef INTERP
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

        for (int k = 0; k < v3->y; k++)
        {
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = y + 1; x < v3->x; x++)
                {
                    if (v3->num[k][y] > v3->num[k][x])
                    {
                        int swap = v3->num[k][y];
                        v3->num[k][y] = v3->num[k][x];
                        v3->num[k][x] = swap;
                    }
                }
            }
        }
        push(&p->stacknode, v3);
        free_stack_node(v1);
#endif
        return true;
    }

        return false;
}
