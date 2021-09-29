#include <stdio.h>
#include <stdbool.h>
int main()
{

    int firstInput;
    printf("How many numbers do you wish to enter ? : ");
    scanf("%d", &firstInput);

    int max = 0;
    int input_2;
    bool error = false;
    printf("Enter %d real numbers: \n", firstInput);
    for (int i = 0; i < firstInput; i++)
    {

        scanf("%d", &input_2);
        if (input_2 % 2 == 0)
        {
            error = true;
        }

        if (input_2 > max)
        {
            max = input_2;
        }
    }

    if (error)
    {
        printf("input only accepts odd numbers");
        return 1;
    }

    printf("max = %d\n", max);

    return 0;
}