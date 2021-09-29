#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int main()
{

    int a, b, c;
    printf("Input three integers: ");
    scanf("%d%d%d", &a, &b, &c);
    int result = (a+b+c)*2 +7;
    printf("Twice the sum of integers plus 7 is %d !\n",result);

}