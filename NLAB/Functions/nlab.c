#include "nlab.h"
#define FILESIZE 100
// #define INTERP
#define CALCULATE_SAME_SIZE(v3, v1, v2, op) \
    for (int y = 0; y < v3->y; y++)         \
        for (int x = 0; x < v3->x; x++)     \
    v3->num[y][x] = v1->num[y][x] op v2->num[y][x]
bool PROG(Program *p)
{
    int *cw = &p->cw;
    if (!strsame(p->wds[*cw], "BEGIN"))
    {
        ERROR("No BEGIN statement ?");
    }
    increment_cw(p);
    if (!strsame(p->wds[*cw], "{"))
    {
        ERROR("Expected {");
    }
    increment_cw(p);
    if (!INSTRCLIST(p))
    {
        printf("SOMETHING WORONG IN INSTRCLIST\n");
        return false;
    }
    return true;
}

bool INSTRCLIST(Program *p)
{
    printf("=====INSTRCLIST======\n");
    printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {
        interp_instrclist(p);
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
    increment_cw(p);
    if (!INSTRCLIST(p))
    {
        return false;
    }
    printf("=====END OF INSTRCLIST======\n");
    return true;
}

bool INSTRC(Program *p)
{
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
            return true;
        }
    }

    if (strsame(p->wds[p->cw], "IF"))
    {
        if (IF(p))
        {
            return true;
        }
    }
    ERROR("INSTRC : Expecting a PRINT or SET or CREATE or LOOP OR '}' OR ';' ?");
    return false;
}

bool PRINT(Program *p)
{
    increment_cw(p);

    if (is_variable(p->wds[p->cw]))
    {

#ifdef INTERP
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
    increment_cw(p);
    if (!VARNAME(p))
    {
        return false;
    }
    int pos = get_pos(p);
    p->pos = pos;
    increment_cw(p);
    if (!p->wds[p->cw][0] || p->wds[p->cw][0] != ':')
    {
        ERROR("Expected symbol : \n");
    }

    if (!p->wds[p->cw][1] || p->wds[p->cw][1] != '=')
    {
        ERROR("Expected symbol = \n");
    }
    increment_cw(p);
    if (!POLISHLIST(p))
    {
        printf("NOT POLISH LIST, RETURN FALSE\n");
        return false;
    }
    return true;
}
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

bool LEFTBRACKET(Program *p)
{
    if (strsame(p->wds[p->cw], "{"))
    {
        return true;
    }

    return false;
}

bool INTEGER(Program *p)
{
    if (digits_only(p->wds[p->cw]))
    {

        return true;
    }
    return false;
}

//===============================
//====== POLISHLIST =============
//===============================
bool POLISHLIST(Program *p)
{
    printf("=====PARSING POLISHLIST=======\n");
    if (p->wds[p->cw][0] == ';')
    {
        printf("YES IS ;;;\n");
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
    printf("AFTER PUSHDOWN\n");
    printCur(p, __LINE__);
    increment_cw(p);
    printCur(p, __LINE__);
    POLISHLIST(p);
    if (p->wds[p->cw][0] != ';')
    {

        return false;
    }

    return true;
}

bool POLISH(Program *p)
{
    printf("=========parsing polish========\n");
    printCur(p, __LINE__);
    printf("IN POLISH....\n");
    printCur(p, __LINE__);
    if (PUSHDOWN(p) == true)
    {
        printf("=>>IS PUSHDOWN\n");
        return true;
    }
    else if (UNARYOP(p))
    {
        printf("=>>IS UNARYOP\n");
        return true;
    }
    else if (BINARYOP(p))
    {
        printf("=>>IS BINARYOP\n");
        return true;
    }
    else if (SORTOP(p))
    {
        printf("=>>IS SORTOP\n");
        return true;
    }
    else if (FLIPOP(p))
    {
        printf("=>>IS FLIPOP\n");
        return true;
    }
    else if (ROTATEOP(p))
    {
        printf("=>>IS FLIPOP\n");
        return true;
    }
    else
    {
        printf("NOTING...\n");
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
    if (digits_only(p->wds[p->cw]))
    {
        interp_pushdown_digits(p);
        return true;
    }

    if (is_variable(p->wds[p->cw]))
    {
        interp_pushdown_variable(p);
        return true;
    }
    return false;
}
bool UNARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "U-NOT"))
    {
        printf("IN U-NOT\n");
        interp_u_not(p);
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
        printf("IN U-EIGHT\n");
        interp_u_eightcount(p);
        return true;
    }
    return false;
}

