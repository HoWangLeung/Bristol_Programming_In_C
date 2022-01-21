#include "../nlab.h"

bool PRINT(Program *p)
{
    increment_cw(p);

    if (is_variable(p->wds[p->cw]))
    {

#if defined INTERP
        var v = get_value(p);
        if (!print_variable(v))
        {
            ERROR("undefined varialbe ?\n");
            return false;
        }

#endif

        return true;
    }

    if (is_string(p->wds[p->cw]))
    {

        char *word = p->wds[p->cw];
        word++;                     // remove first double quote
        word[strlen(word) - 1] = 0; // remove last double quote

#if defined INTERP && !defined TESTMODE
        printf("%s\n", word);
#endif

        return true;
    }
    ERROR("PRINT failure: Check the format ");
    return false;
}

bool print_variable(var v)
{
#if !defined TESTMODE
    printf("===>printings variables:\n");
#endif
    if (v.num != 0)
    {
        for (int y = 0; y < v.y; y++)
        {
            for (int x = 0; x < v.x; x++)
            {
#if !defined TESTMODE
                printf("%d", v.num[y][x]);
#endif
            }
#if !defined TESTMODE
            printf("\n");
#endif
        }
        return true;
    }

    else
    {
        // printf("NOT PRINTING ANYTHING !!! \n");
        ERROR("Undefined Variable ");
    };

    return false;
}
