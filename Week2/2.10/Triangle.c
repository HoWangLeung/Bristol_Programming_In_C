#include <stdio.h>
#include <stdbool.h>

int isPrime(int number);

int main()
{
    int target = 10;
    for (int i = 1; i < target; i++)
    {

        int result = i * ((i + 1) / 2);
        printf("%d\n", result);
    }

    return 0;
}
