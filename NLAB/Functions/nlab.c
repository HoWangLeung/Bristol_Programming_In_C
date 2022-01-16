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
    printf("PROG RETURNS TRUE\n");
    return true;
}

bool INSTRCLIST(Program *p)
{
    printf("======== parsing INSTRCLIST ========\n");
    // printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {
        printf("->RETURN TRUE FROM INSTRCLIST }}} \n");
        return true;
    }
    if (!INSTRC(p))
    {
        printf("INSTRCLIST(): INSTRC error  \n");

        ERROR("INSTRCLIST return false ....\n");

        return false;
    }

    p->cw = p->cw + 1;
    if (!INSTRCLIST(p))
    {
        return false;
    }
    // printf("INSTRCLIST returns true\n");
    // #ifdef TESTMODE
    //     printf("IN TEST...\n");
    // #endif

    return true;
}

bool INSTRC(Program *p)
{
    printf("======== parsing INSTRC ========\n");
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
            printf("SET OK\n");

            return true;
        }
    }

    if (strsame(p->wds[p->cw], "ONES") || strsame(p->wds[p->cw], "READ"))
    {
        if (CREATE(p))
        {

            printf("CREATE() returns true\n");
            return true;
        }
    }

    // if (strsame(p->wds[p->cw], "LOOP"))
    // {

    //     if (LOOP(p))
    //     {
    //         return true;
    //     }
    // }

    ERROR("INSTRC : Expecting a PRINT or SET or CREATE or LOOP OR '}' OR ';' ?");
    return false;
}

