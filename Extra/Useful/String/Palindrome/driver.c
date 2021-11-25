
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
bool isPalindrome(char *s);
bool check(const char *s)
{
    char str[256];
    strcpy(str, s);
    return isPalindrome(str);
}
bool isPalindrome(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        str[i] = tolower(str[i]);
    }
    printf("test = %s\n", str);

    int l = 0;
    int r = n - 1;
    while (l < r)
    {
        if (!isalpha(str[l]))
        {

            l++;
        }
        else if (!isalpha(str[r]))
        {
            r--;
        }
        else
        {

            if (str[l] != str[r])
            {
                return false;
            }
            l++;
            r--;
        }
    }

    return true;
}
