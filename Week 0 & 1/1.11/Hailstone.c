#include <stdio.h>
#include <stdbool.h>
int main()
{

    int input;
    printf("input a number : ");
    scanf("%d", &input);
    int answer = input;
   
    while (answer != 1)
    {
        if (answer % 2 == 0)
        {
            answer = answer / 2;
        }
        else
        {
            answer = answer * 3 + 1;
        }
        printf("%d\n", answer);
    }
    printf("Finsihed");

    return 0;
}