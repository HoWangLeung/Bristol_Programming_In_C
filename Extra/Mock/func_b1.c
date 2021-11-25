#include "common.h"

int numdiff(const int l[], const int n)
{
    if (l == NULL)
    {
        return 0;
    }
    int arr[n];
    int size = n;
 
    int arr1[256] = {0};
  

    return size;
}

//  if (l == NULL)
//     {
//         return 0;
//     }
//     int arr[n];
//     int size = n;
//     for (int i = 0; i < size; i++)
//     {
//         arr[i] = l[i];
//         printf("%d\n",arr[i]);
//     }
//     int i, j, k;
//     for (i = 0; i < size; i++)
//     {
//         for (j = i + 1; j < size; j++)
//         {
//             /* If any duplicate found */
//             if (arr[i] == arr[j])
//             {
//                 for (int k = j; k < size-1; k++)
//                 {
//                     arr[k]=arr[k+1];
//                 }
//                 size--;
//                 j--;
//             }
//         }
//     }

//     printf("size = %d\n", size);

//     return size;