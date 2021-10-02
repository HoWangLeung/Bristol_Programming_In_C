#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_LENGTH 5

typedef struct
{
    char firstname;
    char middlename;
    char lastname;
} name;

int main()
{
    name myname;
    char vowelList[] = {'a', 'e', 'i', 'o', 'u'};
    char alphabetList[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0; i <= 26; i++)
    {

        myname.firstname = alphabetList[i];
    }

    printf("%d\n", myname.firstname);

        return 0;
}
