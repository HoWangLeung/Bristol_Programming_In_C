#include <stdio.h>
#include <stdbool.h>

int isPrime(int number);

int main()
{
    int user_input;
    printf("How many prime number do you wish to print ? \n");
    scanf("%d", &user_input);

    int numberOfPrimeFound = 0;
    int i = 2;
    printf("before while loop\n");
    while (numberOfPrimeFound < user_input)
    {
        // printf("numberOfPrimeFound = %d\n", numberOfPrimeFound);
        // printf("user_input = %d\n", user_input);
        if (isPrime(i))
        {
            numberOfPrimeFound++;
            i++;
        }
        else
        {
            i++;
        }
    }

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
    printf("%d\n", number);
    return 1;
}