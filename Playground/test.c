#include <stdio.h>
#include <string.h>
#include <ctype.h>

void add(int  a);

int main(int argc, char **argv)
{

    int a = 1;

    add(&a);

    printf("a = %d\n",a);

    return 0;
}

void add(int a )
{int a
   a = a+1;
}