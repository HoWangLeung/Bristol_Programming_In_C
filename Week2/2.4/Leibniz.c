#include <stdio.h>
#include <math.h>

int main()
{
    double x = 4;
    double y = 3;
    double sign = -1;
    int i = 0;
    do
    {
        x = x + (sign * 4 / y);
        sign *= -1;
        y += 2;
        i++;
    } while ((long int)(x * 1000000000) != (long int)3141592653);
    printf("answer = %f\n",x * 1000000000);
    printf("num of iteration %d\n", i);
    return 0;
}
