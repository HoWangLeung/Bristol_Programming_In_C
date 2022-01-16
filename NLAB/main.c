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
    
    FILE *file_pointer = h_open(argv[1]);
    read_file(file_pointer, p);

    //  struct StackNode *root = NULL;
    p->stacknode = NULL;

    PROG(p);
    
    fclose(file_pointer);

    for (int i = 0; i < 26; i++)
    {
        if (p->variables[i].num != 0)
        {
            
            for (int j = 0; j < p->variables[i].y; j++)
            {
                free(p->variables[i].num[j]);
            }
            free(p->variables[i].num);
        }
    }

    // free(p->tmp.num);

    free(p);
    printf("END OF PROGRAM\n");
    return 0;
}
