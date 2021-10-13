#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define R 5
#define C 5

int main()
{
    int a[R][C] = {{0, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0}};

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%d",a[i][j]);
        }
        printf("\n");
        
    }
    
    

    return 0;
}