bool PRINT(Program *p)
{
    p->cw = p->cw + 1;
    printf("======== parsing PRINT ========\n");
    if (is_variable(p->wds[p->cw]))
    {

#ifdef INTERP
        var v = get_value(p);
        printf("PRINTING VARIABLE\n");
        printCur(p, __LINE__);
        if (!print_variable(v))
        {
            ERROR("undefined varialbe ?\n");
            return false;
        }
#endif
        printf("is variable  return true\n");
        return true;
    }
    printf("check if string\n");
    if (is_string(p->wds[p->cw]))
    {
        printf("is string\n");
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
    printf("======== parsing SET ========\n");

    p->cw = p->cw + 1;
    if (!VARNAME(p))
    {
        return false;
    }
    printCur(p, __LINE__);
    int pos = get_pos(p);
    printf("NOW POS = %d\n", pos);
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
    printf("VARNAME AND COLON-EQUAL ok\n");
    p->cw = p->cw + 1;
    if (!POLISHLIST(p))
    {
        printf("NOT POLISH LIST, RETURN FALSE\n");
        return false;
    }
    else
    {
        printf("POLISHLIST IS GOOD\n");
    }

    return true;
}
bool CREATE(Program *p)
{
    printf("======== parsing CREATE ========\n");

    p->cw = p->cw + 1;
    if (ROWS(p))
    {
        p->cw = p->cw + 1;
        if (COLS(p))
        {
            printf("COLS OK\n");
            p->cw = p->cw + 1;
            if (VARNAME(p))
            {
                printf("create valname true ....\n");

                int y = atoi(p->wds[p->cw - 2]);
                printf("y = %d\n", y);
                int x = atoi(p->wds[p->cw - 1]);
                printf("x = %d\n", x);
                // #ifdef INTERP
                int pos = get_pos(p);
                printf("create pos = %d\n", pos);

                p->pos = pos;
                printf("create pos y = %d\n", p->variables[pos].y);
                printf("create pos x = %d\n", p->variables[pos].x);
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

    printf("COUNTINUE TO CHECK FILENAME & VARNAME\n");
    if (FILENAME(p))
    {
        p->cw = p->cw + 1;
        if (VARNAME(p))
        {
            printf("VALID READ FILE\n");

#ifdef INTERP
            int pos = get_pos(p);
            printf("filename create pos = %d\n", pos);
            p->pos = pos;
            char *filename = p->wds[p->cw - 1];
            filename++;                         // remove first double quote
            filename[strlen(filename) - 1] = 0; // remove last double quote
            printf("filename = %s\n", filename);
            FILE *file_pointer = h_open(filename);
            // p->variables[pos] = ncalloc(1, sizeof(var));

            // char buffer[FILESIZE];
            int array[6][6];
            int height, width;
            if (fscanf(file_pointer, "%d%d", &height, &width) != 2)
                exit(1);
            p->variables[pos].y = height;
            p->variables[pos].x = width;
            p->variables[pos].num = (int **)n2dcalloc(p->variables[pos].y, p->variables[pos].x, sizeof(int *));

            for (int jj = 0; jj < 5; jj++)
                for (int ii = 0; ii < 5; ii++)
                    if (fscanf(file_pointer, "%d", &array[jj][ii]) != 1)
                        exit(1);

            // printf("Test print\n");

            for (int jj = 0; jj < 5; jj++)
            {
                for (int ii = 0; ii < 5; ii++)
                {
                    p->variables[pos].num[jj][ii] = array[jj][ii];
                    //printf("%d", p->variables[pos]->num[jj][ii]);
                }
                printf("\n");
            }

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
    // p->start = p->cw;

    // while (p->count < 3)
    // {
    //     printf("loop something , cw = %d\n", p->cw);
    //     p->cw = p->cw + 1;
    //     if (!VARNAME(p))
    //     {
    //         printf("VAR NOT OK\n");
    //         ERROR("INVALID VARNAME");
    //     }

    //     //INTERP
    //     p->pos = get_pos(p);
    //     p->variables[p->pos].y = 1;
    //     p->variables[p->pos].x = 1;
    //     p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    //     p->variables[p->pos].num[0][0] = 1;

    //     p->cw = p->cw + 1;
    //     if (!INTEGER(p))
    //     {
    //         printf("INTEGER NOT OK\n");
    //         ERROR("INVALID INTEGER");
    //     }
    //     int max_loop = atoi(p->wds[p->cw]);
    //     printf("MAX LOOP = %d\n", max_loop);

    //     p->cw = p->cw + 1;
    //     if (!LEFTBRACKET(p))
    //     {
    //         printf("LEFT BRACKET NOT OK\n");
    //         ERROR("INVALID INTEGER");
    //     }
    //     p->cw = p->cw + 1;
    //     printCur(p, __LINE__);
    //     printf("****p->count =%d\n", p->count);

    //     INSTRCLIST(p);
    //     printf("......END OF INSTRCLIST\n");
    //     p->cw = p->start;

    //     p->count += 1;
    //     printf("p->count = %d\n", p->count);
    // }

    // p->cw = p->cw + 1;
    // if (!VARNAME(p))
    // {
    //     printf("VAR NOT OK\n");
    //     ERROR("INVALID VARNAME");
    // }

    // //INTERP
    // p->pos = get_pos(p);
    // p->variables[p->pos].y = 1;
    // p->variables[p->pos].x = 1;
    // p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    // p->variables[p->pos].num[0][0] = 1;

    // p->cw = p->cw + 1;
    // if (!INTEGER(p))
    // {
    //     printf("INTEGER NOT OK\n");
    //     ERROR("INVALID INTEGER");
    // }
    // int max_loop = atoi(p->wds[p->cw]);
    // printf("MAX LOOP = %d\n", max_loop);

    // p->cw = p->cw + 1;
    // if (!LEFTBRACKET(p))
    // {
    //     printf("LEFT BRACKET NOT OK\n");
    //     ERROR("INVALID INTEGER");
    // }
    // p->cw = p->cw + 1;
    // printCur(p, __LINE__);
    // printf("****p->count =%d\n", p->count);

    // INSTRCLIST(p);
    // printf("......END OF INSTRCLIST\n");

    // printf("p->count = %d\n", p->count);

    // printf("LOOP returns true\n");
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
    printf("======== LEVEL3:POLISHLIST ========\n");

    if (p->wds[p->cw][0] == ';')
    {
        // #ifdef INTERP
        printf(">>>>>>>> A THE END, FOUND HI ;\n");
        // printf("set pos = %d\n", p->pos);
        var *v = pop(&p->stacknode);
        printf("popped success\n");

        if (v)
        {
            printf("The value inside v = %d\n", v->num[0][0]);
            set_value(p, v);
        }

        free_stack_node(v);
        return true;
    }
    // printf("p->wds[p->cw][0] = %d\n", p->wds[p->cw]);

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
        printf("AT THE END NO ;, false\n");
        return false;
    }

    printf("POLISHLIST return true at the end\n");
    return true;
}

bool POLISH(Program *p)
{
    printf("======== LEVEL3:POLISH ========\n");
    printCur(p, __LINE__);
    if (PUSHDOWN(p) == true)
    {
        printf(" => IS PUSHDOWN\n");
        printCur(p, __LINE__);

        return true;
    }
    else if (UNARYOP(p))
    {
        printf(" => IS UNARYOP\n");
        return true;
    }
    else if (BINARYOP(p))
    {
        printf(" => IS BINARYOP\n");
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
    printf("PUSHDOWN()\n");
    printCur(p, __LINE__);
    if (digits_only(p->wds[p->cw]))
    {
        // #ifdef INTERP
        printf("<<<<<<<<<<< digitsonly >>>>>>>>>>>>\n");
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
        printf("v-val= %d\n", v->num[0][0]);
        push(&p->stacknode, v);

        return true;
    }

    if (is_variable(p->wds[p->cw]))
    {

        printf("<<<<<<<<<<< is_variable >>>>>>>>>>>>\n");
        printCur(p, __LINE__);
        var val = get_value(p);
        printf("HELLO : %d , %d\n", val.y, val.x);
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
        return true;
    }
    printf("PUSHDOWN RETURNS FALSE\n");
    return false;
}
bool UNARYOP(Program *p)
{
    printf("CHECKING UNARYOP\n");

    
    if (strsame(p->wds[p->cw], "U-NOT"))
    {
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);
        printf("IN U-NOT");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);
        var *tmp = calloc(1, sizeof(var));
        printf("IN U-EIGHTCOUNT\n");
        v3->y = v1->y;
        v3->x = v1->x;
        tmp->y = v1->y;
        tmp->x = v1->x;

        printf("v3: y=%d, x=%d\n", v3->y, v3->x);

        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        tmp->num = (int **)n2dcalloc(v3->y + 2, v3->x + 2, sizeof(int *));
        for (int y = 0; y < tmp->y; y++)
        {
            for (int x = 0; x < tmp->x; x++)
            {
                tmp->num[y + 1][x + 1] = v1->num[y][x];
            }
        }

        for (int y = 0; y < tmp->y + 2; y++)
        {
            for (int x = 0; x < tmp->x + 2; x++)
            {
                printf("%d", tmp->num[y][x]);
            }
            printf("\n");
        }
        printf("next:\n");
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
                    //printf("HELLO %d\n",tmp->num[y + offset[k][1]][x + offset[k][0]]);
                    if (tmp->num[y + offset[k][1]][x + offset[k][0]] >= 1)
                    {
                        count += 1;
                        v3->num[y - 1][x - 1] = count;
                    }
                }
            }
        }

        printf("after222:\n");
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {

                printf("%d", v3->num[y][x]);
            }
            printf("\n");
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);

        for (int y = 0; y < tmp->y + 2; y++)
        {
            free(tmp->num[y]);
        }
        free(tmp->num);
        free(tmp);

        printf("finished\n");
        return true;
    }
    printf(" UNARYOP returns false\n");
    return false;
}

