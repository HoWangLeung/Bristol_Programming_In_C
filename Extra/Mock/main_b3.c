#include "common.h"

bool negativeedge(int a[][10], int h);

int main(void)
{

    int i;
    int a[1][10] = {{-2}};
    int b[5][10] = {{0}};
    int c[10][10] = {{0}};
    int d[2][10] = {{0}};
    a[0][5] = -17;
    a[0][1] = 10;

    assert(negativeedge(a, 1));
    assert(negativeedge(b, 5));
    assert(negativeedge(c, 5));
    assert(negativeedge(d, 2));
    for (i = 0; i < 100; i++)
    {
        d[rand() % 2][rand() % 10] = -5;
        a[0][rand() % 10] = -5;
        assert(negativeedge(d, 2));
        assert(negativeedge(a, 1));
    }
    b[2][2] ^= -7; //b[2][2] = b[2][2]  ^ -7
    //the final result of this =  -7, 9
    assert(!negativeedge(b, 5));
    b[2][2] ^= -7;
    assert(negativeedge(b, 5));

    return 0;
}