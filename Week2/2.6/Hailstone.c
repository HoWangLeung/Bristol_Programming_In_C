#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int main()
{
    int longest = 0;
    int largest = 0;
    int count = 1;
    int sum = 0;
    int longest_initial = 0;
    int largest_initial = 0;
    for (int i = 2; i < 50000; i++)
    {
        int number = i;
        sum = number;
        longest = count;
        while (number != 1)
        {
            if (number % 2 == 0)
            {
                number /= 2;
            }
            else
            {
                number = number * 3 + 1;
            }
            sum += number;
            count++;

            if (sum > largest)
            {
                largest = sum;
                largest_initial = i;
            }
            if (count > longest)
            {
                longest = count;
                longest_initial = i;
            };
        }
    }

    printf("\nlongest hailstone = %d\n", longest);
    printf("sum of hailstone = %d\n\n", largest);

    printf("longest initial = %d\n", longest_initial);
    printf("largest initial = %d\n\n", largest_initial);

    return 0;
}
