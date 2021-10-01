#include <stdio.h>
#include <stdbool.h>

int isPrime(int number);

int main()
{
    int target = 10;

    int count = 0;
    int numberOfPrimeFound = 0;
    int i = 2;
    printf("before while loop\n");
    while (numberOfPrimeFound < target)
    {
        // printf("numberOfPrimeFound = %d\n", numberOfPrimeFound);
        // printf("user_input = %d\n", user_input);
        if (isPrime(i))
        {   
            printf("%d\n",i);
            if (i % 10 == 3)
            {

                count++;
            }
            numberOfPrimeFound++;
            i++;
        }
        else
        {
            i++;
        }
    }

    printf("count = %d\n",count);

    return 0;
}

int isPrime(int number)
{
    int i;
    for (i = 2; i < number; i++)
    {
        if (number % i == 0 && i != number)
        {

            return 0;
        }
    }

    return 1;
}