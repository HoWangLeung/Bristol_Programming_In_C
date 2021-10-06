#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_LENGTH 5

int main()
{
    char firstName[100000];
    char middleName[100000];
    char lastName[100000];

    char vowelList[] = {'a', 'e', 'i', 'o', 'u'};
    char nonVowelList[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    int count = 0;
    for (int k = 0; k < 21; k++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 21; i++)
            {
                firstName[count] = nonVowelList[k];
                middleName[count] = vowelList[j];
                lastName[count] = nonVowelList[i];
                count++;
            }
        }
    }

    for (int i = 0; i < 52; i++)
    {
        printf("%i first= %c middle = %c last = %c\n", i, firstName[i], middleName[i], lastName[i]);
    }

    return 0;
}