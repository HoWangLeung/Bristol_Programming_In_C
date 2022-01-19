#include "../../Functions/nlab.h"


bool ROTATEOP(Program *p)
{
    printf("IN SORTOP\n");
    if (strsame(p->wds[p->cw], "ROTATE-L"))
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

        return true;
    }

    if (strsame(p->wds[p->cw], "ROTATE-R"))
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
        int N = v3->y;
        //ROTATION
        for (int i = 0; i < N / 2; i++)
        {
            for (int j = i; j < N - i - 1; j++)
            {
                int temp = v3->num[i][j];
                v3->num[i][j] = v3->num[N - 1 - j][i];
                v3->num[N - 1 - j][i] = v3->num[N - 1 - i][N - 1 - j];
                v3->num[N - 1 - i][N - 1 - j] = v3->num[j][N - 1 - i];
                v3->num[j][N - 1 - i] = temp;
            }
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    return false;
}