bool BINARYOP(Program *p)
{
    printf("BINARYOP CHECK\n");
    var *v1 = pop(&p->stacknode);
    var *v2 = pop(&p->stacknode);
    var *v3 = calloc(1, sizeof(var));
    if (strsame(p->wds[p->cw], "B-ADD"))
    {
        printf("IN B-ADD\n");
        printf("v1: y=%d, x=%d\n", v1->y, v1->x);
        printf("v2: y=%d, x=%d\n", v2->y, v2->x);
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
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

        return true;
    }

    if (strsame(p->wds[p->cw], "B-AND"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "B-OR"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "B-GREATER"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "B-LESS"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "B-TIMES"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    if (strsame(p->wds[p->cw], "B-EQUALS"))
    {
        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND_1\n");
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
            printf("v-val= %d\n", v3->num[0][0]);
            push(&p->stacknode, v3);
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND_2\n");
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
                printf("COND_3\n");
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
        return true;
    }

    return false;
}

void printCur(Program *p, int line)
{
    printf("printCur() is %s ,line %d\n", p->wds[p->cw], line);
}

bool ROWS(Program *p)
{
    printf("handling ROWS\n");

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
    printf("handling ROWS");

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
    // printf("check if VARNAME\n");

    if (is_variable(p->wds[p->cw]))
    {
        return true;
    }
    ERROR("Expect $<A-Z> \n");
    printf("HI\n");
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
    printf("test mode called , %s\n", PHRASE);
    return false;
}
void allocate_space(Program *p)
{
    printf("allocate_space()\n");

    p->variables[p->pos].y = 1;
    p->variables[p->pos].x = 1;
    p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
}

bool set_value(Program *p, var *v)
{
    printf("y:%d,x:%d\n", v->y, v->x);
    printf("py:%d,px:%d\n", p->variables[p->pos].y, p->variables[p->pos].x);
    p->variables[p->pos].y = v->y;
    p->variables[p->pos].x = v->x;
    if (!p->variables[p->pos].num)
    {
        p->variables[p->pos].num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
    }

    printf("OK?\n");
    for (int y = 0; y < v->y; y++)
    {
        for (int x = 0; x < v->x; x++)
        {

            p->variables[p->pos].num[y][x] = v->num[y][x];
        }
    }
    printf("VALUE SET\n");

    for (int y = 0; y < p->variables[p->pos].y; y++)
    {
        for (int x = 0; x < p->variables[p->pos].x; x++)
        {
            printf("%d", p->variables[p->pos].num[y][x]);
        }
        printf("\n");
    }

    return true;
}

var get_value(Program *p)
{

    int pos = get_pos(p);
    printf("pos =%d\n", pos);

    if (!p->variables[pos].num)
    {
        ERROR("UNDEFINED VARIABLED DETECTED\n");
    }

    printf("val inside get_value =%d\n", p->variables[pos].num[0][0]);

    return p->variables[pos];

    // return NULL;
}

int get_pos(Program *p)
{
    return p->wds[p->cw][1] - 'A';
}

bool print_variable(var v)
{
    printf("printing variable:\n");

    printf("y=%d , x=%d\n", v.y, v.x);
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
    printf("START TO PUSH-->\n");
    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    printf(" pushed to stack\n");
}

var *pop(struct StackNode **root)
{
    printf("->START POPPING\n");
    if (isEmpty(*root))
    {
        printf("EMPTY!!!!!!!!!!\n");
        return NULL;
    }

    struct StackNode *temp = *root;
    *root = (*root)->next;
    var *popped = temp->data;

    free(temp);

    printf("popped = %d\n", popped->num[0][0]);
    printf("popping y= %d\n", popped->y);
    printf("popping x= %d\n", popped->x);

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
