#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define tenSec 10
#define oneMin 600
#define tenMin 6000
void calculateRequiredTime(int options[], int user_input, int n);
void randomize(int arr[], int n);
void swap(int *a, int *b);

int main()
{
    int user_input;
    int temp, randomNumber;
    time_t t;
    srand((unsigned)time(&t));

    printf("How many songs required ? ");
    scanf("%d", &user_input);
    int *songList = malloc(sizeof(int) * user_input);
    for (int i = 0; i < user_input; i++)
    {
            songList[i] = i+1;
    }

    randomize(songList, user_input);
    for (int i = 0; i < user_input; i++)
    {
        printf("%d\n", songList[i]);
    }

    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(int arr[], int n)
{
    srand(time(NULL));
    int i;
    for (i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}
