#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int isPrime(int number);

int main()
{
    int x = 0;
    printf("input a number:");
    scanf("%d", &x);

    int result = sin(x) * sin(x) + cos(x) * cos(x);
    printf("result = %d\n",result);

    return 0;
}
