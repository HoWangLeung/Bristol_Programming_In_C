#include <stdio.h>
#include <string.h>
int romanToArabic(char *roman);
int getRomanValue(char c);
int main(int argc, char **argv)
{
    printf("******************************************\n");
    if (argc == 2)
    {
        printf("The roman numeral %s is equal to %d\n",
               argv[1], romanToArabic(argv[1]));
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
    return 0;
}

int romanToArabic(char *roman)
{
    char nextSymbol;
    char currentSymbol;
    int currentValue;
    int nextValue;
    int sum = 0;
    printf("number of roman letter = %lu\n", strlen(roman));
    for (int i = 0; i < strlen(roman); i++)
    {
        currentSymbol = roman[i];
        currentValue = getRomanValue(currentSymbol);
        if (roman[i + 1] != '\0')
        {
            nextSymbol = roman[i + 1];
            nextValue = getRomanValue(nextSymbol);
        };
        printf("\n===>currentSymbol = %c\n", currentSymbol);
        // printf("currentValue = %d\n\n", currentValue);

        printf("nextSymbol = %c\n", nextSymbol);
        //  printf("nextValue = %d\n\n", nextValue);

        if (currentValue < nextValue && (strlen(roman)-i>=2) )
        {
            //printf("cur less then next\n");
            sum += nextValue - currentValue;
            i += 1;
        }
        else
        {
            // printf("cur greater then or equal next\n");
            sum += currentValue;
        }
        printf("sum = %d\n", sum);
    }

    return sum;
}

int getRomanValue(char c)
{
    if (c == 'I')
    {
        return 1;
    }
    if (c == 'V')
    {
        return 5;
    }
    if (c == 'X')
    {
        return 10;
    }
    if (c == 'L')
    {
        return 50;
    }
    if (c == 'C')
    {
        return 100;
    }
    if (c == 'D')
    {
        return 500;
    }
    if (c == 'M')
    {
        return 1000;
    }

    return -1;
};