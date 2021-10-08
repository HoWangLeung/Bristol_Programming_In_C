#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
void test();
void calculate_largest_number(long number, long *largest, long *largest_initial, long current_index);
void calculate_longest_number(long count, long *longest, long *longest_initial, long i);
long get_next_sequence(long number);
int get_sequence_count(long number, int count, long *longest, long *longest_initial, long current_index);

int main()
{
    long largest = 0;
    int count = 1;
    long largest_initial = 0;
    long longest = 0;
    long longest_initial = 0;
    test();
    for (long i = 2; i < 5000; i++)
    {
        count = 1;
        long number = i;
        get_sequence_count(number, count, &longest, &longest_initial, i);
    }

    printf("longest number = %ld\n", longest_initial);
    printf("largest count = %ld\n", longest);
    return 0;
}

int get_sequence_count(long number, int count, long *longest, long *longest_initial, long current_index)
{
    while (number != 1)
    {
        number = get_next_sequence(number);
        count++;
        //calculate_largest_number(number, &largest, &largest_initial, i);
        calculate_longest_number(count, &longest, &longest_initial, current_index);
    }
}

long get_next_sequence(long number)
{
    return number % 2 == 0 ? (number / 2) : (number * 3 + 1);
}

// void calculate_largest_number(long number, long *largest, long *largest_initial, long current_index)
// {
//     if (number > *largest)
//     {
//         *largest = number;
//         *largest_initial = current_index;
//     }
// }

void calculate_longest_number(long count, long *longest, long *longest_initial, long i)
{
    if (count > *longest)
    {
        *longest = count;
        *longest_initial = i;
    };
}

void test()
{
    //test get_next_sequence
    assert(get_next_sequence(2) == 1);
    assert(get_next_sequence(3) == 10);

    long number = 6;
    long count = 1;
    long longest = 0;
    long longest_initial = number;
    long current_index = number;
    while (number != 1)
    {
        number = get_next_sequence(number);
        count++;
        //calculate_largest_number(number, &largest, &largest_initial, i);
        calculate_longest_number(count, &longest, &longest_initial, current_index);
    };
    assert(count == 9);
}