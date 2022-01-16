#include "nlab.h"
#define FILESIZE 100
// #define INTERP

bool PROG(Program *p)
{
    if (!strsame(p->wds[p->cw], "BEGIN"))
    {
        ERROR("No BEGIN statement ?");
    }
    p->cw = p->cw + 1;

    if (!strsame(p->wds[p->cw], "{"))
    {
        ERROR("Expected {");
    }
    p->cw = p->cw + 1;
    if (!INSTRCLIST(p))
    {
        printf("SOMETHING WORONG IN INSTRCLIST\n");
        return false;
    }

    return true;
}

bool INSTRCLIST(Program *p)
{

    printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {

        var *popped = pop(&p->stacknode);
        if (popped)
        {

            if (popped->num[0][0] != p->variables[popped->pos].num[0][0])
            {

                popped->num[0][0] = p->variables[popped->pos].num[0][0];
            }
            if (popped->num[0][0] < popped->max_loop)
            {

                p->cw = popped->start;
                INSTRCLIST(p);
            }
        }

        return true;
    }
    if (!INSTRC(p))
    {
        printf("INSTRCLIST(): INSTRC error  \n");

        ERROR("INSTRCLIST return false ....\n");

        return false;
    }

    if (strsame(p->wds[p->cw], "}") && strsame(p->wds[p->cw + 1], ""))
    {

        return true;
    }
    p->cw = p->cw + 1;

    if (!INSTRCLIST(p))
    {
        return false;
    }

    return true;
}

bool INSTRC(Program *p)
{

    printCur(p, __LINE__);

    if (strsame(p->wds[p->cw], "PRINT"))
    {

        if (PRINT(p))
        {

            return true;
        }
    }
    if (strsame(p->wds[p->cw], "SET"))
    {
        if (SET(p))
        {

            return true;
        }
    }

    if (strsame(p->wds[p->cw], "ONES") || strsame(p->wds[p->cw], "READ"))
    {
        if (CREATE(p))
        {

            return true;
        }
    }

    if (strsame(p->wds[p->cw], "LOOP"))
    {

        if (LOOP(p))
        {

            printCur(p, __LINE__);
            return true;
        }
    }

    ERROR("INSTRC : Expecting a PRINT or SET or CREATE or LOOP OR '}' OR ';' ?");
    return false;
}

bool PRINT(Program *p)
{
    p->cw = p->cw + 1;

    if (is_variable(p->wds[p->cw]))
    {

#ifdef INTERP
        var v = get_value(p);

        // printCur(p, __LINE__);
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

#ifdef INTERP
        printf("%s\n", word);
#endif

        return true;
    }

    ERROR("PRINT failure: Check the format ");
    return false;
}

