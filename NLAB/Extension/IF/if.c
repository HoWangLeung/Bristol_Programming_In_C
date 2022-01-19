#include "../../Functions/nlab.h"

bool IF(Program *p)
{

    increment_cw(p);
    if (COND(p))
    {
        return true;
    }

    return false;
}

bool COND(Program *p)
{
    // printf("========PARSING COND========\n");
    printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {
        return true;
    }

    if (PUSHDOWN(p))
    {
        // printf("->PUSHDOWN\n");
    }
    increment_cw(p);
    printCur(p, __LINE__);
    if (PUSHDOWN(p))
    {
        //printf("->PUSHDOWN 2 \n");
    }
    increment_cw(p);

    COMPARE(p);
    printCur(p, __LINE__);

    COND(p);

    return true;
}

bool COMPARE(Program *p)
{
    //printf("========PARSING COMPARE========\n");
    if (BINARYOP(p))
    {
        // printf("IN BINARYOP\n"); 
        increment_cw(p);
        printCur(p, __LINE__);
        if (strsame(p->wds[p->cw], "AND"))
        {
            // printf("FOUND AND \n"); 
            increment_cw(p);
            if (strsame(p->wds[p->cw], "{"))
            {
                //printf("HERE\n");
                var *v1 = pop(&p->stacknode);
                var *v2 = pop(&p->stacknode);

                if (v1->num[0][0] && v2->num[0][0])
                {
                    printf("EQUAL!!!!\n");
                    increment_cw(p);
                    // return true;
                    INSTRCLIST(p);
                }
                else
                {
                    printf("NOTEQUAL!!!!\n");
                    int right_bracket_pos = search_next_right_bracket(p);
                    p->cw = right_bracket_pos;
                }
                free_stack_node(v1);
                free_stack_node(v2);
            }
        }
        else if (strsame(p->wds[p->cw], "OR"))
        {
            printf("FOUND AND \n");
            increment_cw(p);
            if (strsame(p->wds[p->cw], "{"))
            {
                printf("HERE\n");
                var *v1 = pop(&p->stacknode);
                var *v2 = pop(&p->stacknode);

                if (v1->num[0][0] || v2->num[0][0])
                {
                    printf("EQUAL!!!!\n");
                    increment_cw(p);
                    // return true;
                    INSTRCLIST(p);
                }
                else
                {
                    printf("NOTEQUAL!!!!\n");
                    int right_bracket_pos = search_next_right_bracket(p);
                    p->cw = right_bracket_pos;
                }
                free_stack_node(v1);
                free_stack_node(v2);
            }
        }
        else
        {
            if (strsame(p->wds[p->cw], "{"))
            {
                printf("ELSEEEEE\n");
                var *v1 = pop(&p->stacknode);

                if (v1->num[0][0])
                {
                    printf("EQUAL!!!!\n");
                    increment_cw(p);
                    // return true;
                    INSTRCLIST(p);
                }
                else
                {
                    printf("NOTEQUAL!!!!\n");
                    int right_bracket_pos = search_next_right_bracket(p);
                    p->cw = right_bracket_pos;
                }
                free_stack_node(v1);
            }
        }
    }
    return true;
}

int search_next_right_bracket(Program *p)
{

    int tmp = p->cw;
    int required = 1;
    int found = 0;
    while (!strsame(p->wds[tmp], "}") || found != required)
    {
        tmp++;
        if (strsame(p->wds[tmp], "IF"))
        {
            printf("FOUND IF\n");
            required += 1;
        }

        if (strsame(p->wds[tmp], "}"))
        {
            found += 1;
        }
        printf("found = %d\n", found);
        printf("required = %d\n", required);
    }

    printf("right } pos = %d\n", tmp);

    return tmp;
}

