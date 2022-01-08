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

    if (strsame(p->wds[p->cw], "}"))
    {
        printf("RETURN TRUE FROM INSTRCLIST }}} \n");
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

    if (strsame(p->wds[p->cw], "LOOP"))
    {
        if (LOOP(p))
        {
            return true;
        }
    }

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
    if (p)
        printf("loop something \n");

    p->cw = p->cw + 1;

    if (!VARNAME(p))
    {
        printf("VAR NOT OK\n");
        ERROR("INVALID VARNAME");
    }

#ifdef INTERP

    // int count = 1;
    allocate_space(p);
    p->variables[p->pos].y = 1;
    p->variables[p->pos].x = 1;
    printf("p->count =%d\n", p->variables[p->pos].count);
    p->variables[p->pos].count += 1;
    int count = p->variables[p->pos].count;
    for (int y = 0; y < p->variables[p->pos].y; y++)
    {
        for (int x = 0; x < p->variables[p->pos].x; x++)
        {
            p->variables[p->pos].num[y][x] = count;
        }
    }
    printf("TEST VALUE !!! :\n");
    for (int y = 0; y < p->variables[p->pos].y; y++)
    {
        for (int x = 0; x < p->variables[p->pos].x; x++)
        {
            printf("%d", p->variables[p->pos].num[y][x]);
        }
        printf("\n");
    }
#endif

    p->cw = p->cw + 1;
    if (!INTEGER(p))
    {
        printf("INTEGER NOT OK\n");
        ERROR("INVALID INTEGER");
    }
    int max_loop = atoi(p->wds[p->cw]);
    printf("MAX LOOP = %d\n", max_loop);

    p->cw = p->cw + 1;
    if (!LEFTBRACKET(p))
    {
        printf("LEFT BRACKET NOT OK\n");
        ERROR("INVALID INTEGER");
    }
    p->cw = p->cw + 1;

    for (int i = 0; i < max_loop; i++)
    {
        INSTRCLIST(p);
    }

    printf("LOOP returns true\n");
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
        printf("YES ;\n");
        printf("set pos = %d\n", p->pos);
        var *v = pop(p);
        printf("popped success\n");

        if (v)
        {
            printf("is there value = %d\n", v->num[0][0]);
            set_value(p, v);
        }
        // printf("value inside = %d\n", p->variables[0].num[0][0]);
        clear_stack(p);

        // for (int i = 0; i < 1; i++)
        // {
        //     free(p->tmp.num[i]);
        // }
        // free(p->tmp.num);

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
    if (PUSHDOWN(p) == true)
    {
        printf(" => IS PUSHDOWN\n");
        printCur(p, __LINE__);
        return true;
    }
    // else if (UNARYOP(p))
    // {
    //     printf(" => IS UNARYOP\n");
    //     return true;
    // }
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

    // allocate_space(p);

    if (digits_only(p->wds[p->cw]))
    {
        // #ifdef INTERP
        printf("INTERPs triggered, is digit only\n");
        // var *v = ncalloc(1, sizeof(var));
        p->variables[p->pos].y = 1;
        p->variables[p->pos].x = 1;
        printf("ALLOCATING NUM!!!!\n");
        printf("pos = %d\n", p->pos);
        printf("my = %d\n", p->variables[p->pos].y);
        printf("mx = %d\n", p->variables[p->pos].x);

        printf("IS EMPTY = %d\n", p->variables[p->pos].num);

        p->tmp.num = (int **)n2dcalloc(p->variables[p->pos].y, p->variables[p->pos].x, sizeof(int *));
        p->tmp.y = 1;
        p->tmp.x = 1;
        for (int y = 0; y < p->tmp.y; y++)
        {
            for (int x = 0; x < p->tmp.x; x++)
            {
                p->tmp.num[y][x] = atoi(p->wds[p->cw]);
            }
        }

        push(p);
        // #endif
        return true;
    }

    if (is_variable(p->wds[p->cw]))
    {

        printf("is variable\n");
        printCur(p, __LINE__);

        var v = get_value(p);
        p->tmp = v;
        // printf("v-val = %d\n", v.num);
        if (!v.num)
        {
            ERROR("VARIABLE UNDEFINED????\n");
        }

        push(p);

        return true;
    }

    return false;
}
bool UNARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "U-NOT"))
    {
        return true;
    }

    if (strsame(p->wds[p->cw], "U-EIGHTCOUNT"))
    {
        return true;
    }

    return false;
}

