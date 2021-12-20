#include "nlab.h"
#define FILESIZE 100

bool PROG(Program *p)
{

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
        ERROR("INSTRC ERROR\n");
    }
    p->cw = p->cw + 1;
    if (INSTRCLIST(p))
    {
        return true;
    }
    return false;
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
    ERROR("Expecting a PRINT or SET or CREATE or LOOP ?");
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
    // p->cw = p->cw + 1;
    //     printCur(p, __LINE__);
    // if (p->wds[p->cw][0] != '$')
    // {
    //     ERROR("Expected a $ but received other symbol \n");
    // }

    // if (!p->wds[p->cw][1] || (p->wds[p->cw][1] < 'A' && p->wds[p->cw][1] > 'Z'))
    // {
    //     ERROR("Expected Variable A-Z \n");
    // }
    if (!VARNAME(p))
    {
        return false;
    }

    //===============
    //======For := ==
    //===============

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
    POLISHLIST(p);

    return true;
}
bool CREATE(Program *p)
{
    printf("======== parsing CREATE ========\n");
    printCur(p, __LINE__);
    if (ROWS(p) && COLS(p) && VARNAME(p))
    {
        printf("returning....\n");
        return true;
    }

    printf("COUNTINUE TO CHECK FILENAME & VARNAME\n");
    if (FILENAME(p) && VARNAME(p))
    {
        return true;
    }

    return false;
}
bool LOOP(Program *p)
{
    if (p)
        printf("loop something \n");

    if (VARNAME(p) && INTEGER(p) && LEFTBRACKET(p))
    {
        printf("valid loop........\n");
        p->cw = p->cw + 1;
        INSTRCLIST(p);
        return true;
    }

    return false;
}

bool LEFTBRACKET(Program *p)
{
    p->cw = p->cw + 1;
    if (strsame(p->wds[p->cw], "{"))
    {
        return true;
    }

    return false;
}

bool INTEGER(Program *p)
{
    p->cw = p->cw + 1;
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
    if (p->wds[p->cw][0] == ';')
    {
        return true;
    }
    printCur(p, __LINE__);

    POLISH(p);
    p->cw = p->cw + 1;
    POLISHLIST(p);

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
        ERROR("EXPECT PUSHDOWN | UNARYOP | BINARYOP ")
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

        return true;
    }
    printCur(p, __LINE__);
    if (is_variable(p->wds[p->cw]))
    {
        printf("is variable\n");
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

    p->cw = p->cw + 1;
    printCur(p, __LINE__);
    if (digits_only(p->wds[p->cw]))
    {
        //ERROR("NOT DIGIT ONLY\n");
        return true;
    }

    return false;
}

bool COLS(Program *p)
{
    printf("handling ROWS\n");

    p->cw = p->cw + 1;
    printCur(p, __LINE__);
    if (digits_only(p->wds[p->cw]))
    {
        // ERROR("NOT DIGIT ONLY\n");
        return true;
    }

    return false;
}

bool VARNAME(Program *p)
{
    printf("check if VARNAME\n");
    p->cw = p->cw + 1;
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
