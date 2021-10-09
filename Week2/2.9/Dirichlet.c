#include <stdio.h>
#include <stdbool.h>

int isPrime(int number);

int main()
{
    int target = 1000;

    int count = 0;
    int numberOfPrimeFound = 0;
    int i = 2;
    printf("before while loop\n");
    while (numberOfPrimeFound < target)
    {
        if (isPrime(i))
        {   
       
            if (i % 10 == 3)
            {
                count++;
                printf("%d ---> %d\n",count,i);
            }
            numberOfPrimeFound++;
            i++;
        }
        else
        {
            i++;
        }
    }
   // printf("count = %d\n",count);
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