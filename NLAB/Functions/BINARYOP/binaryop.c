#include "../nlab.h"

#define CALCULATE_SAME_SIZE(v3, v1, v2, op)                     \
    {                                                           \
        for (int y = 0; y < v3->y; y++)                         \
        {                                                       \
            for (int x = 0; x < v3->x; x++)                     \
            {                                                   \
                v3->num[y][x] = v1->num[y][x] op v2->num[y][x]; \
            }                                                   \
        }                                                       \
    }

#define CALCULATE_DIFF_SIZE(v3, v1, v2, op)                     \
    {                                                           \
        for (int y = 0; y < v3->y; y++)                         \
        {                                                       \
            for (int x = 0; x < v3->x; x++)                     \
            {                                                   \
                v3->num[y][x] = v2->num[y][x] op v1->num[0][0]; \
            }                                                   \
        }                                                       \
    }
void free_multiple_nodes(var *v1, var *v2);
bool check_atleast_two_varaibles(var *v1, var *v2);
void binary_calculation(Program *p, char *sign);
void calculation(var *v1, var *v2, var *v3, char *sign, bool same_size);
bool is_same_size(var *v1, var *v2);
bool BINARYOP(Program *p)
{
    if (strsame(p->wds[p->cw], "B-ADD"))
    {
#ifdef INTERP
        binary_calculation(p, "+");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-AND"))
    {
#ifdef INTERP
        binary_calculation(p, "&");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-OR"))
    {
#ifdef INTERP
        binary_calculation(p, "|");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-GREATER"))
    {
#ifdef INTERP
        binary_calculation(p, ">");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-LESS"))
    {
#ifdef INTERP
        binary_calculation(p, "<");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-TIMES"))
    {
#ifdef INTERP
        binary_calculation(p, "*");
#endif
        return true;
    }

    if (strsame(p->wds[p->cw], "B-EQUALS"))
    {
#ifdef INTERP
        binary_calculation(p, "==");
#endif
        return true;
    }
    return false;
}

void binary_calculation(Program *p, char *sign)
{
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (is_same_size(v1, v2))
    {
        allocate_space(v3, v2->y, v2->x);
        calculation(v1, v2, v3, sign, true);
        push(&p->stacknode, v3);
    }
    if (!is_same_size(v1, v2))
    {
        allocate_space(v3, v2->y, v2->x);
        calculation(v1, v2, v3, sign, false);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
}

void calculation(var *v1, var *v2, var *v3, char *sign, bool same_size)
{
    if (strsame(sign, "+"))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, +);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, +);
        }
    }

    if (strsame(sign, "&"))
    {

        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, &);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, &);
        }
    }

    if (strsame(sign, "|"))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, |);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, |);
        }
    }

    if (strsame(sign, ">"))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, >);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, >);
        }
    }

    if (strsame(sign, "<"))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, <);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, <);
        }
    }

    if (strsame(sign, "*"))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, *);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, *);
        }
    }

    if (strsame(sign, "=="))
    {
        if (same_size)
        {
            CALCULATE_SAME_SIZE(v3, v1, v2, ==);
        }
        else
        {
            CALCULATE_DIFF_SIZE(v3, v1, v2, ==);
        }
    }
}

bool check_atleast_two_varaibles(var *v1, var *v2)
{
    if (!v1 || !v2)
    {
        ERROR("REQUIRE 2 VARIABLES");
    }
    return true;
}

void free_multiple_nodes(var *v1, var *v2)
{
    free_stack_node(v1);
    free_stack_node(v2);
}

bool is_same_size(var *v1, var *v2)
{
    if (v2->y == v1->y && v2->x == v1->x)
    {
        return true;
    }
    else if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        return false;
    }
    else
    {
        ERROR("Unexpected error");
    }
    return false;
}

