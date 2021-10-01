#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int count_number_of_digit(int x);
int main()
{
    int x = 4;
    int numberOfDigit = 0;
    numberOfDigit = count_number_of_digit(x);
    int i = 0;
    int dividend = 4;
    int divisor = 3;
    while (i <= 3)
    {
        printf("dividend = %d\n", dividend);
        printf("divisor = %d\n", divisor);
        printf("%d\n", dividend / divisor);

        if (i % 2 == 0 && i!=0)
        {
            x = x + (dividend / divisor);
        }
        else
        {
            printf("adding\n");
            x = x - (dividend / divisor);
        }
        printf("value of x = %d\n", x);
        numberOfDigit = count_number_of_digit(x);
        printf("number of digit = %d\n", numberOfDigit);
        i++;
        divisor += 2;
    }

    return 0;
}

int count_number_of_digit(int x)
{
    int count = 0;
    do
    {
        x /= 10;
        ++count;
    } while (x != 0);
    return count;
}
