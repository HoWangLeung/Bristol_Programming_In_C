#include "../nlab.h"

bool CREATE(Program *p)
{
    increment_cw(p);
    if (ROWS(p))
    {
        increment_cw(p);
        if (COLS(p))
        {
            increment_cw(p);
            if (VARNAME(p))
            {
                interp_create(p);
                return true;
            }
        }
    }
    if (FILENAME(p))
    {
        increment_cw(p);
        if (VARNAME(p))
        {
            interp_create_file(p);
            return true;
        }
    }
    ERROR("INVALID CREATE");
}

bool ROWS(Program *p)
{
    if (digits_only(p->wds[p->cw]))
    {
        return true;
    }
    return false;
}

bool COLS(Program *p)
{
    if (digits_only(p->wds[p->cw]))
    {
        return true;
    }
    ERROR("Eexpect COLS\n");
    return false;
}

void interp_create_file(Program *p)
{
    (void)p;
#ifdef INTERP
    int pos = get_pos(p);
    p->pos = pos;
    char *filename = p->wds[p->cw - 1];
    filename++;                         // remove first double quote
    filename[strlen(filename) - 1] = 0; // remove last double quote
    FILE *file_pointer = h_open(filename);
    int array[100][100];
    int height, width;
    if (fscanf(file_pointer, "%d%d", &height, &width) != 2)
    {
        exit(1);
    }

    allocate_space(&p->variables[pos], height, width);
    // p->variables[pos].y = height;
    // p->variables[pos].x = width;
    // p->variables[pos].num = (int **)n2dcalloc(p->variables[pos].y, p->variables[pos].x, sizeof(int *));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (fscanf(file_pointer, "%d", &array[y][x]) != 1)
            {
                exit(1);
            }
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            p->variables[pos].num[y][x] = array[y][x];
            //
        }
#if !defined TESTMODE
        // printf("\n");
#endif
    }
    //printf("close file pointer\n");
    fclose(file_pointer);
#endif
}

void interp_create(Program *p)
{
    (void)p;
#ifdef INTERP
    int y = atoi(p->wds[p->cw - 2]);
    int x = atoi(p->wds[p->cw - 1]);
    // #ifdef INTERP
    int pos = get_pos(p);

    p->pos = pos;
    allocate_space(&p->variables[pos], y, x);
    // p->variables[pos].y = y;
    // p->variables[pos].x = x;
    // p->variables[pos].num = (int **)n2dcalloc(p->variables[pos].y, p->variables[pos].x, sizeof(int *));

    for (int y = 0; y < p->variables[pos].y; y++)
    {
        for (int x = 0; x < p->variables[pos].x; x++)
        {
            p->variables[pos].num[y][x] = 1;
        }
    }
#endif
}