bool BINARYOP(Program *p)
{
    printf("IN BINARYOP\n");
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

void printCur(Program *p, int line)
{
    printf("printCur() is %s ,line %d\n", p->wds[p->cw], line);
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

bool VARNAME(Program *p)
{
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
}

bool testmode()
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
}

int get_pos(Program *p)
{
    return p->wds[p->cw][1] - 'A';
}

bool print_variable(var v)
{
    printf("=>printing variable:\n");
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

    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

var *pop(struct StackNode **root)
{

    if (isEmpty(*root))
    {
        printf("EMPTY!!!!!!!!!!\n");
        return NULL;
    }

    struct StackNode *temp = *root;
    *root = (*root)->next;
    var *popped = temp->data;

    free(temp);

    printf("popped  nums=%d\n", popped->num[0][0]);
    printf("popped y=%d\n", popped->y);
    printf("popped x=%d\n", popped->x);

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

void increment_cw(Program *p)
{
    p->cw += 1;
}

bool LOOP(Program *p)
{
//SET UP
#ifdef INTERP
    var *v = calloc(1, sizeof(var));
    v->y = 1;
    v->x = 1;
    v->num = (int **)n2dcalloc(v->y, v->x, sizeof(int *));
    v->start = p->cw;
#endif
    increment_cw(p);
    if (!VARNAME(p))
    {
        printf("VAR NOT OK\n");
        ERROR("INVALID VARNAME");
    }
#ifdef INTERP
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
#endif
    increment_cw(p);
    if (!INTEGER(p))
    {
        printf("INTEGER NOT OK\n");
        ERROR("INVALID INTEGER");
    }
#ifdef INTERP
    v->max_loop = atoi(p->wds[p->cw]);
    p->variables[p->pos].max_loop = v->max_loop;

    push(&p->stacknode, v);

    increment_cw(p);
    if (!LEFTBRACKET(p))
    {
        printf("LEFT BRACKET NOT OK\n");
        ERROR("INVALID INTEGER");
    }
#endif
    increment_cw(p);
    INSTRCLIST(p);
#ifdef INTERP
    free_stack_node(v);
#endif
    return true;
}

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
    printf("========PARSING COND========\n");
    printCur(p, __LINE__);
    if (strsame(p->wds[p->cw], "}"))
    {
        return true;
    }

    if (PUSHDOWN(p))
    {
        printf("->PUSHDOWN\n");
    }
    increment_cw(p);
    printCur(p, __LINE__);
    if (PUSHDOWN(p))
    {
        printf("->PUSHDOWN 2 \n");
    }
    increment_cw(p);

    COMPARE(p);
    printCur(p, __LINE__);

    COND(p);

    return true;
}

bool COMPARE(Program *p)
{
    printf("========PARSING COMPARE========\n");

    if (BINARYOP(p))
    {
        printf("IN BINARYOP\n");
        increment_cw(p);
        printCur(p, __LINE__);
        if (strsame(p->wds[p->cw], "AND"))
        {
            printf("FOUND AND \n");
            increment_cw(p);
            if (strsame(p->wds[p->cw], "{"))
            {
                printf("HERE\n");
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

bool SORTOP(Program *p)
{
    printf("IN SORTOP\n");
    if (strsame(p->wds[p->cw], "B-SORT"))
    {
        printf("......IN B-SORT\n");
        var *v3 = calloc(1, sizeof(var));

        var *v1 = pop(&p->stacknode);

        printf("v1 num = %d\n", v1->num[0][0]);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {
                v3->num[y][x] = v1->num[y][x];
            }
        }

        for (int k = 0; k < v3->y; k++)
        {
            for (int y = 0; y < v3->y; y++)
            {
                for (int x = y + 1; x < v3->x; x++)
                {
                    if (v3->num[k][y] > v3->num[k][x])
                    {
                        int swap = v3->num[k][y];
                        v3->num[k][y] = v3->num[k][x];
                        v3->num[k][x] = swap;
                    }
                }
            }
        }
        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    if (strsame(p->wds[p->cw], "Q-SORT"))
    {
        printf("......IN Q-SORT\n");
        var *v3 = calloc(1, sizeof(var));

        var *v1 = pop(&p->stacknode);

        printf("v1 num = %d\n", v1->num[0][0]);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {
                v3->num[y][x] = v1->num[y][x];
            }
        }

        for (int i = 0; i < v3->y; i++)
            qsort(v3->num, v3->y, sizeof(int *), flipcomp);

        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    return false;
}

bool FLIPOP(Program *p)
{
    printf("IN SORTOP\n");
    if (strsame(p->wds[p->cw], "FLIP"))
    {
        printf("......IN FLIP-SORT\n");
        var *v3 = calloc(1, sizeof(var));

        var *v1 = pop(&p->stacknode);

        printf("v1 num = %d\n", v1->num[0][0]);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {
                v3->num[y][x] = v1->num[y][x];
            }
        }

        for (int i = 0; i < v3->y; i++)
            qsort(v3->num, v3->y, sizeof(int *), flipcomp);

        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    return false;
}

int flipcomp(const void *firstArg, const void *secondArg)
{
    /* get the values of the arguments */
    int first = *(int *)firstArg;
    int second = *(int *)secondArg;

    /* return the value as expected by the qsort() method */
    if (first < second)
    {
        return 1;
    }
    else if (second < first)
    {
        return -1;
    }

    return 0;
}

bool ROTATEOP(Program *p)
{
    printf("IN SORTOP\n");
    if (strsame(p->wds[p->cw], "ROTATE-L"))
    {
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {
                v3->num[y][x] = v1->num[y][x];
            }
        }
        int N = v3->y;
        //ROTATION
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = x; y < N - x - 1; y++)
            {
                int temp = v3->num[x][y];
                v3->num[x][y] = v3->num[y][N - 1 - x];
                v3->num[y][N - 1 - x] = v3->num[N - 1 - x][N - 1 - y];
                v3->num[N - 1 - x][N - 1 - y] = v3->num[N - 1 - y][x];
                v3->num[N - 1 - y][x] = temp;
            }
        }
        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    if (strsame(p->wds[p->cw], "ROTATE-R"))
    {
        var *v3 = calloc(1, sizeof(var));
        var *v1 = pop(&p->stacknode);

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        for (int y = 0; y < v3->y; y++)
        {
            for (int x = 0; x < v3->x; x++)
            {
                v3->num[y][x] = v1->num[y][x];
            }
        }
        int N = v3->y;
        //ROTATION
        for (int i = 0; i < N / 2; i++)
        {
            for (int j = i; j < N - i - 1; j++)
            {
                int temp = v3->num[i][j];
                v3->num[i][j] = v3->num[N - 1 - j][i];
                v3->num[N - 1 - j][i] = v3->num[N - 1 - i][N - 1 - j];
                v3->num[N - 1 - i][N - 1 - j] = v3->num[j][N - 1 - i];
                v3->num[j][N - 1 - i] = temp;
            }
        }

        push(&p->stacknode, v3);
        free_stack_node(v1);

        return true;
    }

    return false;
}

void interp_instrclist(Program *p)
{
#ifdef INTERP
    var *popped = pop(&p->stacknode);
    if (popped)
    {
        int popped_val = popped->num[0][0];
        int pos = popped->pos;
        int max_loop = popped->max_loop;
        int start = popped->start;
        int latest_val = p->variables[pos].num[0][0];
        if (popped_val != latest_val)
        {
            popped_val = latest_val;
        }
        if (popped_val < max_loop)
        {
            p->cw = start;
            INSTRCLIST(p);
        }
    }
#endif
}

void interp_create(Program *p)
{
#ifdef INTERP
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
#endif
}

void interp_u_not(Program *p)
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
}

void interp_u_eightcount(Program *p)
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

    //each element represents the offset for one of the eight directions
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
}
void interp_b_add(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {
        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, +);
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

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

void interp_b_and(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, &);

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
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_or(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, |);

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
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_greater(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, <);

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
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_less(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = v1->y;
        v3->x = v1->x;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, >);

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

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}
void interp_b_times(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = 1;
        v3->x = 1;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
        CALCULATE_SAME_SIZE(v3, v1, v2, *);

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
    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

void interp_b_equals(Program *p)
{
#ifdef INTERP
    var *v1 = pop(&p->stacknode);     //first array popped
    var *v2 = pop(&p->stacknode);     //second array popped
    var *v3 = calloc(1, sizeof(var)); //result to be pushed
    if (v2->y == v1->y && v2->x == v1->x)
    {

        v3->y = 1;
        v3->x = 1;
        v3->num = (int **)n2dcalloc(v3->y, v3->x, sizeof(int *));
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

    free_stack_node(v1);
    free_stack_node(v2);
#endif
}

void interp_create_file(Program *p)
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
    fclose(file_pointer);
#endif
}

void interp_pushdown_digits(Program *p)
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
}

void interp_pushdown_variable(Program *p)
{
#ifdef INTERP
    //(p, __LINE__);
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
}
