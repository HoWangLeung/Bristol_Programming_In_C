#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_LENGTH 5

bool isVowel(char c);

int main()
{

    char characters[MAX_LENGTH];
    printf("Enter the string:\n");
    scanf("%s", characters);
    // printf("%s\n", characters);

    for (int i = 0; i < MAX_LENGTH; i++)
    {

        if (isVowel(characters[i]))
        {
            characters[i] = toupper(characters[i]);
        }
        printf("%c\n", characters[i]);
    }
    return 0;
}

bool isVowel(char c)
{
    char vowelList[] = {'a', 'e', 'i', 'o', 'u'};
    for (int j = 0; j < 5; j++)
    {
        if (c == vowelList[j])
            return 1;
    }
    return 0;
}
