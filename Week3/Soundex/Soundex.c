#include <stdio.h>
#include <string.h>
#include <ctype.h>

void soundex(char name[]);
char getNumber(char c);
void remove_immediate_next(char code[], char name[]);
void remove_seperated_soundex(char code[], char name[]);
void removeChar(char p[], int idxToDel);

int main(int argc, char **argv)
{
    char name[] = "Wu";
    soundex(name);
    return 0;
}

void soundex(char name[])
{
    char firstChar = name[0];
    printf("name = %s\n", name);
    int name_length = (int)strlen(name);
    char code[100];
    printf("length of code %d\n", name_length);

    for (int i = 0; i < name_length; i++)
    {
        code[i] = getNumber(name[i]);
        code[i + 1] = '\0';
    }
    printf("%s\n", code);

    for (int i = 0; i < (int)strlen(name); i++)
    {
        remove_immediate_next(code, name);
    }

    printf("=> %s\n", name);
    for (int i = 0; i < (int)strlen(name); i++)
    {
        remove_seperated_soundex(code, name);
    }

    code[0] = toupper(firstChar);

    for (int i = 0; i < (int)strlen(code); i++)
    {
        if (code[i] == '0')
        {
            removeChar(code, i);
        }
    }
    printf(" code =  %s\n", code);
    printf("lengths of code is %ld\n", strlen(code));
    while ((int)strlen(code) < 4)
    {
        code[strlen(code)] = '0';
        code[strlen(code) + 1] = '\0';
    }

    while ((int)strlen(code) > 4)
    {
        code[strlen(code) - 1] = '\0';
    }

    printf("==> %s\n", name);
    printf("final code =  %s\n", code);
}

void remove_seperated_soundex(char code[], char name[])
{
    int tobeRemoved = 0;
    printf("code = %s\n", code);
    for (int i = 0; i < (int)strlen(name); i++)
    {

        if ((name[i] == 'h' || name[i] == 'w') && code[i - 1] == code[i + 1])
        {
            printf("target i = %d\n", i + 1);
            tobeRemoved = i + 1;
            removeChar(name, tobeRemoved);
            removeChar(code, tobeRemoved);
        }
        else
        {
            printf("no target\n");
        }
    }
}
void removeChar(char p[], int idxToDel)
{
    printf("removeChar()\n");
    memmove(&p[idxToDel], &p[idxToDel + 1], strlen(p) - idxToDel);
  
}

void remove_immediate_next(char code[], char name[])
{
    printf("length of code in remove  = %lu \n", strlen(code));
    int to_be_removed = 0;
    for (int i = 0; i < (int)strlen(code); i++)
    {
        printf("code = %c \n", code[i]);
        if (code[i] == code[i + 1])
        {
            printf("character to be removed ===> %c\n", name[i]);
            printf("-------\n");
            to_be_removed = i + 1;
            removeChar(name, to_be_removed);
            removeChar(code, to_be_removed);
        }
    }
}

char getNumber(char c)
{
    c = isupper(c) == 1 ? tolower(c) : c;
    printf("c = %c \n", c);
    if (c == 'b' || c == 'f' || c == 'p' || c == 'v')
    {

        return '1';
    }
    else if (c == 'c' || c == 'g' || c == 'j' || c == 'k' || c == 'q' || c == 's' || c == 'x' || c == 'z')
    {
        return '2';
    }

    else if (c == 'd' || c == 't')
    {

        return '3';
    }
    else if (c == 'l')
    {
        return '4';
    }
    else if (c == 'm' || c == 'n')
    {
        return '5';
    }
    else if (c == 'r')
    {
        return '6';
    }

    else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'h' || c == 'w' || c == 'y')
    {
        return '0';
    }
    else
    {
        return '-';
    }
}