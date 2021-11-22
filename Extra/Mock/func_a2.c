#include "common.h"

char *strnodupes(const char *s)
{
    int i =0;
    while(s[i]!='\0'){
        printf("%c\n",s[i++]);
    }


    int n = strlen(s);
    char *str = calloc(sizeof(char), 100);
    strcpy(str, s);
    char flag[256] = {0}; //Assuming sizeof char is 8. So max 256 different characters.
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n;)
        {
            if (str[i] == str[j])
            {
                //printf("%d\n",j);
                for (int k = j; k < n; k++)
                {
                    str[k] = str[k + 1];
                }
                n--;
            }
            else
            {
                j++;
            }
        }
    }


    printf("%s\n", str);

    return str;
}
