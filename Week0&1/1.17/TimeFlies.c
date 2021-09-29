#include <assert.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    int hh_1, mm_1;
    int hh_2, mm_2;
    printf("Enter a time in 24-hour format:");
    scanf("%d:%d  %d:%d", &hh_1, &mm_1, &hh_2, &mm_2);
    printf("hh_1 = %d , mm_1=%d\n", hh_1, mm_1);
    printf("hh_2 = %d , mm_2=%d\n", hh_2, mm_2);

    int hour_diff = 24 - hh_1 + hh_2;
    int min_diff = mm_2 - mm_1;

    printf("Difference is : %d:%d\n", hour_diff, min_diff);

    return 0;
}

// int main()
// {

// }