#include "../../Functions/nlab.h"

bool ROTATEOP(Program *p)
{

    if (strsame(p->wds[p->cw], "ROTATE-L"))
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
        int N = v3->y;
        //ROTATION
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = x; y < N - x - 1; y++)
            {
                int temp = v3->num[x][y];
                v3->num[x][y] = v3->num[y][N - 1 - x];
                v3->num[y][N - 1 - x] = v3->num[N - 1 - x][N - 1 - y];
                v3->num[N - 1 - x][N - 1 - y] = v3->num[N - 1 - y][x];
                v3->num[N - 1 - y][x] = temp;
            }
        }
        push(&p->stacknode, v3);
        free_stack_node(v1);
#endif

        return true;
    }

    if (strsame(p->wds[p->cw], "ROTATE-R"))
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
        int N = v3->y;
        //ROTATION
        for (int y = 0; y < N / 2; y++)
        {
            for (int x = y; x < N - y - 1; x++)
            {
                int tmp = v3->num[y][x];
                v3->num[y][x] = v3->num[N - 1 - x][y];
                v3->num[N - 1 - x][y] = v3->num[N - 1 - y][N - 1 - x];
                v3->num[N - 1 - y][N - 1 - x] = v3->num[x][N - 1 - y];
                v3->num[x][N - 1 - y] = tmp;
            }
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);
#endif

        return true;
    }

    return false;
}
