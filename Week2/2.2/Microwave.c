#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
int calculateRequiredTime(int options[], int user_input, int n);
#define tenSec 10
#define oneMin tenSec * 6
#define tenMin oneMin * 10

int main()
{

    int user_input;
    int options[] = {tenMin, oneMin, tenSec};
    printf("Type the time required: ");
    scanf("%d", &user_input);
    printf("user input = %d\n", user_input);
    int n = sizeof(options) / sizeof(options[0]);
    int a = calculateRequiredTime(options, user_input, n);

    assert(calculateRequiredTime(options, 25, n) == 3);
    assert(calculateRequiredTime(options, 705, n) == 7);

    return 0;
}

int calculateRequiredTime(int options[], int user_input, int n)
{
    int presses = 0;
    int value_remain = user_input;
    for (int i = 0; i < n; i++)
    {
        while (value_remain >= options[i])
        {
            presses++;
            value_remain -= options[i];
        }
    }
    //handle the remaining
    (value_remain > 0 && value_remain <= 10) && presses++;

    printf("Number of button presses= %d\n", presses);

    return presses;
};
