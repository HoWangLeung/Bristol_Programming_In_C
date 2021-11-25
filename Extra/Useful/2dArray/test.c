#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
//int strend(const char *s, const char *t);

int main(void)
{
    char *a = "aBc";

    int n = strlen(a);
    char s[50];
    strcpy(s, a);

    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = tolower(s[i]);
        }
        else
        {
            s[i] = toupper(s[i]);
        }
    }

    printf("%s\n", s);

    return 0;
}