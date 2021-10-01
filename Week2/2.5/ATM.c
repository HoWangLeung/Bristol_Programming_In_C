#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
// #define note 20;
int main()
{

    int note = 20;
    int user_input;
    printf("How much money would you like ? ");
    scanf("%d", &user_input);
    int number_of_note_needed = user_input / note;
    printf("note needed = %d\n", number_of_note_needed);
    printf("I can give you %d or %d, try again.", number_of_note_needed * note, (number_of_note_needed + 1) * note);

    return 0;
}
