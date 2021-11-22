#include "common.h"
#include <stdbool.h>
void sortString(char string[50]);

bool struses(const char *s1, const char *s2)
{
    int n = strlen(s1);
    for (int i = 0; i < n; i++)
    {
        if (strchr(s2, s1[i]) == NULL)
        {
            printf("invalid found %c character \n", s1[i]);
            return false;
        }
        else
        {
            printf("found at %d\n", strchr(s2, s1[i]) - s2);
        }
    }

    return true;
}

void sortString(char string[50])
{
    char temp;
    int n = strlen(string);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (string[i] > string[j])
            {
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
            }
        }
    }
}
