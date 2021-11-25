
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

bool derange(const char *s1, const char *s2)
{

    char str1[256];
    char str2[256];
    strcpy(str1, s1);
    strcpy(str2, s2);

    int len_s1 = strlen(str1);
    int len_s2 = strlen(str2);

    int arr1[256] = {0};
    int arr2[256] = {0};

    for (int i = 0; i < len_s1; i++)
    {
        arr1[str1[i]] = i;
    }
    for (int i = 0; i < len_s2; i++)
    {
        arr2[str2[i]] = i;
    }

    for (int i = 0; i < 256; i++)
    {
        if (arr1[i] != 0 && arr2[i] != 0 && arr1[i] == arr2[i])
        {
            return false;
        }
    }



    return true;
}