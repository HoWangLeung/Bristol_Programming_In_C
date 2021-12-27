#include "nlab.h"
#define FILESIZE 100
// #define INTERP

bool PROG(Program *p)
{
    bool is_BEGIN = false;
    if (!strsame(p->wds[p->cw], "BEGIN"))
    {
        ERROR("No BEGIN statement ?");
    }
    p->cw = p->cw + 1;
    printCur(p, __LINE__);
    if (!strsame(p->wds[p->cw], "{"))
    {
        ERROR("Expected {");
    }
    p->cw = p->cw + 1;
    INSTRCLIST(p);
    return true;
}

bool INSTRCLIST(Program *p)
{
    if (strsame(p->wds[p->cw], "}"))
    {

        return true;
    }
    if (!INSTRC(p))
    {
        printf("MISSING } \n");
        ERROR("INSTRC ERROR\n");
    }

    p->cw = p->cw + 1;
    INSTRCLIST(p);

    return true;
}

bool INSTRC(Program *p)
{
    printf("======== parsing INSTRC ========\n");
    if (strsame(p->wds[p->cw], "PRINT") && PRINT(p))
    {
        printf("PRINTING\n");
        return true;
    }
    if (strsame(p->wds[p->cw], "SET"))
    {
        if (SET(p))
        {
            printf("SET OK\n");
            printCur(p, __LINE__);
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
    printCur(p, __LINE__);
    ERROR("INSTRC : Expecting a PRINT or SET or CREATE or LOOP OR '}' ?");
    return false;
}

bool PRINT(Program *p)
{
    p->cw = p->cw + 1;
    if (is_variable(p->wds[p->cw]))
    {
        printf("print variable \n ");
        return true;
    }

    if (is_string(p->wds[p->cw]))
    {
        printf("print string \n ");
        printf("%s\n", p->wds[p->cw]);
        return true;
    }

    ERROR("PRINT failure -> :");
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

    allocate_space(p);

    printf("hi = %c\n", p->wds[p->cw][1]);

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

    printf("SET RETURN TRUE\n");
    return true;
}
bool CREATE(Program *p)
{
    printf("======== parsing CREATE ========\n");
    printCur(p, __LINE__);
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
                printf("returning true ....\n");
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
            return true;
        }
    }

    return false;
}
bool LOOP(Program *p)
{
    if (p)
        printf("loop something \n");
    printCur(p, __LINE__);

    p->cw = p->cw + 1;
    printCur(p, __LINE__);
    if (!VARNAME(p))
    {
        printf("VAR NOT OK\n");
        ERROR("INVALID VARNAME");
    }

    p->cw = p->cw + 1;
    if (!INTEGER(p))
    {
        printf("INTEGER NOT OK\n");
        ERROR("INVALID INTEGER");
    }
    p->cw = p->cw + 1;
    if (!LEFTBRACKET(p))
    {
        printf("LEFT BRACKET NOT OK\n");
        ERROR("INVALID INTEGER");

        // if (INTEGER(p))
        // {
        //     p->cw = p->cw + 1;
        //     if (LEFTBRACKET(p))
        //     {
        //         printf("valid loop........\n");
        //         p->cw = p->cw + 1;
        //         INSTRCLIST(p);
        //         return true;
        //     }
        // }
    }
    p->cw = p->cw + 1;
    printCur(p, __LINE__);
    INSTRCLIST(p);

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
    printCur(p, __LINE__);
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
    printCur(p, __LINE__);
    if (p->wds[p->cw][0] == ';')
    {
        printf("YES ;\n");
        return true;
    }
    if (p->wds[p->cw][0] == 0)
    {
        printf("emp null\n");
        ERROR("EMPTY NULL");
    }

    printCur(p, __LINE__);

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
        printCur(p, __LINE__);
        ERROR("POLISH ERROR:EXPECT PUSHDOWN | UNARYOP | BINARYOP ");
    }
}

bool STRING(Program *p)
{
    if (is_string(p->wds[p->cw]))
    {
        return true;
    }
    return false;
}

bool FILENAME(Program *p)
{

    if (STRING(p))
    {

        return true;
    }

    return false;
}

bool PUSHDOWN(Program *p)
{
    if (digits_only(p->wds[p->cw]))
    {
        printf("is integer\n");

        printCur(p, __LINE__);
#ifdef INTERP
        printf("INTERP triggered");
        set_value(p);
#endif

        return true;
    }

    printCur(p, __LINE__);

    if (is_variable(p->wds[p->cw]))
    {
        printf("is variable\n");
        printCur(p, __LINE__);

#ifdef INTERP
        var *v = get_value(p);
        print_variable(v);
        for (int y = 0; y < v->y; y++)
        {
            for (int x = 0; x < v->x; x++)
            {
                p->variables[p->pos]->num[y][x] = v->num[y][x];
            }
        }
#endif
        return true;
    }

    return false;
}
bool UNARYOP(Program *p)
{
    printCur(p, __LINE__);
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
    if (
        strsame(p->wds[p->cw], "B-AND") ||
        strsame(p->wds[p->cw], "B-OR") ||
        strsame(p->wds[p->cw], "B-GREATER") ||
        strsame(p->wds[p->cw], "B-LESS") ||
        strsame(p->wds[p->cw], "B-ADD") ||
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
    printCur(p, __LINE__);
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
    printCur(p, __LINE__);
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

    printCur(p, __LINE__);
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
    printf("test mode called\n");
    return false;
}
void allocate_space(Program *p)
{
    printf("%c\n", p->wds[p->cw][1]);
    int pos = get_pos(p);
    printf("POS = %d\n", pos);
    p->pos = pos;
    p->variables[pos] = ncalloc(1, sizeof(var));
    p->variables[pos]->y = 1;
    p->variables[pos]->x = 1;
    p->variables[pos]->num = (int **)n2dcalloc(1, 1, sizeof(int *));
}

bool set_value(Program *p)
{
    for (int y = 0; y < p->variables[p->pos]->y; y++)
    {
        for (int x = 0; x < p->variables[p->pos]->x; x++)
        {
            p->variables[p->pos]->num[y][x] = atoi(p->wds[p->cw]);
        }
    }

    for (int y = 0; y < p->variables[p->pos]->y; y++)
    {
        for (int x = 0; x < p->variables[p->pos]->x; x++)
        {
            printf("%d", p->variables[p->pos]->num[y][x]);
        }
        printf("\n");
    }
}

var *get_value(Program *p)
{
    printCur(p, __LINE__);
    int pos = get_pos(p);
    printf("pos =%d\n", pos);
    if (p->variables[pos] != NULL)
    {
        printCur(p, __LINE__);

        return p->variables[pos];
    }

    return NULL;
}

int get_pos(Program *p)
{
    return p->wds[p->cw][1] - 'A';
}

void print_variable(var *v)
{
    printf("printing variable:\n");
    if (v)
    {
        for (int y = 0; y < v->y; y++)
        {
            for (int x = 0; x < v->x; x++)
            {
                printf("%d", v->num[y][x]);
            }
            printf("\n");
        }
    }
}
