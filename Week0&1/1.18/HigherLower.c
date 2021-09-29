#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
int cleanStdin();
int checkIsLowerThenSecret(int x, int secret);
void printResult(bool isLowerThenSecret, int i);
void getValidatedInput(int *x);
void checkHasWon(int x, int secret);

int main()
{
    int x;
    int remaining = 10;
    int secret = arc4random_uniform(1001);
    printf("secret = %d\n", secret);
    for (int i = remaining; i > 0; i--)
    {
        getValidatedInput(&x);
        checkHasWon(x, secret);
        bool isLowerThenSecret = checkIsLowerThenSecret(x, secret);
        printResult(isLowerThenSecret, i);
    }
}

void checkHasWon(int x, int secret)
{
    if (x == secret)
    {
        printf("You guessed it right !\n");
        exit(0);
    }
}
void getValidatedInput(int *x)
{
    char term;
    int attempt = 0;
    do
    {
        if (attempt == 0)
        {
            printf("Input an Integer: ");
        }
        else
        {
            printf("You did not input an Integer, try again : ");
        }
        attempt++;
      

    } while (((scanf("%d%c", x, &term) != 2 || term != '\n') && cleanStdin()));
}

int cleanStdin()
{
    while (getchar() != '\n')
        ;
    return 1;
}

int checkIsLowerThenSecret(int x, int secret)
{
    if (x > secret)
    {
        return 0;
    }
    return 1;
}

void printResult(bool isLowerThenSecret, int i)
{
    printf("The secret has a %s value.\nYou have %d remaining chance(s).\n",
           isLowerThenSecret ? "higher" : "lower", i - 1);
}
