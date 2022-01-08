#include "Functions/nlab.h"
#define BIGSTR 1000

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s <file.nlb> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Program *p = ncalloc(1, sizeof(Program));
    printf("argv [1] = %s\n", argv[1]);
    FILE *file_pointer = h_open(argv[1]);
    read_file(file_pointer, p);
    int capacity = 10;
    p->stack = createStack(capacity);

    PROG(p);
    printf("<<<<<<<>>>>>>>>> PARSED OK !\n");
    fclose(file_pointer);

    for (int i = 0; i < 26; i++)
    {
        if (p->variables[i].num != 0)
        {
            printf("p->variables[i].y = %d\n", i);
            for (int j = 0; j < p->variables[i].y; j++)
            {
            free(p->variables[i].num[j]);
            }
            free(p->variables[i].num);
        }
    }

    // for (int i = 0; i < p->stack->capacity; i++)
    // {
    //     if (p->stack->arr[i].num)
    //     {

    //         // free(p->stack->arr[i].num[p->stack->arr[i].y]);

    //         // free(p->stack->arr[i].num);
    //     }
    // }

    // for (int i = 0; i < capacity; i++)
    // {

    //     if (p->stack->arr[i].num != 0)
    //     {
    //         printf("freeable = %d\n",p->stack->arr[i].num[0][0]);
    //         for (int j = 0; j < p->stack->arr[i].y; j++)
    //         {
    //             printf("j=%d\n",j);
    //             free(p->stack->arr[i].num[j]);

    //         }
    //         //  free(p->stack->arr[i].num);
    //     }
    //    // free(p->tmp.num[i]);
    // }

    // free(p->tmp.num);

    free(p->stack->arr);
    free(p->stack);
    free(p);
    return 0;
}
