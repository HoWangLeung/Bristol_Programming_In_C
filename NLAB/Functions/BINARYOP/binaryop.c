#include "../nlab.h"

#define CALCULATE_SAME_SIZE(v3, v1, v2, op) \
    for (int y = 0; y < v3->y; y++)         \
        for (int x = 0; x < v3->x; x++)     \
    v3->num[y][x] = v1->num[y][x] op v2->num[y][x]

#define CALCULATE_DIFF_SIZE(v3, v1, v2, op)                \
    for (int y = 0; y < v3->y; y++)                        \
    {                                                      \
        for (int x = 0; x < v3->x; x++)                    \
        {                                                  \
            v3->num[y][x] = v2->num[y][x] + v1->num[0][0]; \
        }                                                  \
    }

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
    at_least_two_varaibles(p);

        var *v1 = pop(&p->stacknode); //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {
        // v3->y = v1->y;
        // v3->x = v1->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, +);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_DIFF_SIZE(v3, v1, v2, +);
        push(&p->stacknode, v3);
    }

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

void interp_b_and(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {
        // v3->y = v1->y;
        // v3->x = v1->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, &);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] & v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, &);
        push(&p->stacknode, v3);
    }
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_or(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        // v3->y = v1->y;
        // v3->x = v1->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, |);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {

        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] | v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, |);

        push(&p->stacknode, v3);
    }
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_greater(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        // v3->y = v1->y;
        // v3->x = v1->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, <);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {

        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] < v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, <);
        push(&p->stacknode, v3);
    }
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_less(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        // v3->y = v1->y;
        // v3->x = v1->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        // CALCULATE_SAME_SIZE(v3, v1, v2, >);
        CALCULATE_SAME_SIZE(v3, v1, v2, >);
        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] > v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, >);
        push(&p->stacknode, v3);
    }

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_times(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        // v3->y = 1;
        // v3->x = 1;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        allocate_space(v3, v2->y, v2->x);
        CALCULATE_SAME_SIZE(v3, v1, v2, *);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] * v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, *);
        push(&p->stacknode, v3);
    }
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

void interp_b_equals(Program *p)
{
    (void)p;
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {
        allocate_space(v3, v2->y, v2->x);
        // v3->y = 1;
        // v3->x = 1;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v1->num[y][x] == v2->num[y][x];
        //     }
        // }
        CALCULATE_SAME_SIZE(v3, v1, v2, ==);

        push(&p->stacknode, v3);
    }

    if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
    {
        allocate_space(v3, v2->y, v2->x);
        // v3->y = v2->y;
        // v3->x = v2->x;
        // v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        // for (int y = 0; y < v3->y; y++)
        // {
        //     for (int x = 0; x < v3->y; x++)
        //     {
        //         v3->num[y][x] = v2->num[y][x] == v1->num[0][0];
        //     }
        // }
        CALCULATE_DIFF_SIZE(v3, v1, v2, ==);
        push(&p->stacknode, v3);
    }

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

bool at_least_two_varaibles(Program *p)
{

    if (!is_variable(p->wds[p->cw - 1]) && !digits_only(p->wds[p->cw - 1]))
    {

        ERROR("REAUIRE AT LEAST 2 VARIABLES/INTEGER\n");
    }
    else if (!is_variable(p->wds[p->cw - 2]) && !digits_only(p->wds[p->cw - 2]))
    {
        ERROR("REAUIRE AT LEAST 2 VARIABLES/INTEGER\n");
    }
    return true;
}
