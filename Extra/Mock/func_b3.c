#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

bool negativeedge(int a[][10], int h)
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (y >= 1 && y < h - 1 && x > 0 && x < 9)
            {
                if (a[y][x] < 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}