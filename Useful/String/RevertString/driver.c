
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

void reverse(const char *s)
{
    char str[256];
    int len = strlen(s);
    strcpy(str, s);
    for (int i = 0; i < len / 2; i++)
    {
        // temp variable use to temporary hold the string
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    printf("%s\n", str);
}
