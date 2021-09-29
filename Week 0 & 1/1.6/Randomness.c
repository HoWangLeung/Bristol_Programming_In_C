#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define HEIGHT 5
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int median = RAND_MAX / 2;
    printf("median = %d\n", median);
    int minus_cnt = 0;
    int plus_cnt = 0;
    for (int i = 0; i < 499; i++)
    {
        int randNum = rand();
        printf("randNum = %d\n", randNum);
        if (randNum > median)
        {
            plus_cnt++;
        }
        else if (randNum < median)
        {
            minus_cnt++;
        }
    }

    printf("difference = %d", plus_cnt - minus_cnt);
}
