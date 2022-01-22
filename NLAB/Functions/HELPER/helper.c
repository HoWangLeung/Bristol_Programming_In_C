#include "../nlab.h"
#define FILESIZE 100
#define MAX_VAR_LENGTH 26
void printCur(Program *p, int line)
{

    (void)p;
    (void)line;
    //===
    //Commented out in production
    //====
    // printf("\033[0;31m");
    // printf("printCur() is %s ,line %d\n", p->wds[p->cw], line);
    // printf("\033[0m");
}
var get_value(Program *p)
{
    int pos = get_pos(p);
    if (!p->variables[pos].num)
    {
        // printf("UNDEFINED VARIABLED DETECTED\n");
    }
    return p->variables[pos];
}

int get_pos(Program *p)
{
    return p->wds[p->cw][1] - 'A';
}

void read_file(FILE *file_pointer, Program *p)
{
    char buffer[FILESIZE];
    int count = 0;
    while (fscanf(file_pointer, "%s", buffer) != EOF)
    {
        if (buffer[0] == '#')
        {
            fscanf(file_pointer, "%[^\n] ", buffer);
        }
        else
        {
            //printf("Buffer = %s\n", buffer);
            strcpy(p->wds[count++], buffer);
        }
    }
}

void clean_up(Program *p)
{
    for (int i = 0; i < MAX_VAR_LENGTH; i++)
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
    free(p);
}

bool LEFTBRACKET(Program *p)
{
    if (strsame(p->wds[p->cw], "{"))
    {
        return true;
    }

    return false;
}

bool STRING(Program *p)
{
    if (is_string(p->wds[p->cw]))
    {
        return true;
    }
    ERROR("INVALID STRING");
}

bool FILENAME(Program *p)
{

    if (STRING(p))
    {
        return true;
    }

    ERROR("MISSING FILENAME ");
}

bool VARNAME(Program *p)
{
    if (is_variable(p->wds[p->cw]))
    {
        return true;
    }
    ERROR("Expect $<A-Z> \n");
    return false;
}

void allocate_space(var *v, int y, int x)
{
    v->y = y;
    v->x = x;
    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));
}

bool set_value(Program *p, var *v)
{
    p->variables[p->pos].y = v->y;
    p->variables[p->pos].x = v->x;
    if (!p->variables[p->pos].num)
    {
        p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    }
    for (int y = 0; y < v->y; y++)
    {
        for (int x = 0; x < v->x; x++)
        {

            p->variables[p->pos].num[y][x] = v->num[y][x];
        }
    }
    return true;
}

void set_value_single(Program *p, int pos, int data)
{
     for (int y = 0; y < p->variables[pos].y; y++)
    {
        for (int x = 0; x < p->variables[pos].x; x++)
        {
            p->variables[pos].num[y][x] = data;
        }
    }
}

void increment_cw(Program *p)
{
    p->cw += 1;
}

bool INTEGER(Program *p)
{
    if (digits_only(p->wds[p->cw]))
    {

        return true;
    }
    return false;
}