bool BINARYOP(Program *p)
{

    if (strsame(p->wds[p->cw], "B-ADD"))
    {
        printf("IN B-ADD\n");
        // #ifdef INTERP
        printf("p->pos = : %d\n", p->pos);
        var *v1 = pop(p);
        var *v2 = pop(p);

        printf("v1  y:%d , x:%d\n", v1->y, v1->x);
        printf("v2 (LEFT-MOST) y:%d , x:%d\n", v2->y, v2->x);

        // var *v3 = ncalloc(1, sizeof(var));
        p->tmp.num = (int **)n2dcalloc(v2->y, v2->x, sizeof(int *));

        if (v1->y == 1 && v1->x == 1 && v2->y == 1 && v2->x == 1)
        {
            printf("COND 1\n");
            p->tmp.y = 1;
            p->tmp.x = 1;
            for (int y = 0; y < 1; y++)
            {
                for (int x = 0; x < 1; x++)
                {
                    p->tmp.num[y][x] = v2->num[y][x] + v1->num[y][x];
                }
            }
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y == 1 || v1->x == 1))
        {
            printf("COND 2\n");
            p->tmp.y = v2->y;
            p->tmp.x = v2->x;
            int final_value = v1->num[0][0] + v2->num[0][0];

            printf("final_value: %d\n", final_value);

            for (int y = 0; y < p->tmp.y; y++)
            {
                for (int x = 0; x < p->tmp.x; x++)
                {
                    p->tmp.num[y][x] = final_value;
                    // printf("%d", p->tmp.num[y][x]);
                }
            }
            printf("assigned success\n");
        }

        if ((v2->y > 1 || v2->x > 1) && (v1->y > 1 || v1->x > 1))
        {
            if (v2->y == v1->y && v2->x == v1->x)
            {
                printf("COND 3\n");
                p->tmp.y = v2->y;
                p->tmp.x = v2->x;

                int final_value = v1->num[0][0] + v2->num[0][0];

                printf("final_value: %d\n", final_value);

                for (int y = 0; y < p->tmp.y; y++)
                {
                    for (int x = 0; x < p->tmp.x; x++)
                    {
                        p->tmp.num[y][x] = final_value;
                    }
                }
            }
        }

        push(p);

        // free(v3);
        // #endif
        return true;
    }

    if (
        strsame(p->wds[p->cw], "B-AND") ||
        strsame(p->wds[p->cw], "B-OR") ||
        strsame(p->wds[p->cw], "B-GREATER") ||
        strsame(p->wds[p->cw], "B-LESS") ||
        strsame(p->wds[p->cw], "B-TIMES") ||
        strsame(p->wds[p->cw], "B-EQUALS"))
    {
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
    printf("FINAL?\n");
    // printf("val =%d\n", p->variables[pos].num[0][0]);

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

//STACK
Stack *createStack(int capacity)
{
    // malloc(sizeof(struct Stack));
    Stack *stack = (struct Stack *)ncalloc(1, sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    // stack->arr = (var *)n2dcalloc(100, 100, sizeof(var));
    stack->arr = (var *)calloc(capacity, sizeof(var));

    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(Program *p)
{
    printf("pushing to stack : %d \n", p->stack->top);
    if (isFull(p->stack))
        return;
    printf("pushing...\n");
    p->stack->arr[++p->stack->top] = p->tmp;

    printf("pushed to stack : %d, with value: %d \n", p->stack->top, p->stack->arr[p->stack->top].num[0][0]);
}

// Function to remove an item from stack.  It decreases top by 1
var *pop(Program *p)
{
    if (isEmpty(p->stack))
        return NULL;

    printf("popping, top = %d\n", p->stack->top);
    // printf("HI %d\n",stack->arr[stack->top]);

    // printf("pstack inside pop: %d\n", stack->arr[0].num[0][0]);

    for (int y = 0; y < 1; y++)
    {
        for (int x = 0; x < 1; x++)
        {
            printf("%d", p->stack->arr[p->stack->top].num[y][x]);
        }
        printf("\n");
    }
    var *variable = &p->stack->arr[p->stack->top];
    p->stack->top--;

    return variable;
}

// Function to return the top from stack without removing it
int **peek(struct Stack *stack)
{
    if (isEmpty(stack))
        return NULL;
    return NULL;
}

void clear_stack(Program *p)
{
    printf("CLEARING STACK and free, now top = %d\n", p->stack->top);

  

    p->stack->top = -1;
    // printf("val = %d\n", p->tmp.num[0][0]);
    free(p->tmp.num[0]);
    free(p->tmp.num);

    // free(p->variables[p->pos].num[0]);
    // free(p->variables[p->pos].num);
    printf("freed ...........\n");
}
