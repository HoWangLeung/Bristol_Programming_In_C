
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int askForTheNumber();
int determineResult(int secret, int bet_amount, int bet_type);

enum BetType
{
    odd,
    even,
    particularNumber
};

typedef enum BetType BetType;

int main()
{
    //create the secret
    int secret = arc4random_uniform(36);
    printf("secret = %d\n", secret);

    //ask for the bet_amount
    int bet_amount;
    printf("enter your bet: ");
    scanf("%d", &bet_amount);

    //ask for the bet_type;
    int bet_type;

    printf("Choose the type of bet: \n (0) Odd \n (1) Even\n (2) Particular Number\n");
    scanf("%d", &bet_type);

    int received_money = determineResult(secret, bet_amount, bet_type);

    if (secret == 0 && (bet_type == odd || bet_type == even))
    {
        received_money = 0;
    }

    printf(received_money > 0 ? "Congratulation ! You have won $%d\n" : "Sorry, you did not win any money.\n", received_money);
}

int askForTheNumber()
{
    int number;
    printf("please input your guess: ");
    scanf("%d", &number);
    return number;
}

int determineResult(int secret, int bet_amount, int bet_type)
{
    bool isSecretEven = secret % 2 == 0;

    if (bet_type == particularNumber)
    {
        int particularGuess = askForTheNumber();
        if (particularGuess == secret)
        {
            return bet_amount * 35;
        }
    }
    else if (bet_type == odd && !isSecretEven)
    {
       
        return bet_amount * 2;
    }
    else if (bet_type == even && isSecretEven)
    {
        
        return bet_amount * 2;
    }
    else
    {
        return 0;
    }

    return 0;
}