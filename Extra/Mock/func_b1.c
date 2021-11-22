#include "common.h"

int numdiff(const int l[], const int n)
{
    if (l == NULL)
    {
        return 0;
    }
    int arr[n];
    int size = n;

    for (int i = 0; i < size; i++)
    {
        arr[i] = l[i];
    }
    int i, j, k;
    for (i = 0; i < size; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            /* If any duplicate found */
            if (arr[i] == arr[j])
            {
                /* Delete the current duplicate element */
                for (k = j; k < size - 1; k++)
                {
                    arr[k] = arr[k + 1];
                }

                /* Decrement size after removing duplicate element */
                size--;

                /* If shifting of elements occur then don't increment j */
                j--;
            }
        }
    }
    printf("size = %d\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
    return size;
}
