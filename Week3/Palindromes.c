#include <ctype.h>
#include <stdio.h>
#define MAX 150

void remove_spaces(char *s);
int main(void)
{

    printf("Input  a phrase:");
    char input[MAX];
    int n = 0;
    fgets(input, MAX, stdin);


    for (int i = 0; input[i] != '\0'; ++i)
    {
        n = i;
    }
    for (int i = 0; i < n; i++)
    {
        char c = input[i];
        if (isupper(c))
        {
            c = tolower(c);
        }
    }
    remove_spaces(input);
    printf("string is: %s\n", input);
    return 0;
}

void remove_spaces(char *s)
{
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ == *d++);
}







