#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int len;
    bool valid;
    char *options[] = {"10minutes", "1minute", "10seconds"};
    int user_input;
    printf("Input the cooking time in seconds : ");
    printf("You have 3 options\n");
    printf("%lu\n",sizeof(options));

    // for (int i = 0; i < sizeof(options); i++)
    // {
    //     printf("(%d) - %s", i, options[i]);
    // }


    // if (scanf("%d", &user_input) != 1)
    // {
    //     printf("this is not a number\n");
    // }
    // printf("%d\n", user_input);
    // printf("option = %s\n", options[user_input]);
}