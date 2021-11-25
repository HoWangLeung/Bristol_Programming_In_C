#include "common.h"

//version 1
// char *strnodupes(const char *s)
// {
//     int n = strlen(s);

//     char *str = calloc(sizeof(char), 100);
//     strcpy(str, s);
//     char flag[256] = {0}; //Assuming sizeof char is 8. So max 256 different characters.
//     int i = 0;
//     int j = 0;

//     for (i = 0; i < n; i++)
//     {
//         if (0 == flag[str[i]]) //Check if character is already found.
//         {
//             flag[str[i]] = 1; //If a character is found for the first time, enable corresponding flag.
//             str[j] = str[i];
//             j++;
//         }
//     }
//     str[j] = '\0';

//     printf("%s\n", str);

//     return str;
// }

// Version 2
// char *strnodupes(const char *s)
// {
//     int n = strlen(s);

//     char *str = (char *)malloc(sizeof(char) * 100);
//     strcpy(str, s);

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n;) //don't need j++;
//         {
//             if (str[i] == str[j])
//             {
//                 for (int k = j; k < n; k++)
//                 {
//                     str[k] = str[k + 1];
//                 }
//                 n--;
//             }
//             else
//             {
//                 j++;
//             }
//         }
//     }

//     printf("res = %s\n", str);

//     return str;
// }
//Version 2
char *strnodupes(const char *s)
{
    // char str[100];
    char *str = (char *)malloc(sizeof(char) * 100);
    strcpy(str, s);
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n;)
        {
            if (str[j] == str[i])
            {
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
    printf("str= %s\n", str);

    return str;
}
