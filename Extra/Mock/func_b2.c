#include "common.h"
#include<limits.h>

int closestmean(const int l[], const int n)
{
    int n = INFINITY;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        printf("i = %d\n", i);
        sum += l[i];
    }
   
    int average = sum / n;

    int min = 90000000;
    for (int i = 0; i < n; i++)
    {
        if (l[i] > average)
        {
            if (l[i] - average < min)
            {
                min = l[i] - average;
            }
        }
        else
        {
            if (average - l[i] < min)
            {
                min = average - l[i];
            }
        }
    }
    printf("min = %d\n", min);

    for (int i = 0; i < n; i++)
    {
        if (l[i] > average)
        {
            if (l[i] - average ==min)
            {
                return l[i];
            }
        }
        else 
        {
            if (average - l[i] == min)
            {
                 return l[i];
            }
        }
    }

    
}
//INT_MAX
//INT_MIN