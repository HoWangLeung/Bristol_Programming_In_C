
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

bool check(const char *s1)
{
    int index = 0;
    char str[256];
    strcpy(str, s1);
    int len = strlen(str);
    int arr[255] = {0};
    //alternative: str[i] != 0
    for (int i = 0; i < len; i++)
    {
        // if (isalnum(str[i]))
        // {
        printf("str[i] = %d\n", str[i]);
        arr[str[i]] += 1;
        // }
    }
    int max = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[str[i]] > max)
        {
            max = arr[str[i]];
            index = i;
        }
    }
    printf("max = %d\n", index);
    printf("max char = %c\n", str[index]);
}
