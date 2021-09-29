
#include<stdio.h>
#define A 1
#define C 5
#define M 11


int main()
{
    int seed = 0;

    for (int i = 0; i < 5; i++)
    {
        seed = (A * seed + C) % M;
        printf("%d\n",seed);
    }

    
}