bool SET(Program *p)
{

    p->cw = p->cw + 1;
    if (!VARNAME(p))
    {
        return false;
    }
    printCur(p, __LINE__);
    int pos = get_pos(p);

    p->pos = pos;

    p->cw = p->cw + 1;
    if (!p->wds[p->cw][0] || p->wds[p->cw][0] != ':')
    {
        ERROR("Expected symbol : \n");
    }

    if (!p->wds[p->cw][1] || p->wds[p->cw][1] != '=')
    {
        ERROR("Expected symbol = \n");
    }

    p->cw = p->cw + 1;
    if (!POLISHLIST(p))
    {
        printf("NOT POLISH LIST, RETURN FALSE\n");
        return false;
    }
    else
    {
        //  printf("POLISHLIST IS GOOD\n");
    }

    return true;
}
bool CREATE(Program *p)
{

    p->cw = p->cw + 1;
    if (ROWS(p))
    {
        p->cw = p->cw + 1;
        if (COLS(p))
        {

            p->cw = p->cw + 1;
            if (VARNAME(p))
            {

                int y = atoi(p->wds[p->cw - 2]);

                int x = atoi(p->wds[p->cw - 1]);

                // #ifdef INTERP
                int pos = get_pos(p);

                p->pos = pos;

                p->variables[pos].y = y;
                p->variables[pos].x = x;
                p->variables[pos].num = (int **)n2dcalloc(p->variables[pos].y, p->variables[pos].x, sizeof(int *));
                for (int y = 0; y < p->variables[pos].y; y++)
                {
                    for (int x = 0; x < p->variables[pos].x; x++)
                    {
                        p->variables[pos].num[y][x] = 1;
                    }
                }
                // free(p->variables[pos]);
                // #endif

                return true;
            }
        }
    }

    if (FILENAME(p))
    {
        p->cw = p->cw + 1;
        if (VARNAME(p))
        {

#ifdef INTERP
            int pos = get_pos(p);

            p->pos = pos;
            char *filename = p->wds[p->cw - 1];
            filename++;                         // remove first double quote
            filename[strlen(filename) - 1] = 0; // remove last double quote

            FILE *file_pointer = h_open(filename);
            int array[6][6];
            int height, width;
            if (fscanf(file_pointer, "%d%d", &height, &width) != 2)
                exit(1);
            p->variables[pos].y = height;
            p->variables[pos].x = width;
            p->variables[pos].num = (int **)n2dcalloc(p->variables[pos].y, p->variables[pos].x, sizeof(int *));

            for (int jj = 0; jj < height; jj++)
            {

                for (int ii = 0; ii < width; ii++)
                {
                    if (fscanf(file_pointer, "%d", &array[jj][ii]) != 1)
                    {

                        exit(1);
                    }
                }
            }

            for (int jj = 0; jj < height; jj++)
            {
                for (int ii = 0; ii < width; ii++)
                {
                    p->variables[pos].num[jj][ii] = array[jj][ii];
                    //
                }
                printf("\n");
            }
            printf("close file pointer\n");
            // free(p->variables);
            fclose(file_pointer);
#endif

            return true;
        }
    }

    ERROR("INVALID CREATE");
}
bool LOOP(Program *p)
{
    //SET UP
    var *v = calloc(1, sizeof(var));
    v->y = 1;
    v->x = 1;

    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));
    v->start = p->cw;

    p->cw = p->cw + 1;
    if (!VARNAME(p))
    {
        printf("VAR NOT OK\n");
        ERROR("INVALID VARNAME");
    }
    //INTERP
    v->pos = get_pos(p);
    p->pos = v->pos;
    p->variables[p->pos].y = 1;
    p->variables[p->pos].x = 1;

    //===========================================SET I INITIAL VALUE

    if (!p->variables[p->pos].num)
    {

        p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    }

    if (p->variables[p->pos].max_loop == 0 || p->variables[p->pos].num[0][0] < p->variables[p->pos].max_loop)
    {
        p->variables[p->pos].num[0][0] += 1;
        v->num[0][0] = p->variables[p->pos].num[0][0];
    }
    else if (p->variables[p->pos].num[0][0] == p->variables[p->pos].max_loop)
    {

        v->num[0][0] = (p->variables[p->pos].num[0][0] % p->variables[p->pos].max_loop) + 1;
        p->variables[p->pos].num[0][0] = v->num[0][0];
    }

    //===========================================SET I INITIAL VALUE

    p->cw = p->cw + 1;
    if (!INTEGER(p))
    {
        printf("INTEGER NOT OK\n");
        ERROR("INVALID INTEGER");
    }
    v->max_loop = atoi(p->wds[p->cw]);
    p->variables[p->pos].max_loop = v->max_loop;

    push(&p->stacknode, v);

    p->cw = p->cw + 1;
    if (!LEFTBRACKET(p))
    {
        printf("LEFT BRACKET NOT OK\n");
        ERROR("INVALID INTEGER");
    }
    p->cw = p->cw + 1;

    INSTRCLIST(p);

    free_stack_node(v);
    return true;
}

bool LEFTBRACKET(Program *p)
{
    // p->cw = p->cw + 1;
    if (strsame(p->wds[p->cw], "{"))
    {
        return true;
    }

    return false;
}

