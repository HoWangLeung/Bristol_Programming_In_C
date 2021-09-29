
#include <stdio.h>
#define A 7
#define C 5
#define M 11

int main()
{
    int seed = 0;
    int first;
    for (int i = 0; i < 20; i++)
    {

        if (i == 0)
        {
            first = seed;
        }
        seed = (A * seed + C) % M;
        if (seed == first)
        {
            printf("repeated at  %d\n th ", i + 1);
        }

        printf("seed = %d\n", seed);
    }
}