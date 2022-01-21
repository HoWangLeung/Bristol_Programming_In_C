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
void same_size_calculation(Program *p, var *v1, var *v2, var *v3, char sign);
// void diff_size_operation(Program *p, var *v1, var *v2, var *v3);
bool check_atleast_two_varaibles(var *v1, var *v2);

bool BINARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "B-ADD"))
    {
        interp_b_add(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-AND"))
    {
        interp_b_and(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-OR"))
    {
        interp_b_or(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-GREATER"))
    {
        interp_b_greater(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-LESS"))
    {
        interp_b_less(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-TIMES"))
    {
        interp_b_times(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "B-EQUALS"))
    {
        interp_b_equals(p);
        return true;
    }

    return false;
}

void interp_b_add(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);

    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, +);
        push(&p->stacknode, v3);
    }
    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, +);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
}

void interp_b_and(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, &);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, &);
        push(&p->stacknode, v3);
    }

    free_multiple_nodes(v1, v2);
#endif
}
void interp_b_or(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, |);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, |);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
}
void interp_b_greater(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, <);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, >);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
}
void interp_b_less(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, >);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, <);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
}
void interp_b_times(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, *);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, *);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
}

void interp_b_equals(Program *p)
{
    (void)p;
#ifdef INTERP

    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    check_atleast_two_varaibles(v1, v2);
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, ==);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, ==);
        push(&p->stacknode, v3);
    }
    free_multiple_nodes(v1, v2);
#endif
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

void same_size_calculation(Program *p, var *v1, var *v2, var *v3, char sign)
{
    if (v2->y == v1->y && v2->x == v1->x)
    {
        printf("sign = %c\n", sign);
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, +);
        push(&p->stacknode, v3);
    }
}
// void diff_size_operation(Program *p, var *v1, var *v2, var *v3)
// {
//     if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
//     {
//         allocate_space(v3, v2->y, v2->x);
//         CALCULATE_DIFF_SIZE(v3, v1, v2, +);
//         push(&p->stacknode, v3);
//     }
// }
