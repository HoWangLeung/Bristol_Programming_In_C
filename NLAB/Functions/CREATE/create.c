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
#ifdef INTERP
                interp_create(p);
#endif
                return true;
            }
        }
    }
    if (FILENAME(p))
    {
        increment_cw(p);
        if (VARNAME(p))
        {
#ifdef INTERP
            interp_create_file(p);
#endif

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
}

void interp_create(Program *p)
{
    (void)p;

    int y = atoi(p->wds[p->cw - 2]);
    int x = atoi(p->wds[p->cw - 1]);
    int pos = get_pos(p);
    p->pos = pos;
    allocate_space(&p->variables[pos], y, x);
    set_value_single(p,p->pos,1);
    // for (int y = 0; y < p->variables[pos].y; y++)
    // {
    //     for (int x = 0; x < p->variables[pos].x; x++)
    //     {
    //         p->variables[pos].num[y][x] = 1;
    //     }
    // }
}
