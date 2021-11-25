
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

void reverse(char *s);
void check(const char *s)
{
    int i;
    // char s[256];
    scanf("%d", &i);

    printf("input is =%d\n",i);
}

void reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    printf("%s\n", str);
}
