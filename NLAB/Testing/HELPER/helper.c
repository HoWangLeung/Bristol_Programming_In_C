#include "../test.h"


void copy_test_data(Program *p, char test_instructions[ARR_RANGE][ARR_RANGE], int test_number)
{
    char *pch = strtok(test_instructions[test_number], " ");
    int i = 0;
    while (pch != NULL)
    {
        strcpy(p->wds[i++], pch);
        pch = strtok(NULL, " ");
    }
}
void clear_previous_data(Program *p)
{
    memset(p->wds, 0, sizeof(p->wds));
    memset(p->variables, 0, sizeof(p->variables));
    p->cw = 0;
}
void free_struct(Program *p)
{
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
}
