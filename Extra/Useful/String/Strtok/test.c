#include <stdio.h>
#include <string.h>
int main()
{
    char str[] = "- This, a sample string.";
    char *pch;
    printf("Splitting string \"%s\" into tokens:\n", str);
    char *temp[256];
    pch = strtok(str, " ,.-");
    int t = 0;
    while (pch != NULL)
    {
        temp[t++] = pch;
        pch = strtok(NULL, " ,.-");
    }
    for (int i = 0; i < t; i++)
    {
        printf("%s\n", temp[i]);
    }

    return 0;
}