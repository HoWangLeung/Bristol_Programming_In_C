#include "../../Functions/nlab.h"

bool FLIPOP(Program *p)
{
    printf("IN SORTOP\n");
    if (strsame(p->wds[p->cw], "FLIP"))
    {
        printf("......IN FLIP-SORT\n");
        var *v3 = calloc(1, sizeof(var));

        var *v1 = pop(&p->stacknode);

        printf("v1 num = %d\n", v1->num[0][0]);

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

        for (int i = 0; i < v3->y; i++)
            qsort(v3->num, v3->y, sizeof(int *), flipcomp);

        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    return false;
}

int flipcomp(const void *firstArg, const void *secondArg)
{
    /* get the values of the arguments */
    int first = *(int *)firstArg;
    int second = *(int *)secondArg;

    /* return the value as expected by the qsort() method */
    if (first < second)
    {
        return 1;
    }
    else if (second < first)
    {
        return -1;
    }

    return 0;
}