bool INTEGER(Program *p)
{
    // p->cw = p->cw + 1;

    if (digits_only(p->wds[p->cw]))
    {

        return true;
    }
    return false;
}

//==========================
//====== POLISHLIST =============
//==========================
bool POLISHLIST(Program *p)
{

    if (p->wds[p->cw][0] == ';')
    {

#ifdef INTERP
        var *v = pop(&p->stacknode);

        if (v)
        {

            set_value(p, v);
        }

        free_stack_node(v);
#endif
        return true;
    }
    //

    if (p->wds[p->cw] && !p->wds[p->cw][0])
    {
        printf("emp null\n");
        ERROR("EMPTY STRING, RETURN FALSE");
    }

    if (!POLISH(p))
    {
        printf("REAL POLISH ERROR\n");
        ERROR("POLISH ERROR:\n");
        return false;
    }

    p->cw = p->cw + 1;
    POLISHLIST(p);
    if (p->wds[p->cw][0] != ';')
    {

        return false;
    }

    return true;
}

bool POLISH(Program *p)
{

    printCur(p, __LINE__);
    if (PUSHDOWN(p) == true)
    {

        printCur(p, __LINE__);

        return true;
    }
    else if (UNARYOP(p))
    {

        return true;
    }
    else if (BINARYOP(p))
    {

        return true;
    }
    else
    {

        ERROR("POLISH ERROR:EXPECT PUSHDOWN | UNARYOP | BINARYOP ");
    }
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

bool PUSHDOWN(Program *p)
{

    printCur(p, __LINE__);
    if (digits_only(p->wds[p->cw]))
    {
#ifdef INTERP

        var *v = calloc(1, sizeof(var));
        v->y = 1;
        v->x = 1;
        v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));

        for (int y = 0; y < v->y; y++)
        {
            for (int x = 0; x < v->x; x++)
            {
                v->num[y][x] = atoi(p->wds[p->cw]);
            }
        }

        push(&p->stacknode, v);
#endif

        return true;
    }

    if (is_variable(p->wds[p->cw]))
    {
#ifdef INTERP
        printCur(p, __LINE__);
        var val = get_value(p);

        var *v = calloc(1, sizeof(var));
        v->y = val.y;
        v->x = val.x;
        v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));

        for (int y = 0; y < v->y; y++)
        {
            for (int x = 0; x < v->x; x++)
            {
                v->num[y][x] = val.num[y][x];
            }
        }
        push(&p->stacknode, v);
#endif
        return true;
    }

    return false;
}
bool UNARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "U-NOT"))
    {
#ifdef INTERP
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->y; x++)
            {
                v3->num[y][x] = ~v1->num[y][x];
            }
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
#ifdef INTERP
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);
        var *tmp = calloc(1, sizeof(var));

        v3->y = v1->y;
        v3->x = v1->x;
        tmp->y = v1->y;
        tmp->x = v1->x;

        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        tmp->num = (int **)n2dcalloc(v3->y + 2, v3->x + 2, sizeof(int *));
        for (int y = 0; y < tmp->y; y++)
        {
            for (int x = 0; x < tmp->x; x++)
            {
                tmp->num[y + 1][x + 1] = v1->num[y][x];
            }
        }

        int offset[8][2] = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}};

        for (int y = 1; y < tmp->y + 1; y++)
        {
            for (int x = 1; x < tmp->x + 1; x++)
            {
                int count = 0;
                for (int k = 0; k < 8; k++)
                {
                    //
                    if (tmp->num[y + offset[k][1]][x + offset[k][0]] >= 1)
                    {
                        count += 1;
                        v3->num[y - 1][x - 1] = count;
                    }
                }
            }
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);

        for (int y = 0; y < tmp->y + 2; y++)
        {
            free(tmp->num[y]);
        }
        free(tmp->num);
        free(tmp);
#endif
        return true;
    }

    return false;
}

bool BINARYOP(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);
    var *v2 = pop(&p->stacknode);
    var *v3 = calloc(1, sizeof(var));
