#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define N 20
bool derange(const char *s1, const char *s2);

int main(void)
{
    int arr[N][N] = {0};
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            arr[y][x] = rand() % ((9 + 1) - 0) + 0;
        }
        // printf("\n");
    }
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            printf("%d", arr[y][x]);
        }
        printf("\n");
    }
    printf("\n");

    for (int k = 0; k < N; k++)
    {
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (x < N - 1 && arr[y][x + 1] < arr[y][x])
                {
                    int temp = arr[y][x];
                    arr[y][x] = arr[y][x + 1];
                    arr[y][x + 1] = temp;
                }
            }
            // printf("\n");
        }
    }

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            printf("%d", arr[y][x]);
        }
        printf("\n");
    }

    return 0;
}
