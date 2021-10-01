#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
bool check_has_hit(int x, int y, int r);

int main()
{
    // generate random x, y
    int r = 10;
    // hc = hit the circle
    int hc = 0;
    // ha = hit the square
    int ha = 0;
    srand(time(0));
    //check if the dart hits the circle for 500 times;
    for (int i = 0; i < 500; i++)
    {
    
        int x = arc4random_uniform(r + 1);
        int y = arc4random_uniform(r + 1);
        printf("x = %d , y = %d\n", x, y);

        if (check_has_hit(x, y, r) == 1)
        {
            hc++;
        }
        else
        {
            ha++;
        }
    }
    printf("hc = %d , ha = %d\n", hc, ha);
    printf("final result = %d\n", hc * 4 / ha);

    return 0;
}

bool check_has_hit(int x, int y, int r)
{

    if ((x * x) + (y * y) <= r * r)
    {
        return 1;
    }

    return 0;
}