#endif
    if (strsame(p->wds[p->cw], "B-ADD"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] + v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] + v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {
                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] + v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }

        // #endif
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-AND"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] & v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] & v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] & v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-OR"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] | v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] | v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] | v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-GREATER"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] < v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] < v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] < v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-LESS"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] > v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] > v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] > v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-TIMES"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] * v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] * v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] * v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-EQUALS"))
    {
#ifdef INTERP
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {

            v3->y = 1;
            v3->x = 1;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v1->num[y][x] == v2->num[y][x];
                }
            }

            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {

            v3->y = v2->y;
            v3->x = v2->x;
            v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = 0; x < v3->y; x++)
                {
                    v3->num[y][x] = v2->num[y][x] == v1->num[0][0];
                }
            }

            push(&p->stacknode, v3);
        }
        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {

                v3->y = v2->y;
                v3->x = v2->x;
                v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
                for (int y = 0; y < v3->y; y++)
                {
                    for (int x = 0; x < v3->y; x++)
                    {
                        v3->num[y][x] = v2->num[y][x] == v1->num[y][x];
                    }
                }

                push(&p->stacknode, v3);
            }
            else
            {
                ERROR("HEIGHT & WIDTH DOESN't MATCH");
            }
        }
        free_stack_node(v1);
        free_stack_node(v2);
#endif
        return true;
    }

    return false;
}

void printCur(Program *p, int line)
{
    // printf("PRINT CUR\n");
}

bool ROWS(Program *p)
{

    // p->cw = p->cw + 1;

    if (digits_only(p->wds[p->cw]))
    {
        //ERROR("NOT DIGIT ONLY\n");
        return true;
    }
    // ERROR("Eexpect ROWS");
    return false;
}

bool COLS(Program *p)
{

    // p->cw = p->cw + 1;

    if (digits_only(p->wds[p->cw]))
    {
        // ERROR("NOT DIGIT ONLY\n");
        return true;
    }
    ERROR("Eexpect COLS\n");
    return false;
}

bool VARNAME(Program *p)
{
    //

    if (is_variable(p->wds[p->cw]))
    {
        return true;
    }
    ERROR("Expect $<A-Z> \n");

    return false;
}

void read_file(FILE *file_pointer, Program *p)
{
    char buffer[FILESIZE];
    int count = 0;

    while (fscanf(file_pointer, "%s", buffer) != EOF)
    {
        strcpy(p->wds[count++], buffer);
    }
    // free(file_pointer);
}

bool testmode(char *PHRASE)
{

    return false;
}
void allocate_space(Program *p)
{

    p->variables[p->pos].y = 1;
    p->variables[p->pos].x = 1;
    p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
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

var get_value(Program *p)
{

    int pos = get_pos(p);

    if (!p->variables[pos].num)
    {
        printf("UNDEFINED VARIABLED DETECTED\n");
        
    }

    return p->variables[pos];

    // return NULL;
}

int get_pos(Program *p)
{
    return p->wds[p->cw][1] - 'A';
}

bool print_variable(var v)
{

    if (v.num != 0)
    {
        for (int y = 0; y < v.y; y++)
        {
            for (int x = 0; x < v.x; x++)
            {
                printf("%d", v.num[y][x]);
            }
            printf("\n");
        }
        // printf("@-----------\n");
        return true;
    }
    else
    {
        printf("NOT PRINTING ANYTHING !!! \n");
        ERROR("Undefined Variable ");
    };
    return false;
}

struct StackNode *newNode(var *data)
{
    struct StackNode *stackNode =
        (struct StackNode *)
            malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

bool isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, var *data)
{

    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

var *pop(struct StackNode **root)
{

    if (isEmpty(*root))
    {
        // printf("EMPTY!!!!!!!!!!\n");
        return NULL;
    }

    struct StackNode *temp = *root;
    *root = (*root)->next;
    var *popped = temp->data;

    free(temp);

    return popped;
}

void free_stack_node(var *v)
{
    for (int y = 0; y < v->y; y++)
    {
        free(v->num[y]);
    }
    free(v->num); 
    free(v);
}